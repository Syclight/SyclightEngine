#include "Actor.h"

#include <imgui/imgui.h>

Player::Player(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures)
{
	m_Textures = subtextures;
	size_t size = subtextures.size();

	for (size_t i = 0; i < 6; i++)
	{
		syc::Ref<syc::SubTexture2D> subtexture = m_Textures[i];
		auto copyTexture = m_Textures[i]->Copy();
		copyTexture->Inversion();
		m_Textures.emplace_back(copyTexture);
	}
	m_DeadTexture = syc::Texture2D::Create("assets/textures/tombstone.png");
	SetState(STATE::FrontWalk);
}

Player::Player(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures, const glm::vec3& pos)
	: m_Pos({ pos.x, pos.y, pos.z })
{
	m_Textures = subtextures;
	size_t size = subtextures.size();

	for (size_t i = 0; i < 6; i++)
	{
		syc::Ref<syc::SubTexture2D> subtexture = m_Textures[i];
		auto copyTexture = m_Textures[i]->Copy();
		copyTexture->Inversion();
		m_Textures.emplace_back(copyTexture);
	}
	m_DeadTexture = syc::Texture2D::Create("assets/textures/tombstone.png");

	SetState(STATE::FrontWalk);
}

void Player::Update(syc::Timestep ts)
{
	if (m_RecordTimeStamp >= 0.3f)
	{
		m_CrtIndex += 1;
		m_CrtIndex = m_CrtIndex >= 4 ? 0 : m_CrtIndex;
		m_RecordTimeStamp = 0.0f;
		m_Index = m_FrameIndeices[m_CrtIndex];
	}
	m_RecordTimeStamp = m_RecordTimeStamp + ts;

	if (syc::Input::IsKeyPressed(SYC_KEY_W) || syc::Input::IsKeyPressed(SYC_KEY_UP))
	{
		if (m_State != STATE::BackWalk)
		{
			SetState(STATE::BackWalk);
		}
		else
		{
			m_Pos.y += m_Velocity.x * ts;
		}
	}
	else if (syc::Input::IsKeyPressed(SYC_KEY_S) || syc::Input::IsKeyPressed(SYC_KEY_DOWN))
	{
		if (m_State != STATE::FrontWalk)
		{
			SetState(STATE::FrontWalk);
		}
		else
		{
			m_Pos.y += m_Velocity.y * ts;
		}
	}

	if (syc::Input::IsKeyPressed(SYC_KEY_A) || syc::Input::IsKeyPressed(SYC_KEY_LEFT))
	{
		if (m_State != STATE::LeftWalk)
		{
			SetState(STATE::LeftWalk);
		}
		else
		{
			m_Pos.x += m_Velocity.z * ts;
		}
	}
	else if (syc::Input::IsKeyPressed(SYC_KEY_D) || syc::Input::IsKeyPressed(SYC_KEY_RIGHT))
	{
		if (m_State != STATE::RightWalk)
		{
			SetState(STATE::RightWalk);
		}
		else
		{
			m_Pos.x += m_Velocity.w * ts;
		}
	}
}

void Player::Draw()
{
	if (m_Dead)
	{
		syc::Renderer2D::DrawQuad(m_Pos, m_Size, m_DeadTexture);
	}
	else
	{
		syc::Renderer2D::DrawQuad(m_Pos, m_Size, m_Textures[m_Index]);
	}
}

const glm::vec4 Player::GetRect()
{
	return { m_Pos.x,  m_Pos.y, m_Size.x, m_Size.y };
}

void Player::SetVelocity(float velocityX, float velocityY)
{
	m_Velocity.x = velocityY;
	m_Velocity.y = -velocityY;
	m_Velocity.z = -velocityX;
	m_Velocity.w = velocityX;
}

void Player::SetVelocity(float velocityUp, float velocityDown, float velocityRight, float velocityLeft)
{
	m_Velocity.x = velocityUp;
	m_Velocity.y = velocityDown;
	m_Velocity.z = velocityRight;
	m_Velocity.w = velocityLeft;
}

const glm::vec4 Player::GetVelocity()
{
	return m_Velocity;
}

void Player::SetPos(float posX, float posY, float posZ)
{
	m_Pos.x = posX;
	m_Pos.y = posY;
	m_Pos.z = posZ;
}

const glm::vec3 Player::GetPos()
{
	return m_Pos;
}

float Player::SetHp(float hp)
{
	float tmp = hp > m_MaxHp ? m_MaxHp : hp;
	m_CurrentHp = tmp < 0.0f ? 0.0f : tmp;
	return m_CurrentHp;
}


void Player::SetState(STATE state)
{
	switch (state)
	{
	case STATE::Front:
		m_FrameIndeices[0] = 0;
		m_FrameIndeices[1] = 0;
		m_FrameIndeices[2] = 0;
		m_FrameIndeices[3] = 0;
		break;
	case STATE::FrontWalk:
		m_FrameIndeices[0] = 0;
		m_FrameIndeices[1] = 3;
		m_FrameIndeices[2] = 0;
		m_FrameIndeices[3] = 9;
		break;
	case STATE::Right:
		m_FrameIndeices[0] = 8;
		m_FrameIndeices[1] = 8;
		m_FrameIndeices[2] = 8;
		m_FrameIndeices[3] = 8;
		break;
	case STATE::RightWalk:
		m_FrameIndeices[0] = 8;
		m_FrameIndeices[1] = 11;
		m_FrameIndeices[2] = 8;
		m_FrameIndeices[3] = 11;
		break;
	case STATE::Left:
		m_FrameIndeices[0] = 2;
		m_FrameIndeices[1] = 2;
		m_FrameIndeices[2] = 2;
		m_FrameIndeices[3] = 2;
		break;
	case STATE::LeftWalk:
		m_FrameIndeices[0] = 2;
		m_FrameIndeices[1] = 5;
		m_FrameIndeices[2] = 2;
		m_FrameIndeices[3] = 5;
		break;
	case STATE::Back:
		m_FrameIndeices[0] = 1;
		m_FrameIndeices[1] = 1;
		m_FrameIndeices[2] = 1;
		m_FrameIndeices[3] = 1;
		break;
	case STATE::BackWalk:
		m_FrameIndeices[0] = 1;
		m_FrameIndeices[1] = 4;
		m_FrameIndeices[2] = 1;
		m_FrameIndeices[3] = 10;
		break;
	default:
		break;
	}
	m_State = state;
}

void Player::Turn(char dir)
{
	if (dir == 'f')
		SetState(STATE::Front);
	else if (dir == 'b')
		SetState(STATE::Back);
	else if (dir == 'l')
		SetState(STATE::Left);
	else if (dir == 'r')
		SetState(STATE::Right);
}

void Player::Dead()
{
	m_Active = false;
	m_Dead = true;
}

syc::Ref<syc::SubTexture2D> Player::GetTexture()
{
	return nullptr;
}

NPC::NPC(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures)
{
	m_Textures = subtextures;
	size_t size = subtextures.size();

	for (size_t i = 0; i < 6; i++)
	{
		syc::Ref<syc::SubTexture2D> subtexture = m_Textures[i];
		auto copyTexture = m_Textures[i]->Copy();
		copyTexture->Inversion();
		m_Textures.emplace_back(copyTexture);
	}

	SetState(STATE::FrontWalk);
}

NPC::NPC(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures, const glm::vec3& pos)
	:m_InitPos({ pos.x, pos.y, pos.z }), m_Pos({ pos.x, pos.y, pos.z })
{
	m_Textures = subtextures;
	size_t size = subtextures.size();

	for (size_t i = 0; i < 6; i++)
	{
		syc::Ref<syc::SubTexture2D> subtexture = m_Textures[i];
		auto copyTexture = m_Textures[i]->Copy();
		copyTexture->Inversion();
		m_Textures.emplace_back(copyTexture);
	}

	SetState(STATE::FrontWalk);
}

void NPC::Update(syc::Timestep ts)
{
	if (!m_Active) return;
	if (m_RecordTimeStamp >= 0.3f)
	{
		m_CrtIndex += 1;
		m_CrtIndex = m_CrtIndex >= 4 ? 0 : m_CrtIndex;
		m_RecordTimeStamp = 0.0f;
		m_Index = m_FrameIndeices[m_CrtIndex];
	}
	m_RecordTimeStamp = m_RecordTimeStamp + ts;
}

void NPC::Draw()
{
	if (!m_Visible) return;
	syc::Renderer2D::DrawQuad(m_Pos, m_Size, m_Textures[m_Index]);
}

const glm::vec4 NPC::GetRect()
{
	return { m_Pos.x,  m_Pos.y, m_Size.x, m_Size.y };
}

void NPC::Turn(char dir)
{
	if (dir == 'f') { SetState(STATE::Front); }
	else if (dir == 'b') { SetState(STATE::Back); }
	else if (dir == 'l') { SetState(STATE::Left); }
	else if (dir == 'r') { SetState(STATE::Right); }
}

void NPC::SetState(STATE state)
{
	switch (state)
	{
	case STATE::Front:
		m_FrameIndeices[0] = 0;
		m_FrameIndeices[1] = 0;
		m_FrameIndeices[2] = 0;
		m_FrameIndeices[3] = 0;
		break;
	case STATE::FrontWalk:
		m_FrameIndeices[0] = 0;
		m_FrameIndeices[1] = 3;
		m_FrameIndeices[2] = 0;
		m_FrameIndeices[3] = 9;
		break;
	case STATE::Right:
		m_FrameIndeices[0] = 8;
		m_FrameIndeices[1] = 8;
		m_FrameIndeices[2] = 8;
		m_FrameIndeices[3] = 8;
		break;
	case STATE::RightWalk:
		m_FrameIndeices[0] = 8;
		m_FrameIndeices[1] = 11;
		m_FrameIndeices[2] = 8;
		m_FrameIndeices[3] = 11;
		break;
	case STATE::Left:
		m_FrameIndeices[0] = 2;
		m_FrameIndeices[1] = 2;
		m_FrameIndeices[2] = 2;
		m_FrameIndeices[3] = 2;
		break;
	case STATE::LeftWalk:
		m_FrameIndeices[0] = 2;
		m_FrameIndeices[1] = 5;
		m_FrameIndeices[2] = 2;
		m_FrameIndeices[3] = 5;
		break;
	case STATE::Back:
		m_FrameIndeices[0] = 1;
		m_FrameIndeices[1] = 1;
		m_FrameIndeices[2] = 1;
		m_FrameIndeices[3] = 1;
		break;
	case STATE::BackWalk:
		m_FrameIndeices[0] = 1;
		m_FrameIndeices[1] = 4;
		m_FrameIndeices[2] = 1;
		m_FrameIndeices[3] = 10;
		break;
	default:
		break;
	}
	m_State = state;
}

NodeStatus NPC::MoveAround()
{
	return NodeStatus::Success;
}

NodeStatus NPC::CreateNextGen()
{
	return NodeStatus::Success;
}

void NPC::SetVelocity(float velocityX, float velocityY)
{
	m_Velocity.x = velocityY;
	m_Velocity.y = -velocityY;
	m_Velocity.z = -velocityX;
	m_Velocity.w = velocityX;
}

void NPC::SetVelocity(float velocityUp, float velocityDown, float velocityRight, float velocityLeft)
{
	m_Velocity.x = velocityUp;
	m_Velocity.y = velocityDown;
	m_Velocity.z = velocityRight;
	m_Velocity.w = velocityLeft;
}

const glm::vec4 NPC::GetVelocity()
{
	return m_Velocity;
}

void NPC::SetPos(float posX, float posY, float posZ)
{
	m_Pos.x = posX;
	m_Pos.y = posY;
	m_Pos.z = posZ;
}

const glm::vec3 NPC::GetPos()
{
	return m_Pos;
}

Collider::Collider(const glm::vec3& pos, const glm::vec2& size)
{
	m_Pos = pos;
	m_Size = size;
}

const glm::vec4 Collider::GetRect()
{
	return { m_Pos.x,  m_Pos.y, m_Size.x, m_Size.y };
}

void Collider::SetPos(float posX, float posY, float posZ)
{
	m_Pos.x = posX;
	m_Pos.y = posY;
	m_Pos.z = posZ;
}

const glm::vec3 Collider::GetPos()
{
	return m_Pos;
}

Wall::Wall(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures, const glm::vec3& pos, const glm::vec2& size)
{
	m_Textures = subtextures;
	m_Pos = pos;
	m_Size = size;
}

void Wall::Update(syc::Timestep ts)
{
}

void Wall::Draw()
{
	if (!m_Visible) return;
	syc::Renderer2D::DrawQuad(m_Pos, m_Size, m_Textures[m_Index]);
}

const glm::vec4 Wall::GetRect()
{
	return { m_Pos.x,  m_Pos.y, m_Size.x, m_Size.y };
}

void Wall::SetPos(float posX, float posY, float posZ)
{
	m_Pos.x = posX;
	m_Pos.y = posY;
	m_Pos.z = posZ;
}

const glm::vec3 Wall::GetPos()
{
	return m_Pos;
}

void Wall::HandleCollision()
{
	m_HP -= 1;
}

void Wall::nextTexture()
{
	m_Index = (m_Index + 1) % m_Textures.size();
}

const size_t Wall::SetHP(size_t hp)
{
	float tmp = hp > m_MaxHp ? m_MaxHp : hp;
	m_HP = tmp < 0.0f ? 0.0f : tmp;
	m_Index = (hp == 0) ? 4 : (hp >= 80) ? 0 : (79 - hp) / 20 + 1;
	return m_HP;
}

Mask::Mask(const glm::vec3& pos, const glm::vec2& size, const glm::vec3& color, float alpha)
	: m_Pos(pos), m_Size(size), m_Color(color), m_Alpha(alpha)
{
}

void Mask::Draw()
{
	syc::Renderer2D::DrawQuad(m_Pos, m_Size, { m_Color, m_Alpha });
}

const glm::vec4 Mask::GetRect()
{
	return { m_Pos.x,  m_Pos.y, m_Size.x, m_Size.y };
}
