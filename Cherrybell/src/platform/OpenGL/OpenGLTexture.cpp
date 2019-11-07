#include "cbpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace CherryBell {
	OpenGLTexture2D::OpenGLTexture2D(std::string_view path)
		: _path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.data(), &width, &height, &channels, 0);
		CB_CORE_ASSERT(data, "Failed to load image!");

		_width = width; 
		_height = height;

		glGenTextures(1, &_rendererID);
		glBindTexture(GL_TEXTURE_2D, _rendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		switch (channels)
		{
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		default:
			stbi_image_free(data);
			CB_CORE_ASSERT(false, "Unsupported texture channels format!");
			break;
		}
		
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_rendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		//glBindTextureUnit(slot, _rendererID);
		glBindTexture(GL_TEXTURE_2D, _rendererID);
		glActiveTexture(slot);
	}
}