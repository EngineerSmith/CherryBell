#include "cbpch.h"
#include "RenderCommand.h"
#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace CherryBell {
	Scope<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::Create();
}
