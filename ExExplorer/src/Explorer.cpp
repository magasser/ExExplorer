#include "eepch.h"
#include "Explorer.h"

void Explorer::SetCurrentPath(const std::filesystem::path& path)
{
	m_CurrentPath = path;
	RefreshEntries();
}

void Explorer::AppendCurrentPath(const std::filesystem::path& pathPart)
{
	m_CurrentPath /= pathPart;
	RefreshEntries();
}

void Explorer::RefreshDrives()
{
	m_CurrentDrives = FileSystem::GetDrives();
}

void Explorer::RefreshEntries()
{
	m_CurrentEntries = !m_CurrentPath.empty() ? FileSystem::GetPathEntries(m_CurrentPath) : std::vector<Entry>();
}
