#include "sycpch.h"
#include "PhysicsTools.h"

namespace syc
{

	bool8 PhysicsTools::SATCollisionTest(const glm::vec2 rectA[4], const glm::vec2 rectB[4])
	{
        // 期望顶点按顺时针顺序排列：左上、右上、右下、左下
        glm::vec2 axes[4] = {
            glm::normalize(rectA[1] - rectA[0]), // 矩形A的第一条边
            glm::normalize(rectA[3] - rectA[0]), // 矩形A的第二条边
            glm::normalize(rectB[1] - rectB[0]), // 矩形B的第一条边
            glm::normalize(rectB[3] - rectB[0])  // 矩形B的第二条边
        };

        for (const auto& axis : axes)
        {
            float minA = std::numeric_limits<float>::max();
            float maxA = std::numeric_limits<float>::lowest();
            
            float projA0 = glm::dot(rectA[0], axis);
            float projA1 = glm::dot(rectA[1], axis);
            float projA2 = glm::dot(rectA[2], axis);
            float projA3 = glm::dot(rectA[3], axis);
            
            minA = glm::min(glm::min(projA0, projA1), glm::min(projA2, projA3));
            maxA = glm::max(glm::max(projA0, projA1), glm::max(projA2, projA3));

            float minB = std::numeric_limits<float>::max();
            float maxB = std::numeric_limits<float>::lowest();
            
            float projB0 = glm::dot(rectB[0], axis);
            float projB1 = glm::dot(rectB[1], axis);
            float projB2 = glm::dot(rectB[2], axis);
            float projB3 = glm::dot(rectB[3], axis);
            
            minB = glm::min(glm::min(projB0, projB1), glm::min(projB2, projB3));
            maxB = glm::max(glm::max(projB0, projB1), glm::max(projB2, projB3));

            if (maxA < minB || maxB < minA)
            {
                return false;
            }
        }

        return true;
	}

    //const CollisionInfo PhysicsTools::SATCollisionTestInfo(const glm::vec2 rectA[4], const glm::vec2 rectB[4])
    //{
    //    CollisionInfo info = { false, glm::vec2(0.0f) };

    //    glm::vec2 axes[4] = {
    //        glm::normalize(rectA[1] - rectA[0]), // 矩形A的第一条边
    //        glm::normalize(rectA[3] - rectA[0]), // 矩形A的第二条边
    //        glm::normalize(rectB[1] - rectB[0]), // 矩形B的第一条边
    //        glm::normalize(rectB[3] - rectB[0])  // 矩形B的第二条边
    //    };

    //    // 用于记录最小重叠量和对应的轴
    //    float minOverlap = std::numeric_limits<float>::max();
    //    glm::vec2 minAxis;

    //    for (const auto& axis : axes)
    //    {
    //        // 计算rectA在当前轴上的投影范围
    //        float minA = std::numeric_limits<float>::max();
    //        float maxA = std::numeric_limits<float>::lowest();

    //        float projA0 = glm::dot(rectA[0], axis);
    //        float projA1 = glm::dot(rectA[1], axis);
    //        float projA2 = glm::dot(rectA[2], axis);
    //        float projA3 = glm::dot(rectA[3], axis);

    //        minA = glm::min(glm::min(projA0, projA1), glm::min(projA2, projA3));
    //        maxA = glm::max(glm::max(projA0, projA1), glm::max(projA2, projA3));

    //        // 计算rectB在当前轴上的投影范围
    //        float minB = std::numeric_limits<float>::max();
    //        float maxB = std::numeric_limits<float>::lowest();

    //        float projB0 = glm::dot(rectB[0], axis);
    //        float projB1 = glm::dot(rectB[1], axis);
    //        float projB2 = glm::dot(rectB[2], axis);
    //        float projB3 = glm::dot(rectB[3], axis);

    //        minB = glm::min(glm::min(projB0, projB1), glm::min(projB2, projB3));
    //        maxB = glm::max(glm::max(projB0, projB1), glm::max(projB2, projB3));

    //        if (maxA < minB || maxB < minA)
    //        {
    //            return info;
    //        }

    //        // 计算当前轴上的重叠量
    //        float overlap = glm::min(maxA, maxB) - glm::max(minA, minB);
    //        if (overlap < minOverlap) {
    //            minOverlap = overlap;
    //            minAxis = axis;
    //        }
    //    }

    //    // 如果循环结束，说明没有分离轴，两个矩形相交
    //    info.Collided = true;

    //    // 计算两个矩形的中心点
    //    glm::vec2 centerA = (rectA[0] + rectA[1] + rectA[2] + rectA[3]) / 4.0f;
    //    glm::vec2 centerB = (rectB[0] + rectB[1] + rectB[2] + rectB[3]) / 4.0f;

    //    // 计算中心点连线向量（从rectB指向rectA）
    //    glm::vec2 diff = centerA - centerB;

    //    // 使用点积确定minAxis的方向
    //    // 如果点积为负，则反转minAxis，使其从rectB指向rectA
    //    float dotProduct = glm::dot(diff, minAxis);
    //    if (dotProduct < 0) {
    //        minAxis = -minAxis;
    //    }

    //    // 将minAxis设置为碰撞方向
    //    info.Direction = minAxis;

    //    return info;
    //}

    const CollisionInfo PhysicsTools::SATCollisionTestInfo(const glm::vec2 rectA[4], const glm::vec2 rectB[4])
    {
        // 初始化 CollisionInfo，添加 Depth 字段并设为 0
        CollisionInfo info = { false, glm::vec2(0.0f), 0.0f };

        // 定义测试轴（矩形A和矩形B的边）
        glm::vec2 axes[4] = {
            glm::normalize(rectA[1] - rectA[0]), // 矩形A的第一条边
            glm::normalize(rectA[3] - rectA[0]), // 矩形A的第二条边
            glm::normalize(rectB[1] - rectB[0]), // 矩形B的第一条边
            glm::normalize(rectB[3] - rectB[0])  // 矩形B的第二条边
        };

        // 用于记录最小重叠量和对应的轴
        float minOverlap = std::numeric_limits<float>::max();
        glm::vec2 minAxis;

        // 遍历所有轴进行投影测试
        for (const auto& axis : axes)
        {
            // 计算rectA在当前轴上的投影范围
            float minA = std::numeric_limits<float>::max();
            float maxA = std::numeric_limits<float>::lowest();

            float projA0 = glm::dot(rectA[0], axis);
            float projA1 = glm::dot(rectA[1], axis);
            float projA2 = glm::dot(rectA[2], axis);
            float projA3 = glm::dot(rectA[3], axis);

            minA = glm::min(glm::min(projA0, projA1), glm::min(projA2, projA3));
            maxA = glm::max(glm::max(projA0, projA1), glm::max(projA2, projA3));

            // 计算rectB在当前轴上的投影范围
            float minB = std::numeric_limits<float>::max();
            float maxB = std::numeric_limits<float>::lowest();

            float projB0 = glm::dot(rectB[0], axis);
            float projB1 = glm::dot(rectB[1], axis);
            float projB2 = glm::dot(rectB[2], axis);
            float projB3 = glm::dot(rectB[3], axis);

            minB = glm::min(glm::min(projB0, projB1), glm::min(projB2, projB3));
            maxB = glm::max(glm::max(projB0, projB1), glm::max(projB2, projB3));

            // 如果存在分离轴，则未碰撞，直接返回
            if (maxA < minB || maxB < minA)
            {
                return info;
            }

            // 计算当前轴上的重叠量
            float overlap = glm::min(maxA, maxB) - glm::max(minA, minB);
            if (overlap < minOverlap) {
                minOverlap = overlap;
                minAxis = axis;
            }
        }

        // 如果循环结束，说明没有分离轴，两个矩形相交
        info.Collided = true;
        info.Depth = minOverlap;  // 将最小重叠量记录为碰撞深度

        // 计算两个矩形的中心点
        glm::vec2 centerA = (rectA[0] + rectA[1] + rectA[2] + rectA[3]) / 4.0f;
        glm::vec2 centerB = (rectB[0] + rectB[1] + rectB[2] + rectB[3]) / 4.0f;

        // 计算中心点连线向量（从rectB指向rectA）
        glm::vec2 diff = centerA - centerB;

        // 使用点积确定minAxis的方向
        // 如果点积为负，则反转minAxis，使其从rectB指向rectA
        float dotProduct = glm::dot(diff, minAxis);
        if (dotProduct < 0) {
            minAxis = -minAxis;
        }

        // 将minAxis设置为碰撞方向
        info.Direction = minAxis;

        return info;
    }
}