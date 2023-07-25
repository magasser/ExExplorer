#pragma once

#include "UI/Window.h"

class App
{
public:
	App(const std::string& name);
	~App();

	void Run();

private:
	void Init();
	void Terminate();

private:
	std::string m_Name;
	std::unique_ptr<Window> m_Window;
};
