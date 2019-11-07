#pragma once
#include "core/renderer/Texture.h"
#include "core/renderer/RendererID.h"

#include <glad/glad.h>

namespace CherryBell {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(std::string_view path);
		~OpenGLTexture2D();

		uint32_t GetWidth() const override { return _width; };
		uint32_t GetHeight() const override { return _height; };

		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot = 0) const override;
	private:
		std::string _path;
		uint32_t _width = 0u, _height = 0u;
		RendererID _rendererID;

		GLenum _internalFormat, _dataFormat;
	};
}