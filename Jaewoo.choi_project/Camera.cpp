//Name: Jaewoo Choi
//Assignment name: Assignment_1
//Course name: CS300
//Term & Year : 2022&Fall
#include "Camera.h"
#include"glhelper.h"
#include "glm/gtc/matrix_transform.hpp"
Camera::Camera(glm::vec3 eye) :eye(eye), pitch(0), yaw(-90.0f), angle(0)
{
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = glm::vec3(eye - cameraTarget);

    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::cross(cameraDirection, cameraRight);
    view = glm::translate(view, eye);
    //view = glm::rotate(view, 3.14159f, glm::vec3(1.0f, 0.0f, 0.0f));
}
Camera::Camera(glm::vec3 eye, glm::vec3 direction) :eye(eye), cameraDirection(direction), pitch(0), yaw(-90.0f), angle(0)
{
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
    cameraUp = glm::cross(direction, cameraRight);
}
void Camera::Update(float dt)
{
    float speed = 0.0005f;

    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_UP))
    {
        eye.y += speed * dt;
    }
    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_DOWN))
    {
        eye.y -= speed * dt;
    }
    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_W))
    {
        eye += speed * dt * cameraFront;
    }
    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_S))
    {
        eye -= speed * dt * cameraFront;
    }
    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_A))
    {
        eye -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * dt;
    }
    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_D))
    {
        eye += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * dt;
    }
    //view = glm::translate(view, eye);

    view = glm::lookAt(eye, eye + cameraFront, cameraUp);

}
glm::vec3 Camera::mouse_update(float)
{
    double mouse_pos_x = 0;
    double mouse_pos_y = 0;
    static glm::vec2 start_pos{ 0 };
    static bool mouse_start = false;
    glfwGetCursorPos(GLHelper::ptr_window, &mouse_pos_x, &mouse_pos_y);

    glm::mat4 rotate = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    };
    if (GLHelper::mouse_pressed == true)
    {
        if (mouse_start == false)
        {
            start_pos.x = static_cast<float>(mouse_pos_x);
            start_pos.y = static_cast<float>(mouse_pos_y);
            mouse_start = true;
        }
        float xoffset = static_cast<float>(mouse_pos_x - start_pos.x);
        float yoffset = static_cast<float>(start_pos.y - mouse_pos_y);
        start_pos.x = static_cast<float>(mouse_pos_x);
        start_pos.y = static_cast<float>(mouse_pos_y);

        yaw += xoffset * 0.07f;
        pitch += yoffset * 0.07f;
    }
    else
    {
        mouse_start = false;
    }

    glm::vec3 direction= cameraDirection;
    direction.x += cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y += sin(glm::radians(pitch));
    direction.z += sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
    cameraRight = glm::normalize(glm::cross(direction, cameraUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    cameraUp = glm::normalize(glm::cross(cameraRight, direction));
    return (direction);
}
glm::mat4& Camera::GetViewMatrix()
{
    return view;
}

glm::vec3 Camera::GetEye()
{
    return eye;
}
