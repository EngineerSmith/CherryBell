#pragma once
#include "core/renderer/Buffer.h"
#include "core/renderer/RendererID.h"

namespace CherryBell {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() const override { return _layout; };
	private:
		RendererID _rendererID;
		BufferLayout _layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		uint32_t GetCount() const override { return _count; }
	private:
		RendererID _rendererID;
		uint32_t _count;
	};
}