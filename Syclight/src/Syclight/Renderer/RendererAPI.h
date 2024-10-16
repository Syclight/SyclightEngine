#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace syc
{
	class SYC_API RendererAPI
	{
	public:
		enum class SYC_API API
		{
			None = 0,
			OpenGL = 1
		};

	public:
		virtual void_ SetClearColor(const glm::vec4& color) = 0;
		virtual void_ Clear() = 0;

		virtual void_ DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}


