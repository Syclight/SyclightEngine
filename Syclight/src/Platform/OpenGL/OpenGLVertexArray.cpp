#include "sycpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace syc
{
	static GLenum SYC_API ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case syc::ShaderDataType::Float:       return GL_FLOAT;
			case syc::ShaderDataType::Float2:      return GL_FLOAT;
			case syc::ShaderDataType::Float3:      return GL_FLOAT;
			case syc::ShaderDataType::Float4:      return GL_FLOAT;
			case syc::ShaderDataType::Mat3:        return GL_FLOAT;
			case syc::ShaderDataType::Mat4:        return GL_FLOAT;
			case syc::ShaderDataType::Int:         return GL_INT;
			case syc::ShaderDataType::Int2:        return GL_INT;
			case syc::ShaderDataType::Int3:        return GL_INT;
			case syc::ShaderDataType::Int4:        return GL_INT;
			case syc::ShaderDataType::Bool:        return GL_BOOL;
		}
		SYC_CORE_ASSERT(false, "Unkonwn ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void_ OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void_ OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void_ OpenGLVertexArray::AddVerrtexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		SYC_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout! Did you call 'VertexBuffer->SetLayout' before 'VertexArray->AddVerrtexBuffer'?");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32 index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void_*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void_ OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}