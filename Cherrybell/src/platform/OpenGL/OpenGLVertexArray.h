#pragma once
#include "core/renderer/VertexArray.h"
#include "core/renderer/Shader.h"

namespace CherryBell {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return _vertexBuffers; };
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return _indexBuffer; }
	private:
		RendererID _rendererID;
		std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
		std::shared_ptr<IndexBuffer> _indexBuffer;
	};
}