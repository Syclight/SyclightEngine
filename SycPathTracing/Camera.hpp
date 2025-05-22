class Camera {
public:
    glm::vec3 position;
    glm::vec3 lookAt;
    float fov; // 视野角度（度）

    Camera(const glm::vec3& pos, const glm::vec3& target, float f)
        : position(pos), lookAt(target), fov(f) {
    }

    void uploadToShader(GLuint program) {
        glUniform3fv(glGetUniformLocation(program, "cameraPos"), 1, &position[0]);
        glUniform3fv(glGetUniformLocation(program, "cameraLookAt"), 1, &lookAt[0]);
        glUniform1f(glGetUniformLocation(program, "cameraFov"), fov);
    }
};