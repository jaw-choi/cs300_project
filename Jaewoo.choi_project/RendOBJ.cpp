/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: RendOBJ.cpp
Purpose: <This file contains the definitions of class RendOBJ that encapsulates the
functionality required to init and draw models>
Language: <c++>
Platform: <Visual studio 2019, OpenGL 4.5, Window 64 bit>
Project: <jaewoo.choi_CS300_2>
Author: <Jaewoo Choi, jaewoo.choi, 55532>
Creation date: 04/11/2022
End Header --------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "RendOBJ.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "Camera.h"

RendOBJ::RendOBJ() :view{ 0 }, projection{ 0 }, light{ 0 }, eye{ 0 }{}

RendOBJ::~RendOBJ() {}

void RendOBJ::init()
{
    meshes.push_back(LoadOBJ("../object/quad.obj"));
    meshes[0].init("../shaders/PhongShading.vert", "../shaders/PhongShading_plain.frag", phongShadingID, phongLightID, blinnID,{ 0,-0.5f,0 }, { 5.f,5.f,1.f }, { -HALF_PI,0,0 }, numberLamp);
    meshes[0].setTexture();

    float theta = 0;
    float angle = TWO_PI / numberLamp;
    for (int i = 0; i < numberLamp; i++)
    {
        theta = angle * i;
        lampSetting.push_back(lampSet());
        dirlight.push_back(DirLight());

        dirlight[i].position = { 2 * cos(theta),0,2 * sin(theta)};
    }
    meshes.push_back(CreateSphere(60, 60));
    meshes[1].initLamp("../shaders/lamp.vert", "../shaders/lamp.frag");

    meshes.push_back(CreateOrbit(100));
    meshes[2].initLine("../shaders/line.vert", "../shaders/line.frag", { 0,0,0 }, { 1.f,1.f,1.f }, { 0,0,0 });

    meshes.push_back(LoadOBJ("../object/bunny_high_poly.obj"));
    //meshes[3].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", { 0,0,0 }, { 1.f,1.f,1.f }, { 0,0,0 }, numberLamp);
    

    meshes.push_back(LoadOBJ("../object/sphere.obj"));
   // meshes[4].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", { 0,0,0 }, { 1.f,1.f,1.f }, { 0,0,0 }, numberLamp);

    meshes.push_back(LoadOBJ("../object/cube2.obj"));
    //meshes[5].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", { 0,0,0 }, { 1.f,1.f,1.f }, { 0,0,0 }, numberLamp);

    meshes.push_back(LoadOBJ("../object/4Sphere.obj"));
    //meshes[6].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", { 0,0,0 }, { 1.f,1.f,1.f }, { 0,0,0 }, numberLamp);

    meshes.push_back(LoadOBJ("../object/bunny.obj"));
    //meshes[7].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", { 0,0,0 }, { 1.f,1.f,1.f }, { 0,0,0 }, numberLamp);
    
    InitPhongLighting();
    InitblinnLighting();
    InitPhongShading();

    camera = { {0.f, 3.f, 10.0f} };

    SetView();
    
}

void RendOBJ::Update(float deltaTime)
{
    camera.Update(deltaTime);
    //meshes[10].position = { light.x,-light.y,light.z };
    if (!isRotationLamp)
        for (int i = 0; i < numberLamp; i++)
            dirlight[i].position = glm::vec4(2 * cos((i * (TWO_PI / (float)numberLamp)) + deltaTime), 0, 2 * sin(i * (TWO_PI / (float)numberLamp) + deltaTime), 1.f);

}

void RendOBJ::Draw()
{
    glClearColor(global.fogColor.x, global.fogColor.y, global.fogColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    meshes[0].draw(camera.GetViewMatrix(), projection, light, camera.GetEye(), dirlight, numberLamp,global, mate);
    meshes[1].drawLamp(camera.GetViewMatrix(), projection, numberLamp, dirlight, lampSetting);
    meshes[2].drawLine({ 1,1,1 }, camera.GetViewMatrix(), projection, light, camera.GetEye(), {0,0});
    //meshes[3].drawLight(camera.GetViewMatrix(), projection, light, camera.GetEye(), dirlight, numberLamp);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Demo");
    OnImGuiRender();


    ImGui::Begin("Controls");
    DrawBeforeImGui();

    //meshes[10].drawLight(camera.GetViewMatrix(), projection, light, camera.GetEye(), dirlight);

}

void RendOBJ::OnImGuiRender()
{
    const char* Lightitems[16] = { "Light#1","Light#2", "Light#3", "Light#4",
    "Light#5","Light#6", "Light#7", "Light#8",
    "Light#9","Light#10", "Light#11", "Light#12",
    "Light#13","Light#14", "Light#15", "Light#16", };
    static const char* light_current_item = Lightitems[0];

    const char* LightType[3] = { "Point","Direction", "Spot"};
    static const char* type_current_item = LightType[0];

    if (ImGui::CollapsingHeader("Light"))
    {
        ImGui::SliderInt("Light Number", &numberLamp, 1, 16, "%d", 0);
        numberLamp = numberLamp;

        ImGui::Checkbox("Pause Rotation", &isRotationLamp);
        if(ImGui::Button("Scenario 1")){
            int j = 0;
            for (int i = 0; i < 16; i++)
            {
                lightSwitch[i] = false;
            }
            for (int i = 0; i < 6; i++)
            {
                lightSwitch[i] = true;
                dirlight[i].type = 0;
                dirlight[i].ambient = { 1.f,1.f,1.f };
                dirlight[i].diffuse = { 1.f,1.f,1.f };
                dirlight[i].specular = { 1.f,1.f,1.f };
                lampSetting[i].Diffuse = { 1.f,1.f,1.f,1.f };
                j++;
            }
            type_current_item = LightType[0];
            global.attenuation.z = 2.f;
            numberLamp = 6;
        }
        if(ImGui::Button("Scenario 2")){
            int j = 0;
            float a = 1.f/255.f;
            for (int i = 0; i < 16; i++)
            {
                lightSwitch[i] = false;
            }
            for (int i = 0; i < 7; i++)
            {
                lightSwitch[i] = true;
                dirlight[i].type = 2;
                j++;
            }
            dirlight[0].ambient = { 59 * a,234 * a,21 * a };
            dirlight[0].diffuse = dirlight[0].ambient;
            dirlight[0].specular = dirlight[0].ambient;
            lampSetting[0].Diffuse = { dirlight[0].ambient ,1.0f };
            dirlight[1].ambient = { 22 * a,89 * a,248 * a };
            dirlight[1].diffuse = dirlight[1].ambient;
            dirlight[1].specular = dirlight[1].ambient;
            lampSetting[1].Diffuse = { dirlight[1].ambient ,1.0f };
            dirlight[2].ambient = { 244 * a,15 * a,15 * a };
            dirlight[2].diffuse = dirlight[2].ambient;
            dirlight[2].specular = dirlight[2].ambient;
            lampSetting[2].Diffuse = { dirlight[2].ambient ,1.0f };
            dirlight[3].ambient = { 204 * a,28 * a,225 * a };
            dirlight[3].diffuse = dirlight[3].ambient;
            dirlight[3].specular = dirlight[3].ambient;
            lampSetting[3].Diffuse = { dirlight[3].ambient ,1.0f };
            dirlight[4].ambient = { 29 * a,227 * a,179 * a };
            dirlight[4].diffuse = dirlight[4].ambient;
            dirlight[4].specular = dirlight[4].ambient;
            lampSetting[4].Diffuse = { dirlight[4].ambient ,1.0f };
            dirlight[5].ambient = { 226 * a,215 * a,28 * a };
            dirlight[5].diffuse = dirlight[5].ambient;
            dirlight[5].specular = dirlight[5].ambient;
            lampSetting[5].Diffuse = { dirlight[5].ambient ,1.0f };
            
            dirlight[6].ambient = { 226 * a,184 * a,28 * a };
            dirlight[6].diffuse = dirlight[6].ambient;
            dirlight[6].specular = dirlight[6].ambient;
            lampSetting[6].Diffuse = { dirlight[6].ambient ,1.0f };
            global.attenuation.z = 0.45f;
            type_current_item =  LightType[2];
            numberLamp = j;


        }
        if(ImGui::Button("Scenario 3")){
            int j = 0;
            float a = 1.f / 255.f;
            for (int i = 0; i < 16; i++)
            {
                lightSwitch[i] = false;
            }
            for (int i = 0; i < 11; i++)
            {
                lightSwitch[i] = true;
                dirlight[i].type = 0;
                j++;
            }
            dirlight[0].ambient = { 59 * a,234 * a,21 * a };
            dirlight[0].diffuse = dirlight[0].ambient;
            dirlight[0].specular = dirlight[0].ambient;
            lampSetting[0].Diffuse = { dirlight[0].ambient ,1.0f };

            dirlight[1].ambient = { 22 * a,89 * a,248 * a };
            dirlight[1].diffuse = dirlight[1].ambient;
            dirlight[1].specular = dirlight[1].ambient;
            lampSetting[1].Diffuse = { dirlight[1].ambient ,1.0f };

            dirlight[2].ambient = { 244 * a,15 * a,15 * a };
            dirlight[2].diffuse = dirlight[2].ambient;
            dirlight[2].specular = dirlight[2].ambient;
            lampSetting[2].Diffuse = { dirlight[2].ambient ,1.0f };

            dirlight[3].ambient = { 204 * a,28 * a,225 * a };
            dirlight[3].diffuse = dirlight[3].ambient;
            dirlight[3].specular = dirlight[3].ambient;
            lampSetting[3].Diffuse = { dirlight[3].ambient ,1.0f };

            dirlight[4].ambient = { 29 * a,227 * a,179 * a };
            dirlight[4].diffuse = dirlight[4].ambient;
            dirlight[4].specular = dirlight[4].ambient;
            lampSetting[4].Diffuse = { dirlight[4].ambient ,1.0f };

            dirlight[5].ambient = { 226 * a,215 * a,28 * a };
            dirlight[5].diffuse = dirlight[5].ambient;
            dirlight[5].specular = dirlight[5].ambient;
            lampSetting[5].Diffuse = { dirlight[5].ambient ,1.0f };

            dirlight[6].ambient = { 226 * a,184 * a,28 * a };
            dirlight[6].diffuse = dirlight[6].ambient;
            dirlight[6].specular = dirlight[6].ambient;
            lampSetting[6].Diffuse = { dirlight[6].ambient ,1.0f };

            dirlight[7].ambient = { 59 * a,234 * a,21 * a };
            dirlight[7].diffuse = dirlight[7].ambient;
            dirlight[7].specular = dirlight[7].ambient;
            lampSetting[7].Diffuse = { dirlight[7].ambient ,1.0f };

            dirlight[8].ambient = { 22 * a,89 * a,248 * a };
            dirlight[8].diffuse = dirlight[8].ambient;
            dirlight[8].specular = dirlight[8].ambient;
            lampSetting[1].Diffuse = { dirlight[8].ambient ,1.0f };

            dirlight[9].ambient = { 244 * a,15 * a,15 * a };
            dirlight[9].diffuse = dirlight[9].ambient;
            dirlight[9].specular = dirlight[9].ambient;
            lampSetting[9].Diffuse = { dirlight[9].ambient ,1.0f };

            dirlight[10].ambient = { 204 * a,28 * a,225 * a };
            dirlight[10].diffuse = dirlight[10].ambient;
            dirlight[10].specular = dirlight[10].ambient;
            lampSetting[10].Diffuse = { dirlight[10].ambient ,1.0f };

            dirlight[11].ambient = { 29 * a,227 * a,179 * a };
            dirlight[11].diffuse = dirlight[11].ambient;
            dirlight[11].specular = dirlight[11].ambient;
            lampSetting[11].Diffuse = { dirlight[11].ambient ,1.0f };
            global.attenuation.z = 2.f;
            type_current_item = LightType[0];
            numberLamp = j;
        }
        if (ImGui::BeginCombo("Light Count", light_current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < 16; n++)
            {
                bool is_selected = (light_current_item == Lightitems[n]);
                if (ImGui::Selectable(Lightitems[n], is_selected))
                {
                    for (int i = 0; i < 16; i++)
                    {
                        lightSwitch[i] = false;
                    }
                    lightSwitch[n] = true;
                    light_current_item = Lightitems[n];
                    currentLamp = n;
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        if (ImGui::BeginCombo("Light type", type_current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < 3; n++)
            {
                bool is_selected = (dirlight[currentLamp].type == n);
                if (ImGui::Selectable(LightType[n], is_selected))
                {
                    dirlight[currentLamp].type = n;
                    type_current_item = LightType[n];
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::ColorEdit3("Ambient", &dirlight[currentLamp].ambient.x);
        ImGui::ColorEdit3("diffuse", &dirlight[currentLamp].diffuse.x);
        lampSetting[currentLamp].Diffuse.x = dirlight[currentLamp].diffuse.x;
        lampSetting[currentLamp].Diffuse.y = dirlight[currentLamp].diffuse.y;
        lampSetting[currentLamp].Diffuse.z = dirlight[currentLamp].diffuse.z;
        ImGui::ColorEdit3("Specular", &dirlight[currentLamp].specular.x);
        if (type_current_item == LightType[2])
        {
            ImGui::SliderFloat("Inner Angle", &dirlight[currentLamp].innerAngle, 0.f, 90.f);
            ImGui::SliderFloat("Outer Angle", &dirlight[currentLamp].outerAngle, 0.f, 90.f);
            if (dirlight[currentLamp].innerAngle > dirlight[currentLamp].outerAngle)
                dirlight[currentLamp].innerAngle = dirlight[currentLamp].outerAngle;
            ImGui::SliderFloat("Falloff", &dirlight[currentLamp].falloff, 0.f, 10.f);
        }
    }


    ImGui::Button("Camera can move with 'w','a','s','d','up','down'");
    ImGui::Button("Camera can move with 'up','down'");
}

void RendOBJ::UnLoad()
{
    meshes.clear();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //useNormal.r = 1;
}

void RendOBJ::InitPhongShading()
{
    
    meshes[3].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[4].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[5].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[6].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[7].init("../shaders/PhongShading.vert", "../shaders/PhongShading.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
}

void RendOBJ::InitblinnLighting()
{

    meshes[3].init("../shaders/lightBlinn.vert", "../shaders/lightBlinn.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[4].init("../shaders/lightBlinn.vert", "../shaders/lightBlinn.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[5].init("../shaders/lightBlinn.vert", "../shaders/lightBlinn.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[6].init("../shaders/lightBlinn.vert", "../shaders/lightBlinn.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[7].init("../shaders/lightBlinn.vert", "../shaders/lightBlinn.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
}

void RendOBJ::InitPhongLighting()
{
    meshes[3].init("../shaders/PhongLighting.vert", "../shaders/PhongLighting.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[4].init("../shaders/PhongLighting.vert", "../shaders/PhongLighting.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[5].init("../shaders/PhongLighting.vert", "../shaders/PhongLighting.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[6].init("../shaders/PhongLighting.vert", "../shaders/PhongLighting.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
    meshes[7].init("../shaders/PhongLighting.vert", "../shaders/PhongLighting.frag", phongShadingID, phongLightID, blinnID, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 0,0,0 }, numberLamp);
}

void RendOBJ::InitBunny()
{
    meshes.push_back(CreatePlane(2, 2));
   // meshes[0].init("../shaders/PhongShading.vert", "../shaders/triangle.frag", { 0,0,0 }, { 5.f,5.f,1.f }, { 0,0,0 }, false);
    //meshes.push_back(LoadOBJ("../object/quad.obj"));
    //meshes[0].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}


void RendOBJ::InitOrbit()
{
    meshes.push_back(CreateOrbit(100));
    meshes[9].initLine("../shaders/line.vert", "../shaders/line.frag", { 0,0,0 }, { 1.f,1.f,1.f }, { 0,0,0 });
}

void RendOBJ::Init4Sphere()
{
    meshes.push_back(LoadOBJ("../object/4Sphere.obj"));
    //meshes[10].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}

void RendOBJ::Initcube2()
{
    meshes.push_back(LoadOBJ("../object/cube2.obj"));
    //meshes[11].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}

void RendOBJ::InitSphere_()
{
    meshes.push_back(LoadOBJ("../object/sphere.obj"));
    //meshes[12].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}

void RendOBJ::InitSphereModified()
{
    meshes.push_back(LoadOBJ("../object/sphere_modified.obj"));
    //meshes[13].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}

void RendOBJ::SetView()
{
    view = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    };
    projection = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    };
    //eye = { 0.f, 0.f, 10.0f };
    light = { 0.0f, -2.0f, 0.0f };

    //view = glm::rotate(view, PI, glm::vec3(0.0f, 1.0f, 0.0f));

    //view = glm::rotate(view, PI, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, camera.eye);
    projection = glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f);

}

void RendOBJ::DrawBeforeImGui()
{

    const char* items[] = { "bunny_high_poly", "sphere", "cube2", "4Sphere", "bunny" };
    static const char* current_item = items[0];
    

    if (ImGui::CollapsingHeader("Model"))
    {
        if (ImGui::BeginCombo("Loaded Model", current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < 5; n++)
            {
                bool is_selected = (current_item == items[n]);
                if (ImGui::Selectable(items[n], is_selected))
                {
                    meshSwitch[0] = false;
                    meshSwitch[1] = false;
                    meshSwitch[2] = false;
                    meshSwitch[3] = false;
                    meshSwitch[4] = false;
                    meshSwitch[n] = true;
                    current_item = items[n];
                }
                if (is_selected)
                {
                    vertxNrm[0] = false;
                    vertxNrm[1] = false;
                    vertxNrm[2] = false;
                    vertxNrm[3] = false;
                    vertxNrm[4] = false;
                    faceNrm[0] = false;
                    faceNrm[1] = false;
                    faceNrm[2] = false;
                    faceNrm[3] = false;
                    faceNrm[4] = false;
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        if (current_item == items[0] && ImGui::Button("Vertex Normal"))
        {
            vertxNrm[0] = !vertxNrm[0];
        }
        if (current_item == items[0] && ImGui::Button("Face Normal"))
        {
            faceNrm[0] = !faceNrm[0];
        }
        if (current_item == items[1] && ImGui::Button("Vertex Normal"))
        {
            vertxNrm[1] = !vertxNrm[1];
        }
        if (current_item == items[1] && ImGui::Button("Face Normal"))
        {
            faceNrm[1] = !faceNrm[1];
        }
        if (current_item == items[2] && ImGui::Button("Vertex Normal"))
        {
            vertxNrm[2] = !vertxNrm[2];
        }
        if (current_item == items[2] && ImGui::Button("Face Normal"))
        {
            faceNrm[2] = !faceNrm[2];
        }
        if (current_item == items[3] && ImGui::Button("Vertex Normal"))
        {
            vertxNrm[3] = !vertxNrm[3];
        }
        if (current_item == items[3] && ImGui::Button("Face Normal"))
        {
            faceNrm[3] = !faceNrm[3];
        }

        if (current_item == items[4] && ImGui::Button("Vertex Normal"))
        {
            vertxNrm[4] = !vertxNrm[4];
        }
        if (current_item == items[4] && ImGui::Button("Face Normal"))
        {
            faceNrm[4] = !faceNrm[4];
        }
        
    }
    if (meshSwitch[0])
        meshes[3].drawLight(camera.GetViewMatrix(), projection, light, camera.GetEye(), dirlight, numberLamp, global, mate, typeMapping, shaderType, phongShadingID, phongLightID, blinnID);
    else if (meshSwitch[1])
        meshes[4].drawLight(camera.GetViewMatrix(), projection, light, camera.GetEye(), dirlight, numberLamp, global, mate, typeMapping, shaderType, phongShadingID, phongLightID, blinnID);
    else if (meshSwitch[2])
        meshes[5].drawLight(camera.GetViewMatrix(), projection, light, camera.GetEye(), dirlight, numberLamp, global, mate, typeMapping, shaderType, phongShadingID, phongLightID, blinnID);
    else if (meshSwitch[3])
        meshes[6].drawLight(camera.GetViewMatrix(), projection, light, camera.GetEye(), dirlight, numberLamp, global, mate, typeMapping, shaderType, phongShadingID, phongLightID, blinnID);
    else if (meshSwitch[4])
        meshes[7].drawLight(camera.GetViewMatrix(), projection, light, camera.GetEye(), dirlight, numberLamp, global, mate, typeMapping, shaderType, phongShadingID, phongLightID, blinnID);

    if (vertxNrm[0])
        meshes[3].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[0])
        meshes[3].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    if (vertxNrm[1])
        meshes[4].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[1])
        meshes[4].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    if (vertxNrm[2])
        meshes[5].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[2])
        meshes[5].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    if (vertxNrm[3])
        meshes[6].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[3])
        meshes[6].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    if (vertxNrm[4])
        meshes[7].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[4])
        meshes[7].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    const char* shade_items[] = { "phongShading", "phongLighting","blinnShading" };
    static const char* shade_current_item = shade_items[0];
    if (ImGui::CollapsingHeader("Shader"))
    {
        if (ImGui::BeginCombo("Current Shader", shade_current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < 3; n++)
            {
                bool is_selected = (shade_current_item == shade_items[n]);
                if (ImGui::Selectable(shade_items[n], is_selected))
                {
                    shaderType = n;
                    shade_current_item = shade_items[n];
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        if(ImGui::Button("reload shaders"))
        {
            ////////////////////////////////////////////////
        }
    }
    if(ImGui::CollapsingHeader("Material"))
    {
        ImGui::ColorEdit3("Ambient", &mate.ambient.x);
        ImGui::ColorEdit3("Diffuse",  &mate.diffuse.x);
        ImGui::ColorEdit3("Specular", &mate.specular.x);
        ImGui::ColorEdit3("Emissive", &mate.emissive.x);
        if (ImGui::Button("Visualize UV"))
        {
            meshes[0].setTextureGrid();
        }
        if (ImGui::Button("Visualize Texture"))
        {
            meshes[0].setTexture();
        }
        const char* T1_items[] = { "None","Cyndrical", "Spherical", "cube", "Planar"};
        static const char* T1_current_item = T1_items[0];
        if (ImGui::BeginCombo("Texture Projection mode", T1_current_item))
        {
            for (int n = 0; n < 5; n++)
            {
                bool is_selected = (T1_current_item == T1_items[n]);
                if (ImGui::Selectable(T1_items[n], is_selected))
                {
                    typeMapping = n;
                    T1_current_item = T1_items[n];
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        const char* T2_items[] = { "GPU", "CPU" };
        static const char* T2_current_item = T2_items[0];
        if (ImGui::BeginCombo("Texture Projection pipeline", T2_current_item))
        {
            for (int n = 0; n < 2; n++)
            {
                bool is_selected = (T2_current_item == T2_items[n]);
                if (ImGui::Selectable(T2_items[n], is_selected))
                {

                    T2_current_item = T2_items[n];
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        const char* T3_items[] = { "Position", "Normal" };
        static const char* T3_current_item = T3_items[0];
        if (ImGui::BeginCombo("Texture Entity", T3_current_item))
        {
            for (int n = 0; n < 2; n++)
            {
                bool is_selected = (T3_current_item == T3_items[n]);
                if (ImGui::Selectable(T3_items[n], is_selected))
                {
                    T3_current_item = T3_items[n];
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::Button("recalculateUV");
    }
    if (ImGui::CollapsingHeader("Global Constant")) 
    {
        ImGui::SliderFloat3("Attenuation", &global.attenuation.x, 0.f, 3.f);
        ImGui::ColorEdit3("Global Ambient", &global.ambient.x);
        ImGui::ColorEdit3("Fog Color", &global.fogColor.x);
        ImGui::SliderFloat("Fog Min", &global.fogMin, 0.1f, 10.f);
        ImGui::SliderFloat("Fog Max", &global.fogMax, 0.2f, 40.1f);

    }
    if (global.fogMin > global.fogMax)
        global.fogMin = global.fogMax;
}

