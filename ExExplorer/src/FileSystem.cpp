#include "eepch.h"
#include "Filesystem.h"

#include "Core.h"

#define DRIVE_CHAR_COUNT 4

static std::string WideStringToString(LPWSTR wideString)
{
	int32_t requiredSize = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, nullptr, 0, nullptr, nullptr);

	LPSTR buffer = (LPSTR)alloca(requiredSize);
	WideCharToMultiByte(CP_UTF8, 0, wideString, -1, buffer, requiredSize, nullptr, nullptr);

	return std::string(buffer);
}

static std::string DriveTypeToString(DriveType type)
{
	switch (type)
	{
	case DriveType::Unknown: return "Unknown";
	case DriveType::NoRootDir: return "No Root Directory";
	case DriveType::Removable: return "Removable";
	case DriveType::Fixed: return "Fixed";
	case DriveType::Remote: return "Remote";
	case DriveType::CDROM: return "CD ROM";
	case DriveType::RAMDisk: return "RAM Disk";
	default: return "";
	}
}

std::vector<Drive> FileSystem::GetDrives()
{
	constexpr DWORD wideDrivesBufferSize = sizeof(wchar_t) * 26 * DRIVE_CHAR_COUNT;
	WCHAR wideDrivesBuffer[wideDrivesBufferSize];
	DWORD charCount = GetLogicalDriveStrings(wideDrivesBufferSize, wideDrivesBuffer);

	std::vector<Drive> drives;
	drives.reserve(charCount / DRIVE_CHAR_COUNT);

	for (uint32_t p = 0; p < charCount; p += DRIVE_CHAR_COUNT)
	{
		LPWSTR wideRoot = &wideDrivesBuffer[p];

		DriveType type = (DriveType)GetDriveType(wideRoot);

		DWORD sectorsPerCluster, bytesPerSector, freeClusterCount, totalClusterCount;
		bool hasDiskSpaceInfo = GetDiskFreeSpace(wideRoot,
		                                         &sectorsPerCluster,
		                                         &bytesPerSector,
		                                         &freeClusterCount,
		                                         &totalClusterCount);

		WCHAR wideVolumeNameBuffer[MAX_PATH];
		WCHAR wideFileSystemNameBuffer[MAX_PATH];
		DWORD volumeSerialNumber;
		bool hasVolumeInfo = GetVolumeInformation(wideRoot,
		                                          wideVolumeNameBuffer,
		                                          MAX_PATH,
		                                          &volumeSerialNumber,
		                                          nullptr,
		                                          nullptr,
		                                          wideFileSystemNameBuffer,
		                                          MAX_PATH);

		uint64_t bytesPerCluster = bytesPerSector * sectorsPerCluster;
		Size freeStorage(bytesPerCluster * freeClusterCount);
		Size totalStorage(bytesPerCluster * totalClusterCount);

		drives.push_back(Drive(WideStringToString(&wideDrivesBuffer[p]),
		                       hasVolumeInfo ? WideStringToString(wideVolumeNameBuffer) : DriveTypeToString(type),
		                       hasVolumeInfo ? WideStringToString(wideFileSystemNameBuffer) : "Unkown",
		                       hasVolumeInfo ? volumeSerialNumber : 0,
		                       type,
		                       hasDiskSpaceInfo ? freeStorage : 0,
		                       hasDiskSpaceInfo ? totalStorage : 0));
	}

	return drives;
}

std::vector<Entry> FileSystem::GetPathEntries(const std::filesystem::path& path)
{
	std::vector<Entry> entries;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		entries.push_back(Entry(entry));
	}

	return entries;
}
