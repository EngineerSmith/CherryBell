#pragma once
#include "core/renderer/Shader.h"
#include "core/renderer/RendererID.h"
#include <glm/glm.hpp>

namespace CherryBell {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		
		void UploadUniformMat3(const glm::mat3& matrix, const std::string& name);
		void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);

		void UploadUniformFloat4(const glm::vec4& value, const std::string& name);
		void UploadUniformFloat3(const glm::vec3& value, const std::string& name);
		void UploadUniformFloat2(const glm::vec2& value, const std::string& name);
		void UploadUniformFloat(float value, const std::string& name);

		void UploadUniformInt(int value, const std::string& name);


	private:
		RendererID _rendererID;
	};
}