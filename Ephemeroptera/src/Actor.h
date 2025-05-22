#pragma once

#include <Syclight.h>

#include "BehaviorTree.h"

enum STATE
{
	Front,
	FrontWalk,
	Right,
	RightWalk,
	Left,
	LeftWalk,
	Back,
	BackWalk
};

class Actor
{
public:
	virtual ~Actor() = default;
	virtual void Update(syc::Timestep ts) = 0;
	virtual void Draw() = 0;
	virtual const glm::vec4 GetRect() = 0;

	virtual void SetVelocity(float velocityX, float velocityY) = 0;
	virtual void SetVelocity(float velocityUp, float velocityDown, float velocityRight, float velocityLeft) = 0;
	virtual const glm::vec4 GetVelocity() = 0;

	virtual void SetPos(float posX, float posY) = 0;
	virtual void SetPos(float posX, float posY, float posZ) = 0;
	virtual const glm::vec3 GetPos() = 0;

	virtual bool GetVisible() = 0;
	virtual void Invisible() = 0;
	virtual void Visible() = 0;
	virtual bool GetActive() = 0;
	virtual void Disable() = 0;
	virtual void Enable() = 0;

	//virtual void ResetPos(int dir) = 0;
};

class Collider : public Actor
{
public:
	Collider(const glm::vec3& pos, const glm::vec2& size);
	virtual void Update(syc::Timestep ts) override {};
	virtual void Draw() override {};
	virtual const glm::vec4 GetRect() override;
	virtual void SetVelocity(float velocityX, float velocityY) override {};
	virtual void SetVelocity(float velocityUp, float velocityDown, float velocityRight, float velocityLeft) override {};
	virtual const glm::vec4 GetVelocity() override { return glm::vec4(); }
	virtual void SetPos(float posX, float posY) override { m_Pos.x = posX; m_Pos.y = posY; }
	virtual void SetPos(float posX, float posY, float posZ) override;
	virtual const glm::vec3 GetPos() override;

	virtual bool GetVisible() override { return m_Visible; }
	virtual void Invisible() override { m_Visible = false; }
	virtual void Visible() override { m_Visible = true; }
	virtual bool GetActive() override { return m_Active; }
	virtual void Disable() override { m_Active = false; }
	virtual void Enable() override { m_Active = true; }

private:
	glm::vec3 m_Pos = { 0.0f, 0.0f, 0.0f };
	glm::vec2 m_Size = { 0.0f, 0.0f };

	bool m_Visible = false;
	bool m_Active = true;
};

class Player : public Actor
{
public:
	Player(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures);
	Player(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures, const glm::vec3& pos);
	virtual void Update(syc::Timestep ts) override;
	virtual void Draw() override;
	virtual const glm::vec4 GetRect() override;
	
	virtual void SetVelocity(float velocityX, float velocityY) override;
	virtual void SetVelocity(float velocityUp, float velocityDown, float velocityRight, float velocityLeft) override;
	virtual const glm::vec4 GetVelocity() override;
	virtual void SetPos(float posX, float posY) override { m_Pos.x = posX; m_Pos.y = posY; }
	virtual void SetPos(float posX, float posY, float posZ) override;
	virtual const glm::vec3 GetPos() override;

	float SetHp(float hp);
	float GetHp() const { return m_CurrentHp; }
	float SetMaxHp(float maxHp) { m_MaxHp = maxHp; return m_MaxHp; }
	float GetMaxHp() const { return m_MaxHp; }

	float SetScore(size_t score) { m_Score = score; return m_Score; }
	size_t GetScore() const { return m_Score; }

	size_t GetGeneration() const { return m_Generation; }
	size_t SetGeneration(size_t generation) { m_Generation = generation; return m_Generation; }

	virtual bool GetVisible() override { return m_Visible; }
	virtual void Invisible() override { m_Visible = false; }
	virtual void Visible() override { m_Visible = true; }
	virtual bool GetActive() override { return m_Active; }
	virtual void Disable() override { m_Active = false; }
	virtual void Enable() override { m_Active = true; }

	void Turn(char dir);
	void Dead();

private:
	syc::Ref<syc::SubTexture2D> GetTexture();
	std::vector<syc::Ref<syc::SubTexture2D>> m_Textures;
	void SetState(STATE state);

	glm::vec3 m_Pos = { 0.0f, 0.0f, 0.5f };
	glm::vec4 m_Velocity = {6.0f, -6.0f, -6.0f, 6.0f};
	glm::vec2 m_Size = { 1.0f, 1.0f };
	STATE m_State = STATE::Front;
	int m_Index = 0;
	int m_CrtIndex = 0;
	int m_FrameIndeices[4] = { 0, 0, 0, 0 };
	syc::Timestep m_RecordTimeStamp;

	float m_MaxHp = 10;
	float m_CurrentHp = m_MaxHp;
	size_t m_Score = 0;
	size_t m_Generation = 0;

	bool m_Visible = true;
	bool m_Active = true;
	bool m_Dead = false;
	syc::Ref<syc::Texture2D> m_DeadTexture = nullptr;
};

class NPC : public Actor
{
public:
	NPC(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures);
	NPC(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures, const glm::vec3& pos);
	virtual void Update(syc::Timestep ts) override;
	virtual void Draw() override;
	virtual const glm::vec4 GetRect() override;
	virtual void SetPos(float posX, float posY) override { m_Pos.x = posX; m_Pos.y = posY; }
	virtual void SetPos(float posX, float posY, float posZ) override;
	virtual const glm::vec3 GetPos() override;

	void SetInitPos(float x, float y) { m_InitPos.x = x; m_InitPos.y = y; }
	void SetInitPos(float x, float y, float z) { m_InitPos.x = x; m_InitPos.y = y; m_InitPos.z = z; }
	const glm::vec3 GetInitPos() const { return m_InitPos; }

	virtual bool GetVisible() override { return m_Visible; }
	virtual void Invisible() override { m_Visible = false; }
	virtual void Visible() override { m_Visible = true; }
	virtual bool GetActive() override { return m_Active; }
	virtual void Disable() override { m_Active = false; }
	virtual void Enable() override { m_Active = true; }

	void Turn(char dir);

private:
	std::vector<syc::Ref<syc::SubTexture2D>> m_Textures;
	void SetState(STATE state);

	NodeStatus MoveAround();
	NodeStatus CreateNextGen();

	ActionNode moveNode{[this]() { return MoveAround(); }};
	ActionNode CreateNextGenNode{[this]() { return CreateNextGen(); }};

	virtual void SetVelocity(float velocityX, float velocityY) override;
	virtual void SetVelocity(float velocityUp, float velocityDown, float velocityRight, float velocityLeft) override;
	virtual const glm::vec4 GetVelocity() override;

	SelectorNode rootSelector{
		{
			syc::CreateRef<ActionNode>(moveNode),
			syc::CreateRef<ActionNode>(CreateNextGenNode)
		}
	};

	// 创建行为树
	BehaviorTree tree{ syc::CreateRef<SelectorNode>(rootSelector) };

	glm::vec3 m_Pos = { 0.0f, 0.0f, 0.5f };
	glm::vec2 m_Size = { 1.0f, 1.0f };
	glm::vec4 m_Velocity = { 0.0f, 0.0f, 0.0f, 0.0f };
	STATE m_State = STATE::Front;
	int m_Index = 0;
	int m_CrtIndex = 0;
	int m_FrameIndeices[4] = { 0, 0, 0, 0 };
	syc::Timestep m_RecordTimeStamp;

	glm::vec3 m_InitPos = m_Pos;

	glm::vec2 m_Directs[4] = {
		{1.0f, 0.0f},
		{0.0f, 1.0f},
		{-1.0f, 0.0f},
		{0.0f, -1.0f}
	};

	bool m_Visible = true;
	bool m_Active = true;
};

class Wall :public Actor
{
public:
	Wall(const std::vector<syc::Ref<syc::SubTexture2D>>& subtextures, const glm::vec3& pos, const glm::vec2& size);
	virtual void Update(syc::Timestep ts) override;
	virtual void Draw() override;
	virtual const glm::vec4 GetRect() override;
	virtual void SetVelocity(float velocityX, float velocityY) override {};
	virtual void SetVelocity(float velocityUp, float velocityDown, float velocityRight, float velocityLeft) override {};
	virtual const glm::vec4 GetVelocity() override { return glm::vec4(); }
	virtual void SetPos(float posX, float posY) override { m_Pos.x = posX; m_Pos.y = posY; }
	virtual void SetPos(float posX, float posY, float posZ) override;
	virtual const glm::vec3 GetPos() override;
	void HandleCollision();
	void nextTexture();
	size_t const GetIndex() const { return m_Index; }

	size_t GetHP() const { return m_HP; }
	const size_t SetHP(size_t hp);

	virtual bool GetVisible() override { return m_Visible; }
	virtual void Invisible() override { m_Visible = false; }
	virtual void Visible() override { m_Visible = true; }
	virtual bool GetActive() override { return m_Active; }
	virtual void Disable() override { m_Active = false; }
	virtual void Enable() override { m_Active = true; }

private:
	std::vector<syc::Ref<syc::SubTexture2D>> m_Textures;
	glm::vec3 m_Pos = { 0.0f, 0.0f, 0.0f };
	glm::vec2 m_Size = { 0.0f, 0.0f };
	
	size_t m_Index = 0;
	size_t m_MaxHp = 100;
	size_t m_HP = m_MaxHp;

	bool m_Visible = true;
	bool m_Active = true;
};

class Mask :public Actor
{
public:
	Mask(const glm::vec3& pos, const glm::vec2& size, const glm::vec3& color, float alpha=0.8);
	virtual void Update(syc::Timestep ts) override {}
	virtual void Draw() override;
	virtual const glm::vec4 GetRect() override;
	virtual void SetVelocity(float velocityX, float velocityY) override {}
	virtual void SetVelocity(float velocityUp, float velocityDown, float velocityRight, float velocityLeft) override {}
	virtual const glm::vec4 GetVelocity() override { return glm::vec4(); }
	virtual void SetPos(float posX, float posY) override { m_Pos.x = posX; m_Pos.y = posY; }
	virtual void SetPos(float posX, float posY, float posZ) override { m_Pos.x = posX; m_Pos.y = posY; m_Pos.z = posZ; }
	virtual const glm::vec3 GetPos() override { return m_Pos; }

	void SetColor(const glm::vec3& color) { m_Color = color; }
	void SetSize(const glm::vec2& size) { m_Size = size; updateStringPos(); }
	void SetAlpha(float alpha) { m_Alpha = alpha; }
	const glm::vec3 GetColor() const { return m_Color; }
	const glm::vec2 GetSize() const { return m_Size; }
	const float GetAlpha() const { return m_Alpha; }

	virtual bool GetVisible() override { return m_Visible; }
	virtual void Invisible() override { m_Visible = false; }
	virtual void Visible() override { m_Visible = true; }
	virtual bool GetActive() override { return m_Active; }
	virtual void Disable() override { m_Active = false; }
	virtual void Enable() override { m_Active = true; }

private:
	glm::vec3 m_Color = {0.0f, 0.0f, 0.0f};
	float m_Alpha = 0.8f;
	glm::vec3 m_Pos = { 0.0f, 0.0f, 0.99f };
	glm::vec2 m_Size = { 0.0f, 0.0f };
	glm::vec2 m_StringPos = { 0.0f, 0.0f };
	std::string m_ShowString = "";

	bool m_Visible = true;
	bool m_Active = true;

	void updateStringPos() {
		m_StringPos.x = m_Pos.x + m_Size.x / 2.0f;
		m_StringPos.y = m_Pos.y + m_Size.y / 2.0f;
	}
};