#pragma once

#include <string>

#include <glm/glm.hpp>

namespace syc
{
	class SYC_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void_ Bind() const = 0;
		virtual void_ Unbind() const = 0;


		virtual void_ SetInt(const std::string& name, int32 value) = 0;
		virtual void_ SetIntArray(const std::string& name, int32* values, uint32_t count) = 0;
		virtual void_ SetFloat(const std::string& name, float32 value) = 0;
		virtual void_ SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void_ SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void_ SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	/*using ShaderRef = Ref<Shader>;*/

	class SYC_API ShaderLibrary
	{
	public:
		void_ Add(const Ref<Shader>& shader);
		void_ Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}



