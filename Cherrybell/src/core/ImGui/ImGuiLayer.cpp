#include "cbpch.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include "platform/OpenGL/ImGuiOpenGLRender.h"
#include "core/Application.h"

#include "core/KeyCodes.h"

//HACK temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace CherryBell {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui")
	{}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	// HACK should use CherryBell keycodes
		io.KeyMap[ImGuiKey_Tab] = CB_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = CB_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = CB_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = CB_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = CB_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = CB_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = CB_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = CB_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = CB_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = CB_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = CB_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = CB_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = CB_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = CB_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = CB_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = CB_KEY_A;
		io.KeyMap[ImGuiKey_C] = CB_KEY_C;
		io.KeyMap[ImGuiKey_V] = CB_KEY_V;
		io.KeyMap[ImGuiKey_X] = CB_KEY_X;
		io.KeyMap[ImGuiKey_Y] = CB_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = CB_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = _time > 0.0f ? (time - _time) : (1.0f / 60.0f);
		_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(CB_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(CB_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(CB_BIND_EVENT_FN(ImGuiLayer::OnMouseMoveEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(CB_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(CB_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(CB_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(CB_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(CB_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = true;
		return false;
	}
	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = false;
		return false;
	}
	bool ImGuiLayer::OnMouseMoveEvent(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());
		return false;
	}
	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += event.GetOffsetX();
		io.MouseWheelH += event.GetOffsetY();
		return false;
	}
	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[CB_KEY_LEFT_CONTROL] || io.KeysDown[CB_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[CB_KEY_LEFT_SHIFT] || io.KeysDown[CB_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[CB_KEY_LEFT_ALT] || io.KeysDown[CB_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[CB_KEY_LEFT_SUPER] || io.KeysDown[CB_KEY_RIGHT_SUPER];
		return false;
	}
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;
		return false;
	}
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		int key = event.GetKeyCode();
		if (key > 0 && key < 0x10000)
			io.AddInputCharacter((unsigned short)key);
		return false;
	}
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)event.GetWidth(), (float)event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, (int)event.GetWidth(), (int)event.GetHeight());
		return false;
	}
}