#include "Level.h"


#include <imgui/imgui.h>

void Level::Init()
{
	LoadResource();

	syc::Random::Init();

	glm::vec3 mainPos = { 50.0f, 10.0f, 0.99f };
	GenNewPlayer(mainPos);
	//m_Actors["main"] = syc::CreateRef<Player>(LoadSubTexture(m_SpriteSheets["manSubtexture"]), mainPos);
	m_ActorCount++;

	glm::vec3 maskPos = { 0.0f, 0.0f, -1.0f };
	glm::vec2 maskSize = { 1.0f, 1.0f };
	glm::vec3 maskColor = { 0.0f, 0.0f, 0.0f };
	m_Actors["mask"] = syc::CreateRef<Mask>(maskPos, maskSize, maskColor);

	for (size_t i = 0; i < 7; i++)
	{
		glm::vec3 pos = { 0.0f , 0.0f, 0.9f };
		std::string key = (std::ostringstream() << "woman" << std::to_string(m_ActorCount)).str();
		m_Actors[key] = syc::CreateRef<NPC>(LoadSubTexture(m_SpriteSheets["womanSubtexture"]), pos);
		MoveNPCRandom(key);
		m_ActorCount++;
	}

	//for (size_t i = 0; i < 7; i++)
	//{
	//	/*float x = syc::Random::Float() >= 0.5 ? 1.0f : -1.0f;
	//	float y = syc::Random::Float() >= 0.5 ? 1.0f : -1.0f;
	//	glm::vec3 pos = { syc::Random::Float() * x * 10.0f, syc::Random::Float() * y * 10.0f, 1.0f };*/
	//	glm::vec3 pos = { i * -1.4f + 52.0f, -7.0f + 52.0f, 0.5f };
	//	m_Actors[(std::ostringstream() << "man" << std::to_string(m_ActorCount)).str()] = syc::CreateRef<NPC>(LoadSubTexture(m_SpriteSheets["manSubtexture"]), pos);
	//	m_ActorCount++;
	//}

	for (size_t i = 0; i < 7; i++)
	{
		glm::vec3 pos = { i + 49.0f, 93.0f, 0.9f };
		glm::vec2 size = { 1.0f, 1.0f };
		m_Actors[(std::ostringstream() << "stone" << std::to_string(m_ActorCount)).str()] = syc::CreateRef<Wall>(LoadSubTexture(m_SpriteSheets["stoneSubtexture"], 5), pos, size);
		m_ActorCount++;
	}

	for (size_t i = 0; i < m_Map2dCollisionPos.size(); i++)
	{
		glm::vec2 pos2D = m_Map2dCollisionPos[i];
		glm::vec3 pos = { pos2D.x, pos2D.y, 0.0f };
		glm::vec2 size = { 1.0f, 1.0f };
		m_Actors[(std::ostringstream() << "tree" << std::to_string(m_ActorCount)).str()] = syc::CreateRef<Collider>(pos, size);
		m_ActorCount++;
	}

	//SYC_TRACE(m_Map2d.GetType({0, 99})); //3
	//SYC_TRACE(m_Map2d.GetType({79, 99})); //2
	//SYC_TRACE(m_Map2d.GetType({0, 0})); //6
	//SYC_TRACE(m_Map2d.GetType({79, 0})); //1
}

void Level::Update(syc::Timestep ts, syc::OrthographicCameraController& cameraController)
{
	switch (m_LevelStatus)
	{
	case Gaming: UpdateGaming(ts, cameraController); break;
	case Timeout: break;
	case End:
		break;
	case Win:
		break;
	default:
		break;
	}
}

void Level::UpdateGaming(syc::Timestep ts, syc::OrthographicCameraController& cameraController)
{
	//计算是否过了一秒钟
	m_CurrentTime += ts;
	if (m_CurrentTime - m_LastTime >= 1.0f)
	{
		m_Time -= 1.0f;
		m_LastTime = m_CurrentTime;
		if (m_Time <= 0.0f)
		{
			m_LevelStatus = LevelStatus::Timeout;
			m_Time = m_MaxTime; // 3分钟
		}
	}

	// 记录未抖动的相机原始位置
	if (!m_IsShaking)
	{
		m_OriginalPosition = cameraController.GetCameraPos();
	}

	glm::vec4 mainRect = GetPlayer()->GetRect();
	glm::vec2 mainRects[4] = {
		{mainRect.x, mainRect.y}, // 左上角
		{mainRect.x + mainRect.z, mainRect.y}, // 右上角
		{mainRect.x + mainRect.z, mainRect.y + mainRect.w}, // 右下角
		{mainRect.x, mainRect.y + mainRect.w} }; // 左下角
	glm::vec4 mainVelocity = GetPlayer()->GetVelocity();
	GetPlayer()->Update(ts);
	glm::vec3 playerPos = GetPlayer()->GetPos();

	// 限制主角在地图范围内
	glm::vec2 playerPos2D = { playerPos.x, playerPos.y };
	glm::vec2 playerSize = { mainRect.z, mainRect.w };
	std::pair mapSize = m_Map2d.GetMapSize();
	KeepRectInMap2D(playerPos2D, playerSize, { mapSize.second, mapSize.first, 0, 0 });
	GetPlayer()->SetPos(playerPos2D.x, playerPos2D.y, playerPos.z);

	//syc::Ref<Player> player = std::dynamic_pointer_cast<Player>(m_Actors["main"]);

	//=== 碰撞相关 开始 ==============================================
	for (const auto& [key, npc] : m_Actors)
	{
		if (key.find("main") != std::string::npos) { continue; }
		if (!npc->GetActive()) { continue; }
		//在主角周围进行碰撞检测
		
		npc->Update(ts);

		glm::vec4 npcRect = npc->GetRect();
		glm::vec2 npcRects[4] = {
			{npcRect.x, npcRect.y},
			{npcRect.x + npcRect.z, npcRect.y},
			{npcRect.x + npcRect.z, npcRect.y + npcRect.w},
			{npcRect.x, npcRect.y + npcRect.w} };
		if (npc->GetPos().x > playerPos.x + 3.0f && npc->GetPos().x < playerPos.x - 3.0f &&
			npc->GetPos().y > playerPos.y + 3.0f && npc->GetPos().y < playerPos.y - 3.0f)
		{
			continue;
		}

		syc::CollisionInfo info = syc::PhysicsTools::SATCollisionTestInfo(mainRects, npcRects);

		if (info.Collided)
		{
			//SYC_TRACE("发生了碰撞：{}", key);

			if (key.find("woman") != std::string::npos)
			{
				m_IsCollisionNPC = true;
				m_CollisionNPCKey = key;
			}

			if (key.find("stone") != std::string::npos)
			{
				m_CollisionActorKey = key;

				// 触发抖动
				m_IsShaking = true;
				m_ShakeDuration = 0.2f; // 重置抖动时间
				m_ShakeMagnitude = 0.2f;

				// 触发震飞
				m_IsKnockedBack = true;
				m_KnockbackDuration = 0.2f; // 震飞 0.2 秒
				m_KnockbackDistance = 1.0f; // 震飞 1.0 单位
				m_KnockbackDirection = info.Direction; // 反方向震飞
			}

			//glm::vec3 npcPos = npc->GetPos();
			// 计算调整量
			glm::vec2 adjustment = info.Direction * info.Depth;
			/*syc::Ref<Player> player = GetPlayer();*/
			GetPlayer()->SetPos(
				GetPlayer()->GetPos().x + adjustment.x,
				GetPlayer()->GetPos().y + adjustment.y
			);
		}
	}

	// 处理抖动
	if (m_IsShaking)
	{
		if (m_ShakeDuration > 0.0f)
		{
			// 计算当前抖动幅度（线性衰减）
			float currentMagnitude = m_ShakeMagnitude * (m_ShakeDuration / 0.2f);
			// 随机偏移（仅影响 x 和 y）
			float offsetX = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * currentMagnitude;
			float offsetY = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * currentMagnitude;
			// 应用偏移
			glm::vec3 shakePos = m_OriginalPosition + glm::vec3(offsetX, offsetY, 0.0f);
			cameraController.SetCameraPos(shakePos);
			// 减少抖动时间
			m_ShakeDuration -= ts;
		}
		else
		{
			// 抖动结束，恢复原始位置
			cameraController.SetCameraPos(m_OriginalPosition);

			//syc::Ref<Wall> wall = std::dynamic_pointer_cast<Wall>(m_Actors[m_CollisionActorKey]);
			syc::Ref<Wall> wall = ACTOR_EX(Wall, m_CollisionActorKey);
			wall->SetHP(wall->GetHP() - 2);

			m_IsShaking = false;
		}
	}

	// 处理震飞
	if (m_IsKnockedBack)
	{
		if (m_KnockbackDuration > 0.0f)
		{
			// 计算震飞速度（距离 / 时间）
			float knockbackSpeed = m_KnockbackDistance / 0.2f; // 总距离除以总时间
			glm::vec2 knockbackVelocity = m_KnockbackDirection * knockbackSpeed;
			// 更新主角位置
			glm::vec3 currentPos = GetPlayer()->GetPos();
			glm::vec3 newPos = currentPos + glm::vec3(knockbackVelocity * (float)ts, 0.0f);
			GetPlayer()->SetPos(newPos.x, newPos.y, newPos.z);
			// 减少震飞时间
			m_KnockbackDuration -= ts;
		}
		else
		{
			// 震飞结束，恢复正常状态
			m_IsKnockedBack = false;
			//syc::Ref<Player> player = GetPlayer();
			float playerHp = GetPlayer()->SetHp(GetPlayer()->GetHp() - 10.0f);
			if (playerHp <= 0.0f)
			{
				GetPlayer()->Dead();
				m_LevelStatus = LevelStatus::End;
			}
		}
	}

	if (m_IsCollisionNPC)
	{
		//syc::Ref<NPC> npc = std::dynamic_pointer_cast<NPC>(m_Actors[m_CollisionNPCKey]);
		syc::Ref<NPC> npc = ACTOR_EX(NPC, m_CollisionNPCKey);
		glm::vec3 posNPC = npc->GetPos();
#if _DEBUG
		/*MoveNPCRandom(m_CollisionNPCKey);
		const syc::OrthographicCameraBounds& bound = cameraController.GetBounds();
		SYC_TRACE("cameraBound:({0}, {1}, {2}, {3})", bound.Top, bound.Bottom, bound.GetWidth(), bound.GetHeight());*/
		MoveNPCOutCameraRandom(m_CollisionNPCKey, cameraController);
#else // _DEBUG
		MoveNPCOutCameraRandom(m_CollisionNPCKey, cameraController);
#endif
		// 处理玩家逻辑
		//syc::Ref<Player> player = std::dynamic_pointer_cast<Player>(m_Actors[GetCurrentPlayerKey()]);
		syc::Ref<Player> player = ACTOR_EX(Player, GetCurrentPlayerKey());
		glm::vec3 playerPos = GetPlayer()->GetPos();
		m_Actors[GetCurrentPlayerKey()]->SetPos(playerPos.x, playerPos.y, playerPos.z - 0.1);
		m_OldPlayerPosSet.insert({ playerPos.x, playerPos.y });
		player->Turn('f');
		player->Dead();
		m_TomebstonePosSetNPC.insert({ posNPC.x, posNPC.y });
		//m_Actors[GetCurrentPlayerKey()]->Disable();
		//m_Actors[GetCurrentPlayerKey()]->Invisible();

		glm::vec3 newPos = { posNPC.x + 1.0f, posNPC.y, playerPos.z};
		while (m_Map2d.IsCollision(newPos) || newPos == playerPos)
		{
			// 在newPos的上下左右四个方向上随机生成一个新的位置
			float xOffset = syc::Random::Float() * 2.0f - 1.0f; // 随机生成 -1.0 到 1.0 之间的值
			float yOffset = syc::Random::Float() * 2.0f - 1.0f; // 随机生成 -1.0 到 1.0 之间的值
			newPos.x = static_cast<int>(newPos.x + xOffset);
			newPos.y = static_cast<int>(newPos.y + yOffset);
		}
		GenNewPlayer(newPos);
		//GenNewPlayerFromOld();
		m_IsCollisionNPC = false;
	}

	//=== 碰撞相关 结束 ==============================================

	// 地图跟随主角移动
	syc::OrthographicCameraBounds bound = cameraController.GetBounds();
	glm::vec3 pos = cameraController.GetCameraPos();

	glm::vec4 MapRect = {
		bound.Top + pos.y,     // 上边界
		bound.Right + pos.x,   // 右边界
		bound.Bottom + pos.y,  // 下边界
		bound.Left + pos.x     // 左边界
	};

	// 添加缓冲区常量
	const float BUFFER_ZONE = 5.0f;
	const float MOVE_SPEED = 6.0f;
	float moveAmount = MOVE_SPEED * ts;

	glm::vec4 mapBoundRect = {
		mapSize.first - bound.GetWidth() / 2 - 1 ,
		bound.GetWidth() / 2,
		mapSize.second - bound.GetHeight() / 2 - 1,
		bound.GetHeight() / 2
	};

	// 检查右边界
	if (mainRect.x > MapRect[1] - BUFFER_ZONE) // CrtRect[1]是右边界
	{
		//SYC_TRACE("Camera Update Right");
		glm::vec3 newPos = { pos.x + moveAmount, pos.y, pos.z };
		cameraController.SetCameraPos(CalCameraPos(newPos, mapBoundRect));
	}
	// 检查左边界
	if (mainRect.x < MapRect[3] + BUFFER_ZONE) // CrtRect[3]是左边界
	{
		//SYC_TRACE("Camera Update Left");
		glm::vec3 newPos = { pos.x - moveAmount, pos.y, pos.z };
		cameraController.SetCameraPos(CalCameraPos(newPos, mapBoundRect));
	}
	// 检查上边界
	if (mainRect.y > MapRect[0] - BUFFER_ZONE) // CrtRect[0]是上边界
	{
		//SYC_TRACE("Camera Update Top");
		glm::vec3 newPos = { pos.x, pos.y + moveAmount, pos.z };
		cameraController.SetCameraPos(CalCameraPos(newPos, mapBoundRect));
	}
	// 检查下边界
	if (mainRect.y < MapRect[2] + BUFFER_ZONE) // CrtRect[2]是下边界
	{
		//SYC_TRACE("Camera Update Bottom");
		glm::vec3 newPos = { pos.x, pos.y - moveAmount, pos.z };
		cameraController.SetCameraPos(CalCameraPos(newPos, mapBoundRect));
	}
}

void Level::UpdateTimeout(syc::Timestep ts)
{
}

void Level::Draw(const glm::vec3& cameraPos, const glm::vec2& viewSize)
{
	//switch (m_LevelStatus)
	//{
	//case Gaming: DrawGameing(cameraPos, viewSize);  break;
	//case Timeout:
	//	//syc::Ref<Mask> mask = std::dynamic_pointer_cast<Mask>(m_Actors["mask"]);
	//	break;
	//case End:
	//	break;
	//case Win:
	//	break;
	//default:
	//	break;
	//}
	DrawGameing(cameraPos, viewSize);
	if (m_LevelStatus == LevelStatus::End || m_LevelStatus == LevelStatus::Timeout)
	{
		syc::Ref<Mask> mask = ACTOR_EX(Mask, "mask");
		mask->SetSize(viewSize);
		mask->SetPos(cameraPos.x, cameraPos.y, 1.0f);
		mask->Enable();
		mask->Visible();
	}
}

void Level::DrawImGuiLayer(const glm::vec3& cameraPos, const glm::vec2& viewSize, const ImGUIAssets& imguiAsset)
{
	m_ImDrawList = ImGui::GetBackgroundDrawList();
	if (m_LevelStatus == LevelStatus::Gaming)
	{
		ImVec2 pos = ImGui::GetWindowPos();
		DrawImGuiHpBar({ pos.x - 200.0f, pos.y - 20.0f }, { 200, 30 });
		DrawImGuiTimeBar({ pos.x - 200.0f, pos.y - 70.0f });
	}
	else if (m_LevelStatus == LevelStatus::Win)
	{
		auto pos = ImGui::GetWindowPos();
		auto center = syc::Application::Get().GetWindow().GetCenter();
		float fontSize = 80.0f;
		pos.x += center.first - fontSize * 10.0f;
		pos.y += center.second - fontSize * 2.0f;
		DrawImGuiText("恭喜你，你成功逃离命运！你被判处了自由之刑！", { pos.x, pos.y }, { 255, 255, 255, 255 }, imguiAsset.Font, fontSize);
	}
	else if (m_LevelStatus == LevelStatus::End)
	{
		auto pos = ImGui::GetWindowPos();
		auto center = syc::Application::Get().GetWindow().GetCenter();
		float fontSize = 80.0f;
		pos.x += center.first - fontSize * 10.0f;
		pos.y += center.second - fontSize * 2.0f;
		DrawImGuiText("还没到那个规定的时刻，你的生命走向了终结。", { pos.x, pos.y }, { 255, 255, 255, 255 }, imguiAsset.Font, fontSize);
	}
	else if (m_LevelStatus == LevelStatus::Timeout)
	{
		auto pos = ImGui::GetWindowPos();
		auto center = syc::Application::Get().GetWindow().GetCenter();
		float fontSize = 80.0f;
		pos.x += center.first - fontSize * 8.0f;
		pos.y += center.second - fontSize * 2.0f;
		std::string text = "游戏结束：时间已耗尽，最终得分为" + std::to_string(m_Generation * 100);
		DrawImGuiText(text, { pos.x, pos.y }, { 255, 255, 255, 255 }, imguiAsset.Font, fontSize);
	}
}

void Level::DrawGameing(const glm::vec3& cameraPos, const glm::vec2& viewSize)
{
	m_Map2d.DrawBase(cameraPos, viewSize);
	m_Map2d.DrawAddition(cameraPos, viewSize);
	// 遍历所有墓碑位置
	for (const auto& pos : m_TomebstonePosSetNPC)
	{
		glm::vec3 pos3D = { pos.x, pos.y, 0.9f };
		syc::Renderer2D::DrawQuad(pos3D, { 1.0f, 1.0f }, m_SpriteSheets["tombstoneSubtexture"]);
	}
	for (const auto& [key, value] : m_Actors)
	{
		if (!value->GetVisible()) 
			continue;
		value->Draw();
	}
	
}

syc::Ref<Player> Level::GetPlayer()
{
	std::string key = (std::ostringstream() << "main" << std::to_string(m_Generation)).str();
	return ACTOR_EX(Player, key);
}

std::string Level::GetCurrentPlayerKey() const
{
	return (std::ostringstream() << "main" << std::to_string(m_Generation)).str();
}

std::string Level::GenNewPlayer(const glm::vec3& pos)
{
	m_Generation++;
	std::string key = (std::ostringstream() << "main" << std::to_string(m_Generation)).str();
	syc::Ref<Player> player = syc::CreateRef<Player>(LoadSubTexture(m_SpriteSheets["manSubtexture"]), pos);
	player->SetMaxHp(10 * (m_Generation + 1));
	player->SetHp(10 * (m_Generation + 1));
	m_Actors[key] = player;
	m_ActorCount++;
	return key;
}

std::string Level::GenNewPlayerFromOld()
{
	m_Generation++;
	syc::Ref<Player> playerOld = GetPlayer();
	float hpSacle = playerOld->GetHp() / playerOld->GetMaxHp();
	std::string key = (std::ostringstream() << "main" << std::to_string(m_Generation)).str();
	syc::Ref<Player> player = syc::CreateRef<Player>(LoadSubTexture(m_SpriteSheets["manSubtexture"]), playerOld->GetPos());
	player->SetMaxHp(10 * (m_Generation + 1));
	player->SetHp(hpSacle * player->GetMaxHp());
	m_Actors[key] = player;
	m_ActorCount++;
	return key;
}

void Level::MoveNPCRandom(const std::string& key)
{
#if _DEBUG
	if (m_Actors.find(key) == m_Actors.end())
	{
		SYC_ERROR("NPC with key \"{0}\" not exists.", key);
		throw std::runtime_error("NPC with key not exists.");
	}
#endif
	glm::vec4 npcRect = m_Actors[key]->GetRect();
	glm::vec3 pos = m_Actors[key]->GetPos();
	glm::vec2 size = { npcRect.z, npcRect.w };
	std::pair mapSize = m_Map2d.GetMapSize();
	glm::vec3 playPos = GetPlayer()->GetPos();
	glm::vec2 newPos{};
	do
	{
		// 计算新的随机位置
		newPos.x = syc::Random::Float() * (mapSize.first - size.x);
		newPos.y = syc::Random::Float() * (mapSize.second - size.y);
		// 限制NPC在地图范围内
		KeepRectInMap2D(newPos, size, { mapSize.second, mapSize.first, 0, 0 });
	} while (m_Map2d.IsCollision(newPos) || playPos.x == newPos.x || playPos.y == newPos.y);

	//SYC_TRACE("NPC newPos: ({0}, {1})", static_cast<size_t>(newPos.x), static_cast<size_t>(newPos.y));
	m_Actors[key]->SetPos(newPos.x, newPos.y, pos.z);
}

void Level::MoveNPCOutCameraRandom(const std::string& key, syc::OrthographicCameraController cameraC)
{
#if _DEBUG
	if (m_Actors.find(key) == m_Actors.end())
	{
		SYC_ERROR("NPC with key \"{0}\" not exists.", key);
		throw std::runtime_error("NPC with key not exists.");
	}
#endif
	glm::vec4 npcRect = m_Actors[key]->GetRect();
	glm::vec3 pos = m_Actors[key]->GetPos();
	glm::vec2 size = { npcRect.z, npcRect.w };
	std::pair mapSize = m_Map2d.GetMapSize();
	glm::vec3 playPos = GetPlayer()->GetPos();
	glm::vec2 newPos{};
	bool inBound = false;
	do
	{
		// 计算新的随机位置
		newPos.x = syc::Random::Float() * (mapSize.first - size.x);
		newPos.y = syc::Random::Float() * (mapSize.second - size.y);
		// 限制NPC在地图范围内
		KeepRectInMap2D(newPos, size, { mapSize.second, mapSize.first, 0, 0 });

		//新位置是否位于相机可视范围内
		glm::vec3 cameraPos = cameraC.GetCameraPos();
		syc::OrthographicCameraBounds bound = cameraC.GetBounds();
		// 计算相机的边界
		glm::vec4 cameraBound = {
			cameraPos.y + bound.GetHeight(),
			cameraPos.x + bound.GetWidth(),
			cameraPos.y,
			cameraPos.x
		};
		
		//SYC_TRACE("bound ({0}, {1}, {2}, {3})", cameraBound[0], cameraBound[1], cameraBound[2], cameraBound[3]);
		//SYC_TRACE("newPos:({0}, {1})", newPos.x, newPos.y);

		// 检查新位置是否在相机的可视范围内
		if (newPos.x > cameraBound[3] && newPos.x < cameraBound[1] &&
			newPos.y > cameraBound[2] && newPos.y < cameraBound[0])
		{
			inBound = true;
		}
		else
		{
			inBound = false;
		}

	} while (m_Map2d.IsCollision(newPos) || (playPos.x == newPos.x && playPos.y == newPos.y) || inBound);

	//SYC_TRACE("NPC newPos: ({0}, {1})", static_cast<size_t>(newPos.x), static_cast<size_t>(newPos.y));
	m_Actors[key]->SetPos(newPos.x, newPos.y, pos.z);
}

void Level::MoveNPC(const std::string& key, const glm::vec3& pos)
{
#if _DEBUG
	if (m_Actors.find(key) == m_Actors.end())
	{
		SYC_ERROR("NPC with key \"{0}\" not exists.", key);
		throw std::runtime_error("NPC with key not exists.");
	}
#endif
	m_Actors[key] = syc::CreateRef<NPC>(LoadSubTexture(m_SpriteSheets["womanSubtexture"]), pos);
	m_ActorCount++;
}

bool Level::InRect(glm::vec4 rect, glm::vec2 pos)
{
	return rect.x <= pos.x && rect.y;
}


void Level::DrawImGuiHpBar(glm::vec2 pos, glm::vec2 size)
{ 
    syc::Ref<Player> player = GetPlayer();
	float progreeHp = player->GetHp() / player->GetMaxHp();
	//SYC_TRACE("HP: {0}, MaxHp: {1}", player->GetHp(), player->GetMaxHp());
	DrawImGuiProgressBar(progreeHp, pos, size, { 100, 100, 100, 255 }, { 220, 20, 60, 255 }, { 255, 255, 255, 255 });
}

void Level::DrawImGuiTimeBar(glm::vec2 pos)
{
	float progreeTime = m_Time / m_MaxTime;
	DrawImGuiProgressBar(progreeTime, pos, { 1300, 10 }, { 200, 200, 200, 255 }, { 20, 60, 200, 255 });
}

void Level::DrawImGuiText(const std::string& text, const glm::vec2& pos, const glm::vec4& color, ImFont* font, float size)
{
	ImVec2 _pos = { pos.x,  pos.y };
	auto imColor = IM_COL32(color.r, color.g, color.b, color.a);
	m_ImDrawList->AddText(font, size, ImVec2(_pos.x + 1, pos.y + 1), IM_COL32(30, 100, 60, 150), text.c_str());
	m_ImDrawList->AddText(font, size, _pos, imColor, text.c_str());
}

std::vector<syc::Ref<syc::SubTexture2D>> Level::LoadSubTexture(const syc::Ref<syc::Texture2D>& spriteSheet, size_t maxIndex)
{
	std::vector<syc::Ref<syc::SubTexture2D>> textures;
	for (size_t i = 0; i < maxIndex; i++)
	{
		textures.emplace_back(syc::SubTexture2D::CreateFromCoords(spriteSheet, { static_cast<float>(i), 0.0f }, { 16.0f, 16.0f }));
	}
	return textures;
}

void Level::LoadResource()
{
	m_SpriteSheets["manSubtexture"] = syc::Texture2D::Create("assets/textures/man_sheet.png");
	m_SpriteSheets["womanSubtexture"] = syc::Texture2D::Create("assets/textures/woman_sheet.png");
	m_SpriteSheets["manColoredSubtexture"] = syc::Texture2D::Create("assets/textures/man_colored_sheet.png");
	m_SpriteSheets["womanColoredSubtexture"] = syc::Texture2D::Create("assets/textures/woman_colored_sheet.png");
	m_SpriteSheets["stoneSubtexture"] = syc::Texture2D::Create("assets/textures/stone_sheet.png");
	m_SpriteSheets["tombstoneSubtexture"] = syc::Texture2D::Create("assets/textures/tombstone.png");
}

const glm::vec3 Level::CalCameraPos(const glm::vec3& newPos, const glm::vec4& mapSize)
{
	// 0 maxX, 1 minX, 2 maxY, 3 minY
	return { glm::clamp(newPos.x, mapSize[1], mapSize[0]),
		glm::clamp(newPos.y, mapSize[3], mapSize[2]),
		newPos.z };
}

const void Level::KeepRectInMap2D(glm::vec2& playerPos, const glm::vec2& playerSize, const glm::vec4& mapBounds)
{
	// 计算角色矩形的边界
	float halfWidth = playerSize.x / 2.0f;
	float halfHeight = playerSize.y / 2.0f;

	// X轴限制
	playerPos.x = glm::clamp(playerPos.x,
		mapBounds[3] + halfWidth,  // 左边界 + 半个宽度
		mapBounds[1] - halfWidth); // 右边界 - 半个宽度

	// Y轴限制
	playerPos.y = glm::clamp(playerPos.y,
		mapBounds[2] + halfHeight, // 下边界 + 半个高度
		mapBounds[0] - halfHeight); // 上边界 - 半个高度
}

void Level::DrawImGuiProgressBar(float progress, const glm::vec2& pos, const glm::vec2& size, const glm::vec4& bgColor, const glm::vec4& progressColor)
{
	// 获取当前控件在屏幕上的绘制起点位置
	ImVec2 _pos;
	_pos.x = pos.x;
	_pos.y = pos.y;

	float _progress = size.x * glm::clamp(progress, 0.0f, 1.0f);

	auto bgImColor = IM_COL32(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	auto progressImColor = IM_COL32(progressColor.r, progressColor.g, progressColor.b, progressColor.a);

	m_ImDrawList->AddRectFilled(_pos, ImVec2(_pos.x + size.x, _pos.y + size.y), bgImColor);      // 背景
	m_ImDrawList->AddRectFilled(_pos, ImVec2(_pos.x + _progress, _pos.y + size.y), progressImColor); // 进度
}

void Level::DrawImGuiProgressBar(float progress, const glm::vec2& pos, const glm::vec2& size, const glm::vec4& bgColor, const glm::vec4& progressColor, const glm::vec4& frameColor)
{
	// 获取当前控件在屏幕上的绘制起点位置
	ImVec2 _pos;
	_pos.x = pos.x;
	_pos.y = pos.y;

	float _progress = size.x * glm::clamp(progress, 0.0f, 1.0f);

	auto bgImColor = IM_COL32(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	auto progressImColor = IM_COL32(progressColor.r, progressColor.g, progressColor.b, progressColor.a);
	auto frameImColor = IM_COL32(frameColor.r, frameColor.g, frameColor.b, frameColor.a);

	m_ImDrawList->AddRectFilled(_pos, ImVec2(_pos.x + size.x, _pos.y + size.y), bgImColor);      // 背景
	m_ImDrawList->AddRectFilled(_pos, ImVec2(_pos.x + _progress, _pos.y + size.y), progressImColor); // 进度
	m_ImDrawList->AddRect(_pos, ImVec2(_pos.x + size.x, _pos.y + size.y), frameImColor);           // 边框
}


