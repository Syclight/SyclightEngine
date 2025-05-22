#pragma once

#include <Syclight.h>

#include <map>
#include <string>
#include <set>

#include "Actor.h"
#include "MapGenerator.h"
#include "Datatype.hpp"

# define ACTOR_EX(_t, _k) std::dynamic_pointer_cast<_t>(m_Actors[_k])

enum LevelStatus
{
	Gaming = 0,
	Timeout,
	End,
	Win,
};

class Level
{
public:
	Level() {};
	void Init();

	void Update(syc::Timestep ts, syc::OrthographicCameraController& cameraController);
	void Draw(const glm::vec3& cameraPos, const glm::vec2& viewSize);
	void DrawImGuiLayer(const glm::vec3& cameraPos, const glm::vec2& viewSize, const ImGUIAssets& imguiAsset);

	LevelStatus GetLevelStatus() const { return m_LevelStatus; }

private:
	std::vector<syc::Ref<syc::SubTexture2D>> LoadSubTexture(const syc::Ref<syc::Texture2D>& spriteSheet, size_t maxIndex = 6);
	void LoadResource();
	const glm::vec3 CalCameraPos(const glm::vec3& newPos, const glm::vec4& mapSize);
	const static void KeepRectInMap2D(
		glm::vec2& playerPos, 
		const glm::vec2& playerSize, 
		const glm::vec4& mapBounds);
	void DrawImGuiProgressBar(float progress, const glm::vec2& pos, const glm::vec2& size,
		const glm::vec4& bgColor, const glm::vec4& progressColor);
	void DrawImGuiProgressBar(float progress, const glm::vec2& pos, const glm::vec2& size,
		const glm::vec4& bgColor, const glm::vec4& progressColor, const glm::vec4& frameColor);
	void DrawImGuiHpBar(glm::vec2 pos, glm::vec2 size);
	void DrawImGuiTimeBar(glm::vec2 pos);
	void DrawImGuiText(const std::string& text, const glm::vec2& pos, const glm::vec4& color, ImFont* font, float size);

	void UpdateGaming(syc::Timestep ts, syc::OrthographicCameraController& cameraController);
	void UpdateTimeout(syc::Timestep ts);

	void DrawGameing(const glm::vec3& cameraPos, const glm::vec2& viewSize);

	syc::Ref<Player> GetPlayer();
	std::string GetCurrentPlayerKey() const;
	std::string GenNewPlayer(const glm::vec3& pos);
	std::string GenNewPlayerFromOld();
	void MoveNPCRandom(const std::string& key);
	void MoveNPCOutCameraRandom(const std::string& key, syc::OrthographicCameraController cameraC);
	void MoveNPC(const std::string& key, const glm::vec3& pos);

	bool InRect(glm::vec4 rect, glm::vec2 pos);

	RPGMap2D m_Map2d = RPGMap2D("assets/bin/map.bin", "assets/textures/RPGpack_sheet_2X.png");
	std::unordered_map<std::string, syc::Ref<syc::Texture2D>> m_SpriteSheets;
	std::map<std::string, syc::Ref<Actor>> m_Actors;
	const std::vector<glm::vec2> m_Map2dCollisionPos = m_Map2d.GetCollisionPosition();

	LevelStatus m_LevelStatus = LevelStatus::Gaming;

	size_t m_ActorCount = 0;
	float m_LastTime = 0.0f;
	float m_CurrentTime = 0.0f;
	const float m_MaxTime = 180.0f;
	float m_Time = m_MaxTime;

	ImDrawList* m_ImDrawList = nullptr;

	// 相机抖动参数
	bool m_IsShaking = false; // 是否正在抖动
	float m_ShakeDuration = 0.5f;    // 抖动剩余时间
	float m_ShakeMagnitude = 0.2f;   // 抖动幅度
	glm::vec3 m_OriginalPosition = { 0.0f, 0.0f, 0.0f }; // 抖动开始前的相机位置

	// 震飞相关成员
	bool m_IsKnockedBack = false;           // 是否处于震飞状态
	float m_KnockbackDuration = 0.0f;       // 震飞剩余时间
	float m_KnockbackDistance = 5.0f;       // 震飞总距离
	glm::vec2 m_KnockbackDirection = { 0.0f, 0.0f }; // 震飞方向
	std::string m_CollisionActorKey = ""; // 碰撞的墙名称

	// 碰撞npc
	bool m_IsCollisionNPC = false;
	std::string m_CollisionNPCKey = "";

	//玩家相关参数
	int m_Generation = -1;

	struct Vec2Compare 
	{
		bool operator()(const glm::vec2& a, const glm::vec2& b) const
		{
			if (a.x != b.x) return a.x < b.x;
			return a.y < b.y;
		}
	};
    std::set<glm::vec2, Vec2Compare> m_OldPlayerPosSet;

	//NPC参数
	std::set<glm::vec2, Vec2Compare> m_TomebstonePosSetNPC;
	
};
