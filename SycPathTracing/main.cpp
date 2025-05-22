#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "Renderer.hpp"  // 假设路径追踪渲染器定义在此头文件中

// 顶点着色器
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
)";

// 片段着色器
const char* fragmentShaderSource = R"(
#version 330 core
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D screenTexture;
void main() {
    FragColor = texture(screenTexture, TexCoord);
}
)";

int main() {
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 配置 GLFW，使用 OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Path Tracer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 初始化路径追踪渲染器
    Renderer renderer(1280, 720);  // 假设 Renderer 类接受窗口宽度和高度

    // 设置示例场景（根据你的路径追踪实现调整）
    renderer.scene.addSphere({ glm::vec3(0, 0, -1), 1.0f, 0 });
    renderer.scene.addMaterial({ glm::vec3(0.8, 0.2, 0.2), 0.5f, 0.0f });
    renderer.scene.addLight({ glm::vec3(5, 5, 5), glm::vec3(10, 10, 10) });
    renderer.scene.uploadToGPU();

    // 定义全屏四边形的顶点数据（位置和纹理坐标）
    float vertices[] = {
        // 位置       // 纹理坐标
        -1.0f, -1.0f,  0.0f, 0.0f, // 左下
         1.0f, -1.0f,  1.0f, 0.0f, // 右下
        -1.0f,  1.0f,  0.0f, 1.0f, // 左上
         1.0f,  1.0f,  1.0f, 1.0f  // 右上
    };

    // 设置 VAO 和 VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 配置顶点属性
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // 位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // 纹理坐标
    glEnableVertexAttribArray(1);

    // 编译顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 编译片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // 创建并链接着色器程序
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 删除不再需要的着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 执行路径追踪渲染
        renderer.render();

        // 清空屏幕
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用着色器程序绘制全屏四边形
        glUseProgram(shaderProgram);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderer.outputTexture);  // 绑定路径追踪生成的纹理
        glUniform1i(glGetUniformLocation(shaderProgram, "screenenezTexture"), 0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  // 绘制四边形

        // 交换缓冲区并处理事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}