#pragma once

#include "Syclight/Renderer/VertexArray.h"

namespace syc
{
	class SYC_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void_ Bind() const override;
		virtual void_ Unbind() const override;

		virtual void_ AddVerrtexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void_ SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const override { return m_IndexBuffer; };

	private:
		uint32 m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}


