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

		virtual void_ AddVerrtexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void_ SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffers() const = 0;

		static VertexArray* Create();
	};
}


