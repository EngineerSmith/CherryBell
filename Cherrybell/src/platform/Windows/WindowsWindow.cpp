#include "cbpch.h"
#include "WindowsWindow.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/MouseEvent.h"
#include "core/events/KeyEvent.h"
#include "platform/OpenGL/OpenGLContext.h"

#include <stb_image.h>

namespace CherryBell {
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* detail)
	{
		CB_CORE_ERROR("GLFW Error: ({0}) {1}", error, detail);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		_data.Title = props.Title;
		_data.Width = props.Width;
		_data.Height = props.Height;
		_data.Mode = WindowMode::None;

		CB_CORE_INFO("Creating Window \"{0}\" ({1}, {2})", _data.Title, _data.Width, _data.Height);

		if (s_GLFWWindowCount == 0)
		{
			CB_CORE_INFO("Initalizing GLFW");
			int success = glfwInit();
			CB_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

#ifdef CB_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		_window = glfwCreateWindow((int)_data.Width, (int)_data.Height, _data.Title.c_str(), nullptr, nullptr);
		s_GLFWWindowCount++;

		_primaryMonitor = glfwGetPrimaryMonitor();
		_primaryVidmode = *glfwGetVideoMode(_primaryMonitor);

		_context = CreateScope<OpenGLContext>(_window);
		_context->Init();

		_data.WindowedData.Width = props.Width;
		_data.WindowedData.Height = props.Height;
		glfwGetWindowPos(_window, &_data.WindowedData.X, &_data.WindowedData.Y);
		SetWindowMode(props.Mode);
		
		glfwSetWindowUserPointer(_window, &_data);
		SetVSync(true);

		//GLFW Callbacks
		glfwSetWindowSizeCallback(_window,
			[](GLFWwindow* window, int width, int height)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizedEvent event(width, height);
				data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(_window,
			[](GLFWwindow* window)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowClosedEvent event;
				data.EventCallback(event);
			});
		glfwSetWindowPosCallback(_window,
			[](GLFWwindow* window, int x, int y)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowMovedEvent event(x, y);
				data.EventCallback(event);
			});
		glfwSetWindowFocusCallback(_window, 
			[](GLFWwindow* window, int focused)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (focused == GLFW_TRUE)
				{
					WindowFocusedEvent event;
					data.EventCallback(event);
				}
				else
				{
					WindowLostFocusEvent event;
					data.EventCallback(event);
				}
			});
		glfwSetKeyCallback(_window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyCode keyCode = static_cast<KeyCode>(key);
				switch (action)
				{
				case GLFW_PRESS:
				{
					data.RepeatedKeys[keyCode] = 0;
					KeyPressedEvent event(keyCode, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					data.RepeatedKeys.erase(keyCode);
					KeyReleasedEvent event(keyCode);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					data.RepeatedKeys[keyCode]++;
					KeyPressedEvent event(keyCode, data.RepeatedKeys[keyCode]);
					data.EventCallback(event);
					break;
				}
				default:
					CB_CORE_WARN("GLFW Key press event recorded but no event created with action: {0}, key: {1}", action, key);
					break;
				}
			});
		glfwSetCharCallback(_window,
			[](GLFWwindow* window, unsigned int key){
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(static_cast<KeyCode>(key));
				data.EventCallback(event);
			});
		glfwSetMouseButtonCallback(_window,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(static_cast<MouseCode>(button));
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
						data.EventCallback(event);
						break;
					}
					default:
						CB_CORE_WARN("GLFW Mouse button event recorded but no event created with action: {0}, button: {1}", action, button);
						break;
				}
			});

		glfwSetScrollCallback(_window,
			[](GLFWwindow* window, double offsetX, double offsetY)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)offsetX, (float)offsetY);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(_window,
			[](GLFWwindow* window, double x, double y)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)x, (float)y);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		_data.RepeatedKeys.clear();
		glfwDestroyWindow(_window);

		s_GLFWWindowCount--;
		if (s_GLFWWindowCount == 0)
		{
			CB_CORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		_context->SwapBuffers();
	}

	double WindowsWindow::GetTimeSeconds() const
	{
		return glfwGetTime();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		_data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return _data.VSync;
	}

	void WindowsWindow::SetWindowMode(WindowMode mode, int width, int height)
	{
		if (_window == nullptr)
		{
			CB_CORE_ERROR(false, "Attempted to SetWindowMode before window exists!");
			return;
		}

		if (_data.Mode == mode)
			return;

		if (_data.Mode == WindowMode::Windowed) 
		{
			_data.WindowedData.Width = _data.Width;
			_data.WindowedData.Height = _data.Height;
			glfwGetWindowPos(_window, &_data.WindowedData.X, &_data.WindowedData.Y);
		}

		GLFWmonitor* monitor = mode == WindowMode::Windowed ? nullptr : _primaryMonitor;

		if (mode == WindowMode::Boarderless) 
		{
			width = _primaryVidmode.width;
			height = _primaryVidmode.height;
		}
		else if (width == 0 || height == 0) 
		{
			width = _data.WindowedData.Width;
			height = _data.WindowedData.Height;
		}

		glfwSetWindowMonitor(_window, monitor, _data.WindowedData.X, _data.WindowedData.Y, width, height, monitor == nullptr? 0 : _primaryVidmode.refreshRate);
		
		_data.Width = width;
		_data.Height = height;

		if (_data.EventCallback) {
			WindowResizedEvent e(width, height);
			_data.EventCallback(e);
		}

		CB_CORE_INFO("Changed window mode from {0} to {1}: [{2}, {3}]", _data.Mode, mode, width, height);
		_data.Mode = mode;
	}

	void WindowsWindow::SetWindowIcon(std::string_view path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.data(), &width, &height, &channels, 4);
		CB_CORE_ASSERT(channels == 4, "Icon must be RGBA!");

		GLFWimage images[1];
		images[0].width = width;
		images[0].height = height;
		images[0].pixels = data;
		glfwSetWindowIcon(_window, 1, images);
		stbi_image_free(data);
	}
}
