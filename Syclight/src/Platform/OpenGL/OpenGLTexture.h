#pragma once

#include "Syclight/Renderer/Texture.h"

namespace syc
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32 GetWidth() const override { return m_Width; };
		virtual uint32 GetHeight() const override { return m_Height; };

		virtual void_ Bind(uint32 slot = 0) const override;

	private:
		std::string m_Path;
		uint32 m_Width, m_Height;
		uint32 m_RendererID;
	};
}



