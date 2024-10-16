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

		virtual void_ AddVerrtexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void_ SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffers() const override { return m_IndexBuffer; };

	private:
		uint32 m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}


