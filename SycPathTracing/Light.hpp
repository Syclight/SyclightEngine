#pragma once

#include <glm/glm.hpp>

class Light {
public:
    glm::vec3 position;    // 光源位置
    glm::vec3 intensity;   // 光源强度和颜色（RGB）

    // 构造函数
    Light(const glm::vec3& pos = glm::vec3(0.0f),
        const glm::vec3& inten = glm::vec3(1.0f))
        : position(pos), intensity(inten) {
    }
};