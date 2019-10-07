#pragma once
#include "core/renderer/VertexArray.h"
#include "core/renderer/RendererID.h"

namespace CherryBell {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return _vertexBuffers; };
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return _indexBuffer; }
	private:
		RendererID _rendererID;
		std::vector<Ref<VertexBuffer>> _vertexBuffers;
		Ref<IndexBuffer> _indexBuffer;
	};
}