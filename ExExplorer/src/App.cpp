#include "eepch.h"
#include "App.h"

#include "Log.h"

App::App(const std::string& name)
	: m_Name(name)
{
	Init();
}

App::~App()
{
	Terminate();
}

void App::Run()
{
	auto drives = FileSystem::GetDrives();
	auto entries = FileSystem::GetPathEntries(drives[0].GetRoot());

	while (!m_Window->ShouldClose())
	{
		OnUpdate();
		OnUIRender();
	}
}

void App::OnUpdate()
{
	OnUpdateCore();
}

void App::OnUIRender()
{
	m_Window->Begin();

	OnUIRenderCore();

	m_Window->End();
}

void App::Init()
{
	Log::Init();

	EE_LOG_INFO("Initializing {} App.", m_Name);

	WindowParams params = { m_Name, 1000, 600 };
	m_Window = std::make_unique<Window>(params);
}

void App::Terminate()
{
	EE_LOG_INFO("Terminating {} App.", m_Name);
}
