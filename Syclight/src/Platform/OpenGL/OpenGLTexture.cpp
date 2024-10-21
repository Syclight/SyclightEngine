#include "sycpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace syc
{
	OpenGLTexture2D::OpenGLTexture2D(uint32 width, uint32 height, uint32 type)
		:m_Width(width), m_Height(height)
	{
		GLenum interalFormat = 0, dataFormat = 0;

		if (type == 4)
		{
			interalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (type == 3)
		{
			interalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InteralFormat = interalFormat;
		m_DataFormat = dataFormat;

		SYC_ASSERT(m_InteralFormat & m_DataFormat, "Image format not supported!");
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InteralFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		int32 width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		SYC_CORE_ASSERT(data, "Fail to load image!");
		m_Width = width;
		m_Height = height;

		GLenum interalFormat = 0, dataFormat = 0;

		if (channels == 4)
		{
			interalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			interalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InteralFormat = interalFormat;
		m_DataFormat = dataFormat;

		SYC_ASSERT(m_InteralFormat & m_DataFormat, "Image format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InteralFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void_ OpenGLTexture2D::SetData(void_* data, uint32 size)
	{
		uint32 bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		SYC_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!")
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void_ OpenGLTexture2D::Bind(uint32 slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}