#pragma once

struct GLFWwindow;

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

	void BeginFrame();
	void EndFrame();

	bool ShouldClose();

	void SetTitle(const std::string& title);

private:
	void Init();
	void Terminate();

private:
	std::string m_Title;
	int32_t m_Width;
	int32_t m_Height;
	GLFWwindow* m_GLFWwindow;
};
