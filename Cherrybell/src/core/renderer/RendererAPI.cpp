#include "cbpch.h"
#include "RendererAPI.h"
#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace CherryBell {
	RendererAPI::API RendererAPI::s_api = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_api)
		{
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}

}
