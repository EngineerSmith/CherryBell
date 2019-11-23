#pragma once
#include "core/renderer/Window.h"
#include "core/renderer/GraphicsContext.h"
#include "core/input/KeyCodes.h"

#include <GLFW/glfw3.h>

namespace CherryBell {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		double GetTimeSeconds() const override;

		unsigned int GetWidth() const override { return _data.Width; }
		unsigned int GetHeight() const override { return _data.Height; }
		std::pair<unsigned int, unsigned int> GetSize() override { return std::make_pair<unsigned int, unsigned int>((unsigned int)_data.Width, (unsigned int)_data.Height); }

		void SetEventCallback(const EventCallbackFn& callback) override {
			_data.EventCallback = callback;
		}
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void SetWindowMode(WindowMode mode, int width = 0, int height = 0) override;

		void SetWindowIcon(std::string_view path) override;

		inline void* GetNativeWindow() const override { return _window; };
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* _window;
		GLFWmonitor* _primaryMonitor;
		GLFWvidmode _primaryVidmode;
		Scope<GraphicsContext> _context;

		struct WindowData
		{
			std::string Title;
			int Width, Height;
			bool VSync;
			WindowMode Mode;
			WindowedModeData WindowedData;
			EventCallbackFn EventCallback;
			std::unordered_map<KeyCode, unsigned int> RepeatedKeys;
		};
		WindowData _data;
	};
}
