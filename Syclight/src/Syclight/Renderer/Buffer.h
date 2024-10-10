#pragma once

#include "Syclight/Common.h"

namespace syc
{
	class SYC_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void_ Bind() const = 0;
		virtual void_ Unbind() const = 0;

		static VertexBuffer* Create(float32* vertices, size1d size);
	};

	class SYC_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void_ Bind() const = 0;
		virtual void_ Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static IndexBuffer* Create(uint32* indices, size1d count);
	};
}