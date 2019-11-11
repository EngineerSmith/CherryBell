#include "cbpch.h"
#include "Buffer.h"
#include "core/renderer/Renderer.h"
#include "platform/OpenGL/OpenGLBuffer.h"

namespace CherryBell {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}
	
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}
}

