#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

// 表示球体的结构体
struct Sphere {
    glm::vec3 center;      // 球心位置
    float radius;          // 半径
    int materialIndex;     // 材质索引
};

// 表示材质的结构体
struct Material {
    glm::vec3 color;       // 颜色
    float reflectivity;    // 反射率
    float refractivity;    // 折射率
    // 可根据需要添加其他属性
};

// 表示光源的结构体
struct Light {
    glm::vec3 position;    // 位置
    glm::vec3 intensity;   // 强度
    // 可根据需要添加其他属性
};

class Scene {
public:
    std::vector<Sphere> spheres;      // 存储所有球体
    std::vector<Material> materials;  // 存储所有材质
    std::vector<Light> lights;        // 存储所有光源

    GLuint sphereBuffer;              // 球体数据的 SSBO
    GLuint materialBuffer;            // 材质数据的 SSBO
    GLuint lightBuffer;               // 光源数据的 SSBO

    // 构造函数，初始化缓冲区
    Scene() {
        glGenBuffers(1, &sphereBuffer);
        glGenBuffers(1, &materialBuffer);
        glGenBuffers(1, &lightBuffer);
    }

    // 析构函数，清理缓冲区
    ~Scene() {
        glDeleteBuffers(1, &sphereBuffer);
        glDeleteBuffers(1, &materialBuffer);
        glDeleteBuffers(1, &lightBuffer);
    }

    // 添加球体
    void addSphere(const Sphere& sphere) {
        spheres.push_back(sphere);
    }

    // 添加材质
    void addMaterial(const Material& material) {
        materials.push_back(material);
    }

    // 添加光源
    void addLight(const Light& light) {
        lights.push_back(light);
    }

    // 将数据上传到 GPU
    void uploadToGPU() {
        // 上传球体数据
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, sphereBuffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
            spheres.size() * sizeof(Sphere),
            spheres.data(),
            GL_STATIC_DRAW);

        // 上传材质数据
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialBuffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
            materials.size() * sizeof(Material),
            materials.data(),
            GL_STATIC_DRAW);

        // 上传光源数据
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, lightBuffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
            lights.size() * sizeof(Light),
            lights.data(),
            GL_STATIC_DRAW);
    }

    // 绑定缓冲区以供计算着色器使用
    void bindBuffers() {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, sphereBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, materialBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, lightBuffer);
    }
};