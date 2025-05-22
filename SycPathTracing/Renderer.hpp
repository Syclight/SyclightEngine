#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Scene.hpp"
#include "Camera.hpp"

#include <fstream>
#include <sstream>

void uploadSceneToGPU(const Scene& scene, GLuint& sphereBuffer, GLuint& materialBuffer, GLuint& lightBuffer) {
    // 上传球体数据
    glGenBuffers(1, &sphereBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, sphereBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, scene.spheres.size() * sizeof(Sphere), scene.spheres.data(), GL_STATIC_DRAW);

    // 上传材质数据
    glGenBuffers(1, &materialBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, scene.materials.size() * sizeof(Material), scene.materials.data(), GL_STATIC_DRAW);

    // 上传光源数据
    glGenBuffers(1, &lightBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, lightBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, scene.lights.size() * sizeof(Light), scene.lights.data(), GL_STATIC_DRAW);
}

class Renderer {
public:
    GLuint program, outputTexture;
    Scene scene;
    Camera camera;

    Renderer(int w, int h) : camera(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), 60.0f), width(w), height(h) {
        initShader();
        initTexture();
    }

    void initShader() {
        // 编译并链接计算着色器（假设代码已加载到字符串 shaderSource）

        std::ifstream file("PathTracing.glsl");
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();  // 将文件内容加载到字符串流中
        std::string shaderSource = buffer.str();
        source = shaderSource.c_str();

        program = glCreateProgram();
        GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        glAttachShader(program, shader);
        glLinkProgram(program);
        glDeleteShader(shader);
    }

    void initTexture() {
        glGenTextures(1, &outputTexture);
        glBindTexture(GL_TEXTURE_2D, outputTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
        glBindImageTexture(0, outputTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    }

    void render() {
        glUseProgram(program);

        // 上传场景和相机数据
        GLuint sphereBuffer, materialBuffer, lightBuffer;
        uploadSceneToGPU(scene, sphereBuffer, materialBuffer, lightBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, sphereBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, materialBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, lightBuffer);
        camera.uploadToShader(program);

        glUniform1i(glGetUniformLocation(program, "width"), width);
        glUniform1i(glGetUniformLocation(program, "height"), height);

        // 调度计算着色器
        glDispatchCompute((width + 15) / 16, (height + 15) / 16, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }

private:
    int width, height;
    const char* source = nullptr;
};
