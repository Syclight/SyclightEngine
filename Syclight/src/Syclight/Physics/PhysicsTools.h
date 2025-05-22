#pragma once

#include "Syclight/Core/Base.h"

#include <glm/glm.hpp>

namespace syc
{
	struct CollisionInfo {
		bool8 Collided;        // 是否发生碰撞
		glm::vec2 Direction;  // 碰撞方向（法线方向，从rectB指向rectA）
		float Depth; // 碰撞深度
	};

	class PhysicsTools
	{
	public:
		static bool8 SATCollisionTest(const glm::vec2 rectA[4], const glm::vec2 rectB[4]);
		const static CollisionInfo SATCollisionTestInfo(const glm::vec2 rectA[4], const glm::vec2 rectB[4]);
	};
}

