#include "cbpch.h"
#include "RenderCommand.h"

#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace CherryBell {
	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI();
}