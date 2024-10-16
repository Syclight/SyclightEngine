#pragma once

#include "Syclight/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace syc
{
	class SYC_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void_ Bind() const override;
		virtual void_ Unbind() const override;

		void_ UploadUniforInt(const std::string& name, int32 values);
		void_ UploadUniforInt2(const std::string& name, const glm::ivec2& values);
		void_ UploadUniforInt3(const std::string& name, const glm::ivec3& values);
		void_ UploadUniforInt4(const std::string& name, const glm::ivec4& values);

		void_ UploadUniforFloat(const std::string& name, float32 values);
		void_ UploadUniforFloat2(const std::string& name, const glm::vec2& values);
		void_ UploadUniforFloat3(const std::string& name, const glm::vec3& values);
		void_ UploadUniforFloat4(const std::string& name, const glm::vec4& values);

		void_ UploadUniforMat3(const std::string& name, const glm::mat3& matrix);
		void_ UploadUniforMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};
}


