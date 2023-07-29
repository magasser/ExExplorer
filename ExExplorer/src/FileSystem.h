#pragma once

#include <filesystem>

#define KILO_MULTIPLIER 1024.0

class Size
{
public:
	Size(uintmax_t bytes) : m_Bytes(bytes) {}
	~Size() {}

	inline uintmax_t GetBytes() const { return m_Bytes; }
	inline double GetKilobytes() const { return (double)m_Bytes / KILO_MULTIPLIER; }
	inline double GetMegabytes() const { return GetKilobytes() / KILO_MULTIPLIER; }
	inline double GetGigabytes() const { return GetMegabytes() / KILO_MULTIPLIER; }
	inline double GetTerabytes() const { return GetGigabytes() / KILO_MULTIPLIER; }

private:
	uintmax_t m_Bytes;
};

enum class DriveType
{
	Unknown = 0,
	NoRootDir,
	Removable,
	Fixed,
	Remote,
	CDROM,
	RAMDisk
};

class Drive
{
public:
	Drive(const std::string& root,
	      const std::string& name,
	      const std::string& fileSystemName,
	      uint64_t serialNumber,
	      DriveType type,
	      Size freeStorage,
	      Size totalStorage)
		: m_Root(root),
		  m_Name(name),
		  m_FileSystemName(fileSystemName),
		  m_SerialNumber(serialNumber),
		  m_Type(type),
		  m_FreeStorage(freeStorage),
		  m_TotalStorage(totalStorage) { }

	~Drive() {}

	inline const std::string& GetRoot() const { return m_Root; }
	inline const std::string& GetName() const { return m_Name; }
	inline const std::string& GetFileSystemName() const { return m_FileSystemName; }
	inline uint64_t GetSerialNumber() const { return m_SerialNumber; }
	inline const DriveType GetType() const { return m_Type; }
	inline const Size GetFreeStorage() const { return m_FreeStorage; }
	inline const Size GetTotalStorage() const { return m_TotalStorage; }

	inline bool IsExplorable() const { return m_TotalStorage.GetBytes() > 0; }

private:
	std::string m_Root, m_Name, m_FileSystemName;
	uint64_t m_SerialNumber;
	DriveType m_Type;
	Size m_FreeStorage, m_TotalStorage;
};

class Entry
{
public:
	Entry(const std::filesystem::directory_entry& entry)
		: m_Name(entry.path().filename().string()),
		  m_Path(entry.path()),
		  m_Extension(entry.path().extension().string()),
		  m_Size(entry.file_size()),
		  m_IsDirectory(entry.is_directory()),
		  m_LastModified(entry.last_write_time()) {}

	~Entry() {}

	inline const std::string& GetName() const { return m_Name; }
	inline const std::filesystem::path& GetPath() const { return m_Path; }
	inline const std::string& GetExtension() const { return m_Extension; }
	inline Size GetSize() const { return m_Size; }
	inline std::filesystem::file_time_type GetLastModified() const { return m_LastModified; }
	inline bool IsDirectory() const { return m_IsDirectory; };

private:
	std::string m_Name;
	std::filesystem::path m_Path;
	std::string m_Extension;
	Size m_Size;
	std::filesystem::file_time_type m_LastModified;
	bool m_IsDirectory;
};

class FileSystem
{
public:
	static std::vector<Drive> GetDrives();
	static std::vector<Entry> GetPathEntries(const std::filesystem::path& path);
};
