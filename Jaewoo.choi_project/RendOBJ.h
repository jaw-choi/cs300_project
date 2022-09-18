//Name: Jaewoo Choi
//Assignment name: Assignment_1
//Course name: CS300
//Term & Year : 2022&Fall
/*!
@file    RendOBJ.h
@author  Jaewoo.choi
@date    14/09/2022

Note : 

*//*__________________________________________________________________________*/
#pragma once

#include"Mesh.h"
#include "Camera.h"

class RendOBJ
{
public:
    RendOBJ();
    ~RendOBJ();
    void init();
    void Update(float deltaTime);
    void Draw();
    void OnImGuiRender();
    void UnLoad();


    void SetView();

    std::vector<Mesh> meshes;

    const GLfloat bgColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    //const GLfloat one = 1.0f;
    Vec4 useNormal = Vec4(1.f, 0.2f, 0.4f, 1.0f);

private:

    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 eye;
    glm::vec3 light;

    //bool meshSwitch[NUM_MESHES] = { true,true,true,true,true/*,true*/ };
    //bool is_switch_pressed(const char* buttonName, bool& buttonType);
    //void onOffSwitch();
};