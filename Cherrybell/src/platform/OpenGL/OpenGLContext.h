#pragma once
#include "core/renderer/GraphicsContext.h"

struct GLFWwindow;

namespace CherryBell {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* _windowHandle;
	};
}