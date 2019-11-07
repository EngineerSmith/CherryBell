#pragma once
#include "core/renderer/RendererID.h"

#include <glm/glm.hpp>
#include <string>

namespace CherryBell {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static Ref<Shader> Create(std::string_view filepath);
		static Ref<Shader> Create(std::string_view name, std::string_view filepath);
		static Ref<Shader> Create(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc);

		virtual const std::string& GetName() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Set(const glm::mat4& value, std::string_view name) = 0;
		virtual void Set(const glm::mat3& value, std::string_view name) = 0;
		virtual void Set(const glm::vec4& value, std::string_view name) = 0;
		virtual void Set(const glm::vec3& value, std::string_view name) = 0;
		virtual void Set(const glm::vec2& value, std::string_view name) = 0;
		virtual void Set(const float value, std::string_view name) = 0;
		virtual void Set(const int value, std::string_view name) = 0;
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(std::string_view name, const Ref<Shader>& shader);
		Ref<Shader> Load(std::string_view filepath);
		Ref<Shader> Load(std::string_view filepath, std::string_view name);

		Ref<Shader> Get(std::string_view name);
		bool Exists(std::string_view name) const;

		std::unordered_map<std::string, Ref<Shader>>::iterator begin() { return _shaders.begin(); }
		std::unordered_map<std::string, Ref<Shader>>::iterator end() { return _shaders.end(); }
	private:
		std::unordered_map<std::string, Ref<Shader>> _shaders;
	};
}