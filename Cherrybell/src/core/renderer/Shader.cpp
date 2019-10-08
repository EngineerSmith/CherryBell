#include "cbpch.h"
#include "Shader.h"
#include "core/renderer/Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace CherryBell {
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}
}