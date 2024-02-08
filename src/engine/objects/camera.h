#ifndef YUMEGL_CAMERA_H
#define YUMEGL_CAMERA_H

#include "../../config.h"
#include "../../yume.h"

namespace object {
    class Camera3D { // >>>>>>>> IN EARLY DEVELOPMENT <<<<<<<< learning from learn opengl
    public:
        glm::vec3 position = {0.0f, 0.0f, 3.0f};
        glm::vec3 front = {0.0f, 0.0f, -1.0f};
        glm::vec3 up = {0.0f, 1.0f, 0.0f};

        float sensitivity = 0.3f;
        bool firstMouse = true;

        Camera3D(unsigned int window_width, unsigned int window_height);

        void updateCameraInput(float deltaTime);
        static void mouseCallback(GLFWwindow* window, double xPos, double yPos);
        void setWindowSize(unsigned int width, unsigned int height);
        void update(Shader shader) const;

    private:
        float yaw = -90.0f;
        float pitch = 0.0f;
        float lastX = 800.0f / 2.0;
        float lastY = 600.0f / 2.0;
        float fov = 45.0f;

        float windowWidth{};
        float windowHeight{};
    };

    Camera3D::Camera3D(unsigned int window_width, unsigned int window_height) {
        glfwSetCursorPosCallback(yumegl::_window, Camera3D::mouseCallback);
        glfwSetWindowUserPointer(yumegl::_window, this);

        setWindowSize(window_width, window_height);
    }

    void Camera3D::setWindowSize(const unsigned int width, const unsigned int height) {
        windowWidth = (float)width;
        windowHeight = (float)height;
    }

    void Camera3D::updateCameraInput(float deltaTime) {
        auto cameraSpeed = static_cast<float>(5.0 * deltaTime);

        if (input::keyDown(GLFW_KEY_W))
            position += cameraSpeed * front;
        if (input::keyDown(GLFW_KEY_S))
            position -= cameraSpeed * front;
        if (input::keyDown(GLFW_KEY_A))
            position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
        if (input::keyDown(GLFW_KEY_D))
            position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

        // -------------- fps style
        position.y = 0.0f;
    }

    void Camera3D::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
        auto* camera = static_cast<Camera3D*>(glfwGetWindowUserPointer(window));
        if (camera == nullptr)
            return;

        if (camera->firstMouse) {
            camera->lastX = (float)xPos;
            camera->lastY = (float)yPos;

            camera->firstMouse = false;
        }

        float xOffset = ((float)xPos - camera->lastX) * camera->sensitivity;
        float yOffset = (camera->lastY - (float)yPos) * camera->sensitivity;

        camera->lastX = (float)xPos;
        camera->lastY = (float)yPos;

        camera->yaw += xOffset;
        camera->pitch += yOffset;

        if (camera->pitch > 89.0f)
            camera->pitch = 89.0f;
        if (camera->pitch < -89.0f)
            camera->pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
        front.y = sin(glm::radians(camera->pitch));
        front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));

        camera->front = glm::normalize(front);
    }

    void Camera3D::update(Shader shader) const {
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        glm::mat4 view = glm::lookAt(position, position + front, up);
        shader.setMat4("view", view);
    }
}
#endif
