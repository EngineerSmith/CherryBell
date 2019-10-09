#include "cbpch.h"
#include "WindowsWindow.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/MouseEvent.h"
#include "core/events/KeyEvent.h"
#include "platform/OpenGL/OpenGLContext.h"

namespace CherryBell {
	static bool s_GLFWInitialized = false;

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

		CB_CORE_INFO("Creating Window \"{0}\" ({1}, {2})", _data.Title, _data.Width, _data.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			CB_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		_window = glfwCreateWindow((int)_data.Width, (int)_data.Height, _data.Title.c_str(), nullptr, nullptr);
		
		_context = new OpenGLContext(_window);
		_context->Init();
		
		glfwSetWindowUserPointer(_window, &_data);
		SetVSync(true);

		//GLFW Callbacks
		glfwSetWindowSizeCallback(_window,
			[](GLFWwindow* window, int width, int height)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(_window,
			[](GLFWwindow* window)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});
		glfwSetKeyCallback(_window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					data.RepeatedKeys.erase(key);
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					if (data.RepeatedKeys.find(key) != data.RepeatedKeys.end())
					{
						data.RepeatedKeys[key]++;
					}
					else
					{
						data.RepeatedKeys[key] = 1;
					}
					KeyPressedEvent event(key, data.RepeatedKeys[key]);
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
				KeyTypedEvent event(key);
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
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
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
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		_context->SwapBuffers();
	}

	float WindowsWindow::GetTime() const
	{
		return (float)glfwGetTime();
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
}