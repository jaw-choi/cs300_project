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

    void InitBunny();
    void InitSphere();
    void InitOrbit();
    void Init4Sphere();
    void Initcube2();
    void InitSphere_();
    void InitSphereModified();
    void SetView();
    void DrawBeforeImGui();

    std::vector<Mesh> meshes;

    const GLfloat bgColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    //const GLfloat one = 1.0f;
    Vec4 useNormal = Vec4(0.9f, 0.9f, 0.9f, 1.0f);

private:
    Camera camera;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 eye;
    glm::vec3 light;
    bool vertxNrm[5] = { false,false,false,false,false };
    bool faceNrm[5] = { false,false,false,false,false };
    bool meshSwitch[5] = { true,false,false,false,false };
    //bool is_switch_pressed(const char* buttonName, bool& buttonType);
    //void onOffSwitch();
};
