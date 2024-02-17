#ifndef YUMEGL_CAMERA_HPP
#define YUMEGL_CAMERA_HPP

#include "../../config.h"
#include "../../yume.h"

#include "src/engine/input/input.hpp"

namespace object {
    class Camera3D { // >>>>>>>> IN EARLY DEVELOPMENT <<<<<<<<
    public:
        glm::vec3 position{ 0.0f, 0.0f, 3.0f };
        glm::vec3 front{ 0.0f, 0.0f, -1.0f };
        glm::vec3 up{ 0.0f, 1.0f, 0.0f };

        float sensitivity{ 0.16f };
        bool firstMouse{ true };
        bool active{ true };
        bool freeCam{ false };
        bool boobing{ true };

        Camera3D(glm::uvec3 position_value, unsigned int window_width, unsigned int window_height, bool free_cam);

        void update(float deltaTime);
        static void mouseCallback(GLFWwindow* window, double xPos, double yPos);
        void changeCursorVisibility();
        void setWindowSize(unsigned int width, unsigned int height);
        void update(const shaderSystem::Shader& shader) const;

    private:
        float posY{ 0.0f };
        float yaw{ -90.0f };
        float pitch{ 0.0f };
        float lastX{ 800.0f / 2.0 };
        float lastY{ 600.0f / 2.0 };
        float fov{ 45.0f };
        
        bool moving{ false };

        float windowWidth{};
        float windowHeight{};
    };

    Camera3D::Camera3D(glm::uvec3 position_value, unsigned int window_width, unsigned int window_height, bool free_cam) {
        glfwSetCursorPosCallback(yumegl::_window, Camera3D::mouseCallback);
        glfwSetWindowUserPointer(yumegl::_window, this);

        position = position_value;
        freeCam = free_cam;
        posY = position_value.y;

        setWindowSize(window_width, window_height);
    }

    void Camera3D::setWindowSize(const unsigned int width, const unsigned int height) {
        windowWidth = (float)width;
        windowHeight = (float)height;
    }

    void Camera3D::update(float deltaTime) {
        auto cameraSpeed = static_cast<float>((input::keyDown(GLFW_KEY_LEFT_SHIFT) ? 24.0f : 16.0f) * deltaTime);

        // MOVEMENT
        if (input::keyDown(GLFW_KEY_W))
            position += cameraSpeed * front;
        if (input::keyDown(GLFW_KEY_S))
            position -= cameraSpeed * front;
        if (input::keyDown(GLFW_KEY_A))
            position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
        if (input::keyDown(GLFW_KEY_D))
            position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

        if (input::keyDown(GLFW_KEY_W) || input::keyDown(GLFW_KEY_S) || input::keyDown(GLFW_KEY_A) || input::keyDown(GLFW_KEY_D))
            moving = true;
        else
            moving = false;

        // SHORTCUTS
        if (input::keyDown(GLFW_KEY_Y) && input::keyDown(GLFW_KEY_EQUAL))
            posY += cameraSpeed;
        else if (input::keyDown(GLFW_KEY_Y) && input::keyDown(GLFW_KEY_MINUS))
            posY -= cameraSpeed;

        if (input::keyDown(GLFW_KEY_M) && input::keyDown(GLFW_KEY_EQUAL))
            sensitivity += 0.0005f;
        else if (input::keyDown(GLFW_KEY_M) && input::keyDown(GLFW_KEY_MINUS))
            sensitivity -= 0.0005f;

        if (input::keyPressed(GLFW_KEY_P))
            active = !active;

        if (input::keyPressed(GLFW_KEY_F))
            freeCam = !freeCam;

        if (!freeCam && moving && boobing) {
            auto time = (float)glfwGetTime();
            auto yOffset = sin(time * 14) * cameraSpeed * 1.4f;
            position.y = (float)posY + (float)yOffset;
        }
    }

    void Camera3D::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
        auto* camera = static_cast<Camera3D*>(glfwGetWindowUserPointer(window));
        if (camera == nullptr)
            return;

        if (camera->active) {
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

            if(camera->freeCam)
                camera->posY = camera->position.y;
        }
    }

    void Camera3D::update(const shaderSystem::Shader& shader) const {
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        glm::mat4 view = glm::lookAt(position, position + front, up);
        shader.setMat4("view", view);

        glfwSetInputMode(yumegl::_window, GLFW_CURSOR, active ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    void Camera3D::changeCursorVisibility() {
        active = !active;
    }
}
#endif
