#pragma once

#include "Syclight/Core/Core.h"

#include <glm/glm.hpp>

namespace syc
{
	class PhysicsTools
	{
	public:
		static bool8 SATCollisionTest(const glm::vec2 rectA[4], const glm::vec2 rectB[4]);
	};
}

