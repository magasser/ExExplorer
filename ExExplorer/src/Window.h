#pragma once

#include <imgui.h>
#include <GLFW/glfw3.h>

struct WindowParams
{
	std::string Title = "ExExplorer";
	int32_t Width = 1000;
	int32_t Height = 600;
};

class Window
{
public:
	Window(const WindowParams& params);
	~Window();

	void Begin();
	void End();

	bool ShouldClose();

	void SetTitle(const std::string& title);

private:
	void Init();
	void Terminate();

private:
	std::string m_Title;
	int32_t m_Width;
	int32_t m_Height;
	ImVec4 m_ClearColor;
	GLFWwindow* m_GLFWwindow;
};
