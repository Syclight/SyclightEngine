#include "sycpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace syc
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") 
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") 
			return GL_FRAGMENT_SHADER;

		SYC_CORE_ASSERT(false, "Unknown shader type {0}", type);

		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		SYC_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Complie(shaderSources);

		// 将文件名作为name
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc)
		:m_Name(name)
	{
		SYC_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Complie(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		SYC_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	void_ OpenGLShader::Bind() const
	{
		SYC_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void_ OpenGLShader::Unbind() const
	{
		SYC_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void_ OpenGLShader::SetInt(const std::string& name, const int32 value)
	{
		UploadUniformInt(name, value);
	}

	void_ OpenGLShader::SetFloat(const std::string& name, const float32 value)
	{
		UploadUniformFloat(name, value);
	}

	void_ OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void_ OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void_ OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void_ OpenGLShader::UploadUniformInt(const std::string& name, int32 values)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, values);
	}

	void_ OpenGLShader::UploadUniformInt2(const std::string& name, const glm::ivec2& values)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2i(location, values.x, values.y);
	}

	void_ OpenGLShader::UploadUniformInt3(const std::string& name, const glm::ivec3& values)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3i(location, values.x, values.y, values.z);
	}

	void_ OpenGLShader::UploadUniformInt4(const std::string& name, const glm::ivec4& values)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4i(location, values.x, values.y, values.z, values.w);
	}

	void_ OpenGLShader::UploadUniformFloat(const std::string& name, float32 values)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, values);
	}

	void_ OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void_ OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void_ OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void_ OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void_ OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		SYC_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		SYC_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			SYC_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		SYC_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char8* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			SYC_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			SYC_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specification!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = 
				source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() -1 : nextLinePos));
		}

		return shaderSources;
	}
	void_ OpenGLShader::Complie(std::unordered_map<GLenum, std::string>& shaderSources)
	{
		SYC_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs;
		/*std::array<GLenum, 2>*/
		glShaderIDs.reserve(shaderSources.size());
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isComplied = GL_FALSE;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isComplied);
			if (isComplied == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				SYC_CORE_ERROR("{0}", infoLog.data());
				SYC_CORE_ASSERT(false, " Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			SYC_CORE_ERROR("{0}", infoLog.data());
			SYC_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
		}

		m_RendererID = program;
	}
}