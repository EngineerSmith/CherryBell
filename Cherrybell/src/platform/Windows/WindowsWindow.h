#pragma once
#include "core/renderer/Window.h"
#include "core/renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace CherryBell {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		float GetTime() const override;

		inline unsigned int GetWidth() const override { return _data.Width; }
		inline unsigned int GetHeight() const override { return _data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override {
			_data.EventCallback = callback;
		}
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline void* GetNativeWindow() const override { return _window; };
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* _window;
		GraphicsContext* _context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
			std::unordered_map<int, int> RepeatedKeys;
		};

		WindowData _data;
	};
}