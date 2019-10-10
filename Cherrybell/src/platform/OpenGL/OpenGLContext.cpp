#include "cbpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace CherryBell {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: _windowHandle(windowHandle)
	{
		CB_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		CB_CORE_INFO("Creating OpenGL Context");
		glfwMakeContextCurrent(_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CB_CORE_ASSERT(status, "Failed to initialize Glad!");
#ifdef CB_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		CB_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 4), "CherryBell requires at least OpenGL version 4.4!");
#endif
		CB_CORE_INFO("OpenGL Info:\n\t\t\tVendor:   {0}\n\t\t\tRenderer: {1}\n\t\t\tVersion:  {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}
}