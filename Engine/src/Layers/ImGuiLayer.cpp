#include "ImGuiLayer.hpp"
//#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "../Application.hpp"
#include "../Events/KeyEvent.hpp"
#include "../Log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3_loader.h>


namespace ENGINE 
{

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGUI Layer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		io.Fonts->AddFontFromFileTTF("assets/fonts/Neuropol.otf", 12.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/whitrabt.ttf", 10.0f);

		//ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();
		SetThemeColors();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		style.TabRounding = 4;
		style.ScrollbarRounding = 9;
		style.WindowRounding = 7;
		style.GrabRounding = 3;
		style.FrameRounding = 3;
		style.PopupRounding = 4;
		style.ChildRounding = 4;

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true); 
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		//static bool show = true;
		//ImGui::ShowDemoWindow(&show);
	}


	void ImGuiLayer::SetDefaultTheme()
	{
		ImGui::StyleColorsDark();
	}

	void ImGuiLayer::SetThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

	void ImGuiLayer::SetTheme2()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
		colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		// Border
		colors[ImGuiCol_Border] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
		colors[ImGuiCol_BorderShadow] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.24f };
		// Text
		colors[ImGuiCol_Text] = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		colors[ImGuiCol_TextDisabled] = ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f };
		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_CheckMark] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };
		// Popups
		colors[ImGuiCol_PopupBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 0.92f };
		// Slider
		colors[ImGuiCol_SliderGrab] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.54f };
		colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.54f };
		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.13f, 0.13, 0.17, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.24, 0.24f, 0.32f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.2f, 0.22f, 0.27f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
		colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.24f, 0.24f, 0.32f, 1.0f };
		// Seperator
		colors[ImGuiCol_Separator] = ImVec4{ 0.44f, 0.37f, 0.61f, 1.0f };
		colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };
		colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 1.0f };
		// Resize Grip
		colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
		colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.29f };
		colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 0.29f };
		// Docking
		colors[ImGuiCol_DockingPreview] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};
		/*auto& style = ImGui::GetStyle();
		style.TabRounding = 4;
		style.ScrollbarRounding = 9;
		style.WindowRounding = 7;
		style.GrabRounding = 3;
		style.FrameRounding = 3;
		style.PopupRounding = 4;
		style.ChildRounding = 4;*/
	}

	void ImGuiLayer::SetTheme3()
	{
		auto& colors = ImGui::GetStyle().Colors;

		colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);//ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
	}

}