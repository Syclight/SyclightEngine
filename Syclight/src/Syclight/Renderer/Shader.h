#pragma once

#include <string>
#include <glm/glm.hpp>
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

		void_ UploadUniforMat4(const std::string name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};
}



