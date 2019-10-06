#pragma once
#include "core/renderer/RendererID.h"

#include <string>
#include <glm/glm.hpp>

namespace CherryBell {
	//TODO make generic and move OPENGL code to its own instance 
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);
	private:
		RendererID _rendererID;
	};
}