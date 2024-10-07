#pragma once

#include <string>
#include "Syclight/Common.h"

namespace syc
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void_ Bind() const;
		void_ Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}



