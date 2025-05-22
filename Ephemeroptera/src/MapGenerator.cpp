#include "MapGenerator.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

RPGMap2D::RPGMap2D(std::string mapFilePath, std::string mapSheetPath)
{
    Init(mapFilePath);
    // m_MapSheets = syc::Texture2D::Create("assets/textures/RPGpack_sheet_2X.png");
    m_MapSheets = syc::Texture2D::Create(mapSheetPath);
    m_TextureGrass = syc::SubTexture2D::CreateFromCoords(m_MapSheets, { 1, 11 }, { 128.0f, 128.0f });
    m_TextureEarth = syc::SubTexture2D::CreateFromCoords(m_MapSheets, { 6, 11 }, { 128.0f, 128.0f });
    m_TextureWater = syc::SubTexture2D::CreateFromCoords(m_MapSheets, { 11, 11 }, { 128.0f, 128.0f });
    m_TextureTree = syc::SubTexture2D::CreateFromCoords(m_MapSheets, { 2, 1 }, { 128.0f, 128.0f }, { 1, 2 });
	m_TextureFence = syc::SubTexture2D::CreateFromCoords(m_MapSheets, { 0, 6 }, { 128.0f, 128.0f });
}

//void RPGMap2D::DrawBase(const glm::vec3& cameraPos, const glm::vec2& viewSize)
//{
//    const size_t redundantAround = 3;
//
//    // 生成地形
//    for (size_t i = 0; i < m_MapDescStr.size(); i++) {
//        if (i < cameraPos.y - viewSize.y / 2 - redundantAround || i  > cameraPos.y + viewSize.y / 2 + redundantAround) continue;
//        std::string line = m_MapDescStr[i];
//        for (size_t j = 0; j < line.size(); j++) {
//            if (j < cameraPos.x - viewSize.x / 2 - redundantAround || j > cameraPos.x + viewSize.x / 2 + redundantAround) continue;
//            char ch = line[j];
//           /* int x = i - 18;
//            int y = j - 10;*/
//            int x = j;
//            int y = i;
//            switch (ch) {
//            case '0':
//                syc::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, m_TextureWater);
//                break;
//            case '1':
//            case '2':
//                syc::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, m_TextureGrass);
//                break;
//            case '3':
//                syc::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, m_TextureEarth);
//                break;
//            case '9':
//                syc::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, {0.0f, 0.0f, 0.0f, 1.0f});
//                break;
//            default:
//                SYC_ERROR("Runtime ERROR: Unknown char \"{0}\"", ch);
//                return;
//            }
//        }
//    }
//}

void RPGMap2D::DrawBase(const glm::vec3& cameraPos, const glm::vec2& viewSize)
{
    const size_t redundantAround = 3;

    // 反转摄像机的Y坐标
    float adjustedCameraY = m_MapDescStr.size() - 1 - cameraPos.y;

    for (size_t i = 0; i < m_MapDescStr.size(); i++) {
        // 使用反转后的摄像机Y坐标计算可见范围
        if (i < adjustedCameraY - viewSize.y / 2 - redundantAround || i > adjustedCameraY + viewSize.y / 2 + redundantAround) continue;
        std::string line = m_MapDescStr[i];
        for (size_t j = 0; j < line.size(); j++) {
            if (j < cameraPos.x - viewSize.x / 2 - redundantAround || j > cameraPos.x + viewSize.x / 2 + redundantAround) continue;
            char ch = line[j];
            int x = j;
            int y = m_MapDescStr.size() - 1 - i; // 反转Y坐标
            switch (ch) {
            case '0':
                syc::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, m_TextureWater);
                break;
            case '1':
            case '2':
            case '6':
                syc::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, m_TextureGrass);
                break;
            case '3':
                syc::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, m_TextureEarth);
                break;
            case '9':
                syc::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f });
                break;
            default:
                SYC_ERROR("Runtime ERROR: Unknown char \"{0}\"", ch);
                return;
            }
        }
    }
}

//void RPGMap2D::DrawAddition(const glm::vec3& cameraPos, const glm::vec2& viewSize)
//{
//    const size_t redundantAround = 3;
//
//    // 添加树，从上到下渲染（从大 i 到小 i）
//    for (size_t i = m_MapDescStr.size(); i-- > 0; ) {
//        if (i < cameraPos.y - viewSize.y / 2 - redundantAround || i > cameraPos.y + viewSize.y / 2 + redundantAround) continue;
//        std::string line = m_MapDescStr[i];
//        for (size_t j = 0; j < line.size(); j++) {
//            if (j < cameraPos.x - viewSize.x / 2 - redundantAround || j > cameraPos.x + viewSize.x / 2 + redundantAround) continue;
//            if (line[j] == '2')
//            {
//                /*if (i > 0 && m_MapDescStr[i-1][j] == '2')
//                {
//                    continue;
//                }*/
//                // 计算 z 值：让下方的树（较小的 i）有较小的 z 值
//                float z = 0.8f + (0.001f * (m_MapDescStr.size() - 1 - i));
//                syc::Renderer2D::DrawQuad({ j, i, z }, { 1.0f, 2.0f }, m_TextureTree);
//            }
//        }
//    }
//}

void RPGMap2D::DrawAddition(const glm::vec3& cameraPos, const glm::vec2& viewSize)
{
    const size_t redundantAround = 3;

    // 反转摄像机的Y坐标
    float adjustedCameraY = m_MapDescStr.size() - 1 - cameraPos.y;

    // 添加树，从小到大渲染（从小 i 到大 i），以确保下方的树（较大 i，较小 y）后渲染
    for (size_t i = 0; i < m_MapDescStr.size(); i++) {
        if (i < adjustedCameraY - viewSize.y / 2 - redundantAround || i > adjustedCameraY + viewSize.y / 2 + redundantAround) continue;
        std::string line = m_MapDescStr[i];
        for (size_t j = 0; j < line.size(); j++) {
            if (j < cameraPos.x - viewSize.x / 2 - redundantAround || j > cameraPos.x + viewSize.x / 2 + redundantAround) continue;
            if (line[j] == '2')
            {
                /*if (i > 0 && m_MapDescStr[i-1][j] == '2')
                {
                    continue;
                }*/
                // 反转Y坐标
                int y = m_MapDescStr.size() - 1 - i;
                // 计算 z 值：让下方的树（较小的 y，较大的 i）有较小的 z 值
                float z = 0.8f + (0.001f * i);
                syc::Renderer2D::DrawQuad({ j, y, z }, { 1.0f, 2.0f }, m_TextureTree);
            }
        }
    }
}

//const std::vector<glm::vec2> RPGMap2D::GetCollisionPosition()
//{
//    std::vector<glm::vec2> rects;
//    for (size_t i = 0; i < m_MapDescStr.size(); i++) {
//        std::string line = m_MapDescStr[i];
//        for (size_t j = 0; j < line.size(); j++) {
//            char ch = line[j];
//            if (ch == '2')
//            {
//                //if (i > 0 && m_MapDescStr[i - 1][j] == ch) continue;
//                rects.push_back({ static_cast<float>(j), static_cast<float>(i - 0.5) });
//            }
//            if (ch == '0' || ch == '9')
//            {
//                rects.push_back({ static_cast<float>(j), static_cast<float>(i) });
//            }
//        }
//    }
//    return rects;
//}

const std::vector<glm::vec2> RPGMap2D::GetCollisionPosition()
{
    std::vector<glm::vec2> rects;
    for (size_t i = 0; i < m_MapDescStr.size(); i++) {
        std::string line = m_MapDescStr[i];
        for (size_t j = 0; j < line.size(); j++) {
            char ch = line[j];
			float y = static_cast<float>(m_MapDescStr.size() - 1 - i); // 反转Y坐标
            if (ch == '2')
            {
                rects.push_back({ static_cast<float>(j), y + 0.5f });
            }
            if (ch == '0' || ch == '9')
            {
                rects.push_back({ static_cast<float>(j), y });
            }
        }
    }
    return rects;
}

bool RPGMap2D::IsGrass(const glm::vec2& pos)
{
	return GetType(pos) == '1';
}

bool RPGMap2D::IsWater(const glm::vec2& pos)
{
    return GetType(pos) == '0';
}

bool RPGMap2D::IsCollision(const glm::vec2& pos)
{
    char ch = GetType(pos);
    return ch == '0' || ch == '2' || ch == '9' || ch == '6';
}

void RPGMap2D::Init(std::string mapFilePath)
{
    fs::path filepath = mapFilePath;
    if (!fs::exists(filepath)) {
        SYC_ERROR("Runtime ERROR: File \"{0}\" is not exist!", mapFilePath);
        return;
    }

    std::ifstream file(filepath);
    if (!file) {
        SYC_ERROR("Runtime ERROR: File \"{0}\" can not be opened!", filepath);
        return;
    }

    std::string line;
	size_t lineCount = 0;
    while (std::getline(file, line)) {
        if (lineCount == 0)
        {
			size_t splitTokenPos = line.find('x');
			m_MapWidth = std::stoi(line.substr(0, splitTokenPos));
			m_MapHeight = std::stoi(line.substr(splitTokenPos + 1));
        }
        else
        {
            m_MapDescStr.emplace_back(line);
        }
		lineCount++;
    }

    file.close();
}

char RPGMap2D::GetType(const glm::vec2& pos)
{
    // 反转Y坐标
    glm::vec2 adjustedPos = { pos.x, static_cast<float>(m_MapDescStr.size() - 1 - pos.y) };
    //glm::vec2 adjustedPos = { pos.x, pos.y };
    // 检查坐标是否在地图范围内
    if (adjustedPos.x < 0 || adjustedPos.y < 0 ||
        adjustedPos.x >= m_MapDescStr[0].size() || adjustedPos.y >= m_MapDescStr.size())
    {
        return 'a'; // 超出地图范围
    }
    return m_MapDescStr[adjustedPos.y][adjustedPos.x];
}
