#include "eepch.h"
#include "Window.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Core.h"

static void glfwErrorCallback(int32_t error, const char* description)
{
	EE_LOG_ERROR("[GLFW ERROR] ({0}): {1}.", error, description);
}

Window::Window(const WindowParams& params)
	: m_Title(params.Title),
	  m_Width(params.Width),
	  m_Height(params.Height),
	  m_ClearColor(ImVec4(0.0f, 0.0f, 0.0f, 1.0f))
{
	Init();
}

Window::~Window()
{
	Terminate();
}

void Window::Begin()
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	int32_t window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::Begin(m_Title.c_str(), nullptr, window_flags);

	ImGui::PopStyleVar(3);
}

void Window::End()
{
	ImGui::End();

	ImGui::Render();
	int32_t displayWidth, displayHeight;
	glfwGetFramebufferSize(m_GLFWwindow, &displayWidth, &displayHeight);
	glViewport(0, 0, displayWidth, displayHeight);
	glClearColor(m_ClearColor.x * m_ClearColor.w,
	             m_ClearColor.y * m_ClearColor.w,
	             m_ClearColor.z * m_ClearColor.w,
	             m_ClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backupContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupContext);
	}

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
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit())
		return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_GLFWwindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

	if (!m_GLFWwindow)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_GLFWwindow);
	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

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
