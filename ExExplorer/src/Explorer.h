#pragma once

#include "FileSystem.h"

class Explorer
{
public:
	Explorer() : m_CurrentPath(std::filesystem::path{}) { ForceRefresh(); }

	void ForceRefresh()
	{
		RefreshDrives();
		RefreshEntries();
	}

	inline bool HasCurrentPath() const { return !m_CurrentPath.empty(); }

	inline const std::vector<Drive>& GetCurrentDrives() const { return m_CurrentDrives; }
	inline const std::vector<Entry>& GetCurrentEntries() const { return m_CurrentEntries; }
	inline const std::filesystem::path& GetCurrentPath() const { return m_CurrentPath; }

	void SetCurrentPath(const std::filesystem::path& path);
	void AppendCurrentPath(const std::filesystem::path& pathPart);

private:
	void RefreshDrives();
	void RefreshEntries();

private:
	std::filesystem::path m_CurrentPath;
	std::vector<Drive> m_CurrentDrives;
	std::vector<Entry> m_CurrentEntries;
};
