#include "cbpch.h"
#include "Texture.h"
#include "core/renderer/Renderer.h"
#include "platform/OpenGL/OpenGLTexture.h"

namespace CherryBell {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}
}