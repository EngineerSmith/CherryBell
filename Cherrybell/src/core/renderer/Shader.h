#pragma once
#include <string>

typedef uint32_t RendererID;
	
namespace CherryBell {
	//TODO make generic and move OPENGL code to its own instance 
	class Shader
	{
	public:
		Shader(std::string vertexSrc, std::string fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		RendererID _rendererID;
	};
}