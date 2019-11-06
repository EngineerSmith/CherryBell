#pragma once
#include "core/renderer/RendererID.h"

#include <glm/glm.hpp>
#include <string>

namespace CherryBell {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual const std::string& GetName() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Set(const glm::mat4& value, const std::string& name) = 0;
		virtual void Set(const glm::mat3& value, const std::string& name) = 0;
		virtual void Set(const glm::vec4& value, const std::string& name) = 0;
		virtual void Set(const glm::vec3& value, const std::string& name) = 0;
		virtual void Set(const glm::vec2& value, const std::string& name) = 0;
		virtual void Set(const float value, const std::string& name) = 0;
		virtual void Set(const int value, const std::string& name) = 0;
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& filepath, const std::string& name);

		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> _shaders;
	};
}