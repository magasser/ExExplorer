#pragma once

#include "Window.h"
#include "FileSystem.h"

class App
{
public:
	App(const std::string& name);
	virtual ~App();

	void Run();

protected:
	virtual void OnUpdateCore() = 0;
	virtual void OnUIRenderCore() = 0;

private:
	void OnUpdate();
	void OnUIRender();

	void Init();
	void Terminate();

private:
	std::string m_Name;
	std::unique_ptr<Window> m_Window;
};
