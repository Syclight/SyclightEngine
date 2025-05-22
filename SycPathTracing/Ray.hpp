#pragma once

#include <glm/glm.hpp>

class Ray {
public:
    glm::vec3 origin;      // 光线起点
    glm::vec3 direction;   // 光线方向（单位向量）
    float tMax;            // 光线传播的最大距离

    // 构造函数
    Ray(const glm::vec3& orig, const glm::vec3& dir, float maxT = INFINITY)
        : origin(orig), direction(glm::normalize(dir)), tMax(maxT) {
    }

    // 获取光线在参数 t 处的点
    glm::vec3 at(float t) const {
        return origin + t * direction;
    }
};