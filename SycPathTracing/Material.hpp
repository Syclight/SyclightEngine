#pragma once

#include <glm/glm.hpp>

class Material {
public:
    glm::vec3 color;       // 基础颜色（RGB）
    float ambient;         // 环境光系数 [0, 1]
    float diffuse;         // 漫反射系数 [0, 1]
    float specular;        // 镜面反射系数 [0, 1]
    float shininess;       // 镜面高光的光泽度（越大高光越小）
    float reflectivity;    // 反射率 [0, 1]
    float refractivity;    // 折射率（典型值为 1.0 到 2.0，0 表示无折射）

    // 构造函数
    Material(const glm::vec3& col = glm::vec3(1.0f),
        float amb = 0.1f, float diff = 0.9f, float spec = 0.5f,
        float shiny = 32.0f, float refl = 0.0f, float refr = 0.0f)
        : color(col), ambient(amb), diffuse(diff), specular(spec),
        shininess(shiny), reflectivity(refl), refractivity(refr) {
    }

    // 设置材质属性
    void set(const glm::vec3& col, float amb, float diff, float spec,
        float shiny, float refl, float refr) {
        color = col;
        ambient = amb;
        diffuse = diff;
        specular = spec;
        shininess = shiny;
        reflectivity = refl;
        refractivity = refr;
    }
};