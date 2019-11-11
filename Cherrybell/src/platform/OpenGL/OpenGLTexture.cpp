#include "cbpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace CherryBell {
	constexpr GLenum TextureSlotToEnum(uint32_t slot)
	{
#define GLenumSlot(slot) case slot: return GL_TEXTURE##slot
		switch (slot)
		{
			GLenumSlot(0);
			GLenumSlot(1);
			GLenumSlot(2);
			GLenumSlot(3);
			GLenumSlot(4);
			GLenumSlot(5);
			GLenumSlot(6);
			GLenumSlot(7);
			GLenumSlot(8);
			GLenumSlot(9);
			GLenumSlot(10);
			GLenumSlot(11);
			GLenumSlot(12);
			GLenumSlot(13);
			GLenumSlot(14);
			GLenumSlot(15);
			GLenumSlot(16);
			GLenumSlot(17);
			GLenumSlot(18);
			GLenumSlot(19);
			GLenumSlot(20);
			GLenumSlot(21);
			GLenumSlot(22);
			GLenumSlot(23);
			GLenumSlot(24);
			GLenumSlot(25);
			GLenumSlot(26);
			GLenumSlot(27);
			GLenumSlot(28);
			GLenumSlot(29);
			GLenumSlot(30);
			GLenumSlot(31);
		default:
			CB_CORE_ASSERT(false, "Unsupported texture slot: {0}", slot);
			return GL_TEXTURE0;
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: _width(width), _height(height), _internalFormat(GL_RGBA8), _dataFormat(GL_RGBA)
	{
		glGenTextures(1, &_rendererID);
		glBindTexture(GL_TEXTURE_2D, _rendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _dataFormat, GL_UNSIGNED_BYTE, nullptr);
	}

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
			_internalFormat = GL_RGB8;
			_dataFormat = GL_RGB;
			break;
		case 4:
			_internalFormat = GL_RGBA8;
			_dataFormat = GL_RGBA;
			break;
		default:
			stbi_image_free(data);
			CB_CORE_ASSERT(false, "Unsupported texture channels format!");
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _dataFormat, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_rendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = _dataFormat == GL_RGBA ? 4 : _dataFormat == GL_RGB ? 3 : -1;
		CB_CORE_ASSERT(size == _width * _height * bpp, "Data must be entire texture!");
		glBindTexture(GL_TEXTURE_2D, _rendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTexture(GL_TEXTURE_2D, _rendererID);
		glActiveTexture(TextureSlotToEnum(slot));
	}
}
