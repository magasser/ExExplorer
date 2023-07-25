#include "eepch.h"
#include "Window.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Core.h"

Window::Window(const WindowParams& params)
	: m_Title(params.Title), m_Width(params.Width), m_Height(params.Height)
{
	Init();
}

Window::~Window()
{
	Terminate();
}

void Window::BeginFrame()
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_GLFWwindow);
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_GLFWwindow) != 0;
}

void Window::SetTitle(const std::string& title)
{
	m_Title = title;
}

void Window::Init()
{
	if (!glfwInit())
	{
		EE_ASSERT(false, "Failed to initialize GLFW.");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_GLFWwindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

	if (!m_GLFWwindow)
	{
		EE_ASSERT(false, "Failed to create GLFW window.");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_GLFWwindow);
	glfwSwapInterval(0);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_GLFWwindow, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void Window::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_GLFWwindow);
	glfwTerminate();
}
