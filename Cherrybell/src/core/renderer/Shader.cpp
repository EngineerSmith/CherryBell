#include "cbpch.h"
#include "Shader.h"
#include "core/renderer/Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace CherryBell {
	Ref<Shader> Shader::Create(const std::string& filepath)
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

	Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath)
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

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
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

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		CB_CORE_ASSERT(!Exists(name), "Shader already exists!");
		_shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto& shader = CherryBell::Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath, const std::string& name)
	{
		auto& shader = CherryBell::Shader::Create(name, filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		CB_CORE_ASSERT(Exists(name), "Shader not found");
		return _shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return _shaders.find(name) != _shaders.end();
	}
}