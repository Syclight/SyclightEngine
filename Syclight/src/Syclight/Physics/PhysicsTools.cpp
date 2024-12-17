#include "sycpch.h"
#include "PhysicsTools.h"

namespace syc
{
	bool8 PhysicsTools::SATCollisionTest(const glm::vec2 rectA[4], const glm::vec2 rectB[4])
	{
        glm::vec2 axes[4] = {
            glm::normalize(rectA[1] - rectA[0]),
            glm::normalize(rectA[3] - rectA[0]),
            glm::normalize(rectB[1] - rectB[0]),
            glm::normalize(rectB[3] - rectB[0])
        };

        for (const auto& axis : axes)
        {
            float minA = std::numeric_limits<float>::max();
            float maxA = std::numeric_limits<float>::lowest();
            for (int i = 0; i < 4; i++) // 遍历rectA的顶点
            {
                float projection = glm::dot(rectA[i], axis);
                minA = glm::min(minA, projection);
                maxA = glm::max(maxA, projection);
            }

            float minB = std::numeric_limits<float>::max();
            float maxB = std::numeric_limits<float>::lowest();
            for (int i = 0; i < 4; i++) // 遍历rectB的顶点
            {
                float projection = glm::dot(rectB[i], axis);
                minB = glm::min(minB, projection);
                maxB = glm::max(maxB, projection);
            }

            if (maxA < minB || maxB < minA)
                return false;
        }

        return true;
	}
}