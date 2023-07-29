#pragma once

#include "App.h"
#include "Explorer.h"

class ExExplorerApp : public App
{
public:
	ExExplorerApp() : App("ExExplorer") {}

private:
	void OnUpdateCore() override;
	void OnUIRenderCore() override;

private:
	Explorer m_Explorer;
	bool m_HasUpdated;
	std::filesystem::path m_NewPath;
};
