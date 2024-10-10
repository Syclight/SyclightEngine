#pragma once

#include <glad/glad.h>

#include "Syclight/Renderer/Buffer.h"

namespace syc
{
	class SYC_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float32* vertices, size1d size);
		virtual ~OpenGLVertexBuffer();

		virtual void_ Bind() const override;
		virtual void_ Unbind() const override;

	private:
		uint32 m_RendererID;
	};

	class SYC_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32* indices, size1d count);
		virtual ~OpenGLIndexBuffer();

		virtual void_ Bind() const override;
		virtual void_ Unbind() const override;
		virtual uint32 GetCount() const { return m_Count; }

	private:
		uint32 m_RendererID;
		uint32 m_Count;
	};
}