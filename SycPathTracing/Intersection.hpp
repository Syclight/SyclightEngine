#pragma once

#include <glm/glm.hpp>
#include <limits>

class Intersection {
public:
    float t;               // 光线参数 t
    glm::vec3 point;       // 相交点坐标
    glm::vec3 normal;      // 相交点法线
    int objectIndex;       // 相交物体的索引
    bool hit;              // 是否相交

    // 默认构造函数，初始化为无相交状态
    Intersection()
        : t(std::numeric_limits<float>::max()),
        point(0.0f),
        normal(0.0f),
        objectIndex(-1),
        hit(false) {
    }

    // 设置相交信息
    void set(float tVal, const glm::vec3& p, const glm::vec3& n, int objIdx) {
        t = tVal;
        point = p;
        normal = n;
        objectIndex = objIdx;
        hit = true;
    }

    // 重置为无相交状态
    void reset() {
        t = std::numeric_limits<float>::max();
        point = glm::vec3(0.0f);
        normal = glm::vec3(0.0f);
        objectIndex = -1;
        hit = false;
    }
};