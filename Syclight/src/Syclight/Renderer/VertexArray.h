#pragma once

#include <memory>
#include "Syclight/Renderer/Buffer.h"

namespace syc
{
	class SYC_API VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void_ Bind() const = 0;
		virtual void_ Unbind() const = 0;

		virtual void_ AddVerrtexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void_ SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const = 0;

		static VertexArray* Create();
	};
}


