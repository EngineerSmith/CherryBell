#include "cbpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "platform/OpenGL/OpenGLVertexArray.h"

namespace CherryBell {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}
}