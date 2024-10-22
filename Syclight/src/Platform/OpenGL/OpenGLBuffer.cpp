#include "sycpch.h"
#include "OpenGLBuffer.h"

namespace syc
{

	//////////////////////////////////////////////////////////////////////////////////
	// VertexBuffer //////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float32* vertices, size1d size)
	{
		SYC_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		SYC_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void_ syc::OpenGLVertexBuffer::Bind() const
	{
		SYC_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void_ syc::OpenGLVertexBuffer::Unbind() const
	{
		SYC_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer ///////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, size1d count)
		:m_Count(count)
	{
		SYC_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		SYC_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void_ OpenGLIndexBuffer::Bind() const
	{
		SYC_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void_ OpenGLIndexBuffer::Unbind() const
	{
		SYC_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

