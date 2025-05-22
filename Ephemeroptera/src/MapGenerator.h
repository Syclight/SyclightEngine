#pragma once

#include <Syclight.h>

#include <string>

//struct QuadData {
//	glm::vec3 position;
//	glm::vec2 size;
//	syc::Ref<syc::SubTexture2D> texture;
//};

class RPGMap2D
{
public:
	RPGMap2D(std::string mapFilePath, std::string mapSheetPath);
	~RPGMap2D() {};
	void DrawBase(const glm::vec3& cameraPos, const glm::vec2& viewSize);
	void DrawAddition(const glm::vec3& cameraPos, const glm::vec2& viewSize);
	//const std::vector<std::vector<glm::vec2>> GetCollisionRects();
	const std::vector<glm::vec2> GetCollisionPosition();
	const std::pair<size_t, size_t> GetMapSize() { return { m_MapWidth, m_MapHeight }; }
	bool IsGrass(const glm::vec2& pos);
	bool IsWater(const glm::vec2& pos);
	bool IsCollision(const glm::vec2& pos);
	char GetType(const glm::vec2& pos);

private:
	void Init(std::string mapFilePath);

	std::vector<std::string> m_MapDescStr;
	syc::Ref<syc::Texture2D> m_MapSheets = nullptr;
	syc::Ref<syc::SubTexture2D> m_TextureTree = nullptr;
	syc::Ref<syc::SubTexture2D> m_TextureWater = nullptr;
	syc::Ref<syc::SubTexture2D> m_TextureGrass = nullptr;
	syc::Ref<syc::SubTexture2D> m_TextureEarth = nullptr;
	syc::Ref<syc::SubTexture2D> m_TextureFence = nullptr;

	//bool m_isDraw = false;
	size_t m_MapWidth = 0;
	size_t m_MapHeight = 0;
};

