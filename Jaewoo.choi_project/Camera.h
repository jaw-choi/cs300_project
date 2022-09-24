//Name: Jaewoo Choi
//Assignment name: Assignment_1
//Course name: CS300
//Term & Year : 2022&Fall
#pragma once
#include <GL/glew.h> 
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
class Camera
{
public:
    Camera() = default;
    Camera(glm::vec3 eye);
    Camera(glm::vec3 eye, glm::vec3 direction);
    void Update(float dt);
    glm::vec3 mouse_update(float dt);
    glm::mat4& GetViewMatrix();
    glm::vec3 GetEye();

    glm::mat4      view = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    };
    glm::vec3 eye{ 0 }; //camera position
    glm::vec3 cameraTarget{ 0 }; //view target
    glm::vec3 cameraDirection{ 0 }; //view direction
    glm::vec3 cameraUp{ 0 };
    glm::vec3 cameraRight{ 0 };
    glm::vec2 direction{ 0 };
    float pitch{ 0 };
    float yaw{ 0 };
    glm::vec3 angle{ 0 };
};