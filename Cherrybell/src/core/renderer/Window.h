#pragma once
#include "core/Core.h"
#include "core/events/Event.h"

namespace CherryBell {
	enum class WindowMode
	{
		None = 0,
		Windowed, 
		Boarderless
	};

	struct WindowedModeData {
		int X, Y, Width, Height;
	};

	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;
		WindowMode Mode;

		WindowProps(std::string_view title = "CherryBell Engine",
			unsigned int width = 720,
			unsigned int height = 480,
			WindowMode mode = WindowMode::Windowed)
			: Title(title), Width(width), Height(height), Mode(mode)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual double GetTimeSeconds() const = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		
		virtual void SetWindowMode(WindowMode mode, int width = 0, int height = 0) = 0;

		virtual void SetWindowIcon(std::string_view path) = 0;

		virtual inline void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
