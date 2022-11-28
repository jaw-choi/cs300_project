/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: RendOBJ.h
Purpose: <This file contains the declaration of class RendOBJ that encapsulates the
functionality required to init and draw models>
Language: <c++>
Platform: <Visual studio 2019, OpenGL 4.5, Window 64 bit>
Project: <jaewoo.choi_CS300_3>
Author: <Jaewoo Choi, jaewoo.choi, 55532>
Creation date: 04/11/2022
End Header --------------------------------------------------------*/
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

    void InitPhongShading();
    void InitblinnLighting();
    void InitPhongLighting();

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
    GLuint FBO;

    const GLfloat bgColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    Vec4 useNormal = Vec4(0.9f, 0.9f, 0.9f, 1.0f);
    int numberLamp = 16;
    GLuint phongLightID = 0;
    GLuint phongShadingID = 0;
    GLuint blinnID = 0;

private:
    Camera camera;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 eye;
    glm::vec3 light;
    bool vertxNrm[5] = { false,false,false,false,false };
    bool faceNrm[5] = { false,false,false,false,false };
    bool meshSwitch[5] = { true,false,false,false,false };
    bool materialSwitch[10] = { true,false,false,false,false,false,false,false,false,false };

    int indexFresnel = 0;
    std::vector<float> RefractiveIndex;
    std::vector<float> FresnelConstant;
    float FresnelPower = 0.5;
    bool shaderSwitch[3] = { true,false,false };
    bool lightSwitch[16] = { false,};
    std::vector<DirLight> dirlight;
    bool isRotationLamp = false;
    int currentLamp = 0;
    int typeMapping = 1;
    std::vector<lampSet> lampSetting;
    Global global{};
    Material mate{};
    bool reflection = true;
    bool refraction = true;
    int shaderType = 0;
    std::vector<GLuint> cubemapTexture;
    std::vector<std::string> faces
    {
            "../textures/right.jpg",
            "../textures/left.jpg",
            "../textures/top.jpg",
            "../textures/bottom.jpg",
            "../textures/front.jpg",
            "../textures/back.jpg"
    };
};
