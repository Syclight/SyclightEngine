#include "sycpch.h"
#include "SubTexture2D.h"

namespace syc
{
	SubTexture2D::SubTexture2D()
		: m_Texture(nullptr)
	{
		m_TexCoords[0] = { 0.0f, 0.0f };
		m_TexCoords[1] = { 0.0f, 0.0f };
		m_TexCoords[2] = { 0.0f, 0.0f };
		m_TexCoords[3] = { 0.0f, 0.0f };
	}
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y};
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * cellSize.x) / texture->GetWidth(), (coords.y * cellSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };
		return CreateRef<SubTexture2D>(texture, min, max);
	}

	void_ SubTexture2D::Inversion()
	{
		glm::vec2 temp = m_TexCoords[0];
		m_TexCoords[0] = m_TexCoords[1];
		m_TexCoords[1] = temp;
		temp = m_TexCoords[2];
		m_TexCoords[2] = m_TexCoords[3];
		m_TexCoords[3] = temp;
	}

	Ref<SubTexture2D> SubTexture2D::Copy() const
	{
		syc::Ref<SubTexture2D> texture = CreateRef<SubTexture2D>();
		texture->m_Texture = m_Texture;
		for (size_t i = 0; i < 4; i++)
		{
			texture->m_TexCoords[i] = m_TexCoords[i];
		}
		return texture;
	}
}