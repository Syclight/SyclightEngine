#pragma once

#include "Syclight/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace syc
{
	class SYC_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void_ Bind() const override;
		virtual void_ Unbind() const override;

		virtual void_ SetInt(const std::string& name, const int32 value) override;
		virtual void_ SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void_ SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void_ SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void_ UploadUniformInt(const std::string& name, int32 values);
		void_ UploadUniformInt2(const std::string& name, const glm::ivec2& values);
		void_ UploadUniformInt3(const std::string& name, const glm::ivec3& values);
		void_ UploadUniformInt4(const std::string& name, const glm::ivec4& values);

		void_ UploadUniformFloat(const std::string& name, float32 values);
		void_ UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void_ UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void_ UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void_ UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void_ UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void_ Complie(std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}


