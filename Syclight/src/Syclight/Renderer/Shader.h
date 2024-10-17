#pragma once

#include <string>
#include "Syclight/Common.h"

namespace syc
{
	class SYC_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void_ Bind() const = 0;
		virtual void_ Unbind() const = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	/*using ShaderRef = Ref<Shader>;*/
}



