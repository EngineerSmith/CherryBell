#include "cbpch.h"
#include "OpenGLShader.h"
#include "core/io/File.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace CherryBell {
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment")
			return GL_FRAGMENT_SHADER;
		CB_CORE_ASSERT(false, "Unknown Shader type: {0}", type);
		return 0;
	}

	OpenGLShader::OpenGLShader(std::string_view filepath)
	{
		std::string source = IO::ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);
	
		// Extract file name from filepath
		// assets/shaders/Texture.glsl -> Texture
		// TODO move to helper class
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind(".");
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		_name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(std::string_view name, std::string_view filepath)
		: _name(name)
	{
		std::string source = IO::ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc)
		: _name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(_rendererID);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			CB_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			CB_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			CB_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);
			
			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		CB_CORE_ASSERT(shaderSources.size() <= 2, "Currently only support 2 shader functions.");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum shaderType = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(shaderType);
			const char* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);
				for (auto& shaderId : glShaderIDs)
					glDeleteShader(shaderId);

				CB_CORE_ERROR("{0}", infoLog.data());
				CB_CORE_ASSERT(false, "Shader failed to compile!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (auto& shaderId : glShaderIDs)
				glDeleteShader(shaderId);

			CB_CORE_ERROR("{0}", infoLog.data());
			CB_CORE_ASSERT(false, "Shader link failed!");
			return;
		}

		for (auto& shaderId : glShaderIDs)
		{
			glDetachShader(program, shaderId);
			glDeleteShader(shaderId);
		}
		_rendererID = program;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(_rendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::Set(const glm::mat4& value, std::string_view name)
	{
		UploadUniformMat4(value, name);
	}

	void OpenGLShader::Set(const glm::mat3& value, std::string_view name)
	{
		UploadUniformMat3(value, name);
	}

	void OpenGLShader::Set(const glm::vec4& value, std::string_view name)
	{
		UploadUniformFloat4(value, name);
	}

	void OpenGLShader::Set(const glm::vec3& value, std::string_view name)
	{
		UploadUniformFloat3(value, name);
	}

	void OpenGLShader::Set(const glm::vec2& value, std::string_view name)
	{
		UploadUniformFloat2(value, name);
	}

	void OpenGLShader::Set(const float value, std::string_view name)
	{
		UploadUniformFloat(value, name);
	}

	void OpenGLShader::Set(const int value, std::string_view name)
	{
		UploadUniformInt(value, name);
	}

	void OpenGLShader::UploadUniformMat3(const glm::mat3& matrix, std::string_view name)
	{
		GLint location = glGetUniformLocation(_rendererID, name.data());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const glm::mat4& matrix, std::string_view name)
	{
		GLint location = glGetUniformLocation(_rendererID, name.data());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformFloat4(const glm::vec4& value, std::string_view name)
	{
		GLint location = glGetUniformLocation(_rendererID, name.data());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformFloat3(const glm::vec3& value, std::string_view name)
	{
		GLint location = glGetUniformLocation(_rendererID, name.data());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat2(const glm::vec2& value, std::string_view name)
	{
		GLint location = glGetUniformLocation(_rendererID, name.data());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat(float value, std::string_view name)
	{
		GLint location = glGetUniformLocation(_rendererID, name.data());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformInt(int value, std::string_view name)
	{
		GLint location = glGetUniformLocation(_rendererID, name.data());
		glUniform1i(location, value);
	}
}