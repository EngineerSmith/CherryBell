#pragma once
#include "core/renderer/Shader.h"
#include "core/renderer/RendererID.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace CherryBell {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string_view filepath);
		OpenGLShader(std::string_view name, std::string_view filepath);
		OpenGLShader(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		const std::string& GetName() const override { return _name; }

		void Set(const glm::mat4& value, std::string_view name) override;
		void Set(const glm::mat3& value, std::string_view name) override;
		void Set(const glm::vec4& value, std::string_view name) override;
		void Set(const glm::vec3& value, std::string_view name) override;
		void Set(const glm::vec2& value, std::string_view name) override;
		void Set(const float value, std::string_view name) override;
		void Set(const int value, std::string_view name) override;

		void UploadUniformMat4(const glm::mat4& matrix, std::string_view name);
		void UploadUniformMat3(const glm::mat3& matrix, std::string_view name);
		void UploadUniformFloat4(const glm::vec4& value, std::string_view name);
		void UploadUniformFloat3(const glm::vec3& value, std::string_view name);
		void UploadUniformFloat2(const glm::vec2& value, std::string_view name);
		void UploadUniformFloat(float value, std::string_view name);
		void UploadUniformInt(int value, std::string_view name);
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		RendererID _rendererID;
		std::string _name;
	};
}