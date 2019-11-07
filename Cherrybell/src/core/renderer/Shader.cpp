#include "cbpch.h"
#include "Shader.h"
#include "core/renderer/Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace CherryBell {
	Ref<Shader> Shader::Create(std::string_view filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}

	Ref<Shader> Shader::Create(std::string_view name, std::string_view filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, filepath);
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}

	Ref<Shader> Shader::Create(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "Renderer API \"None\" currently unsupported!");
			return nullptr;
		default:
			CB_CORE_ASSERT(false, "Unsupported Renderer API!");
			return nullptr;
		}
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}

	void ShaderLibrary::Add(std::string_view name, const Ref<Shader>& shader)
	{
		CB_CORE_ASSERT(!Exists(name), "Shader already exists!");
		_shaders[name.data()] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(std::string_view filepath)
	{
		auto& shader = CherryBell::Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(std::string_view filepath, std::string_view name)
	{
		auto& shader = CherryBell::Shader::Create(name, filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(std::string_view name)
	{
		CB_CORE_ASSERT(Exists(name), "Shader not found");
		return _shaders[name.data()];
	}

	bool ShaderLibrary::Exists(std::string_view name) const
	{
		return _shaders.find(name.data()) != _shaders.end();
	}
}