/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: RendOBJ.cpp
Purpose: <This file contains the definitions of class RendOBJ that encapsulates the
functionality required to init and draw models>
Language: <c++>
Platform: <Visual studio 2019, OpenGL 4.5, Window 64 bit>
Project: <jaewoo.choi_CS300_1>
Author: <Jaewoo Choi, jaewoo.choi, 55532>
Creation date: 14/09/2022
End Header --------------------------------------------------------*/
#include "RendOBJ.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "Camera.h"

RendOBJ::RendOBJ() :view{ 0 }, projection{ 0 }, light{ 0 }, eye{ 0 }{}

RendOBJ::~RendOBJ(){}

void RendOBJ::init()
{
    InitBunny();
    InitSphere();
    InitOrbit();
    Init4Sphere();
    Initcube2();
    InitSphere_();
    InitSphereModified();

    camera = { {0.f, 0.f, 8.0f} };
    
    SetView();

}

void RendOBJ::Update(float deltaTime)
{
    camera.Update(deltaTime);

    for (int i = 1; i <= 8; i++)
    {
        meshes[i].position = glm::vec3(2*cos((i * QUARTER_PI)+deltaTime),0,2*sin(i * QUARTER_PI +deltaTime));
    }
}

void RendOBJ::Draw()
{
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Demo");
    OnImGuiRender();
    DrawBeforeImGui();

}

void RendOBJ::OnImGuiRender()
{

    const char* items[] = { "bunny_high_poly", "4Sphere", "cube2", "sphere", "sphere_modified"};
    static const char* current_item = items[0];

    if (ImGui::BeginCombo("Model", current_item)) // The second parameter is the label previewed before opening the combo.
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
    if (current_item == items[0]&&ImGui::Button("Vertex Normal"))
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


    ImGui::SliderFloat("x_pos_light", &light.x,-5.f,5.f,"%.2f", 0);
    light.x = light.x;


    ImGui::SliderFloat("y_pos_light", &light.y,-5.f,5.f,"%.2f", 0);
    light.y = light.y;
    

    ImGui::SliderFloat("z_pos_light", &light.z,-5.f,5.f,"%.2f", 0);
    light.z = light.z;

    ImGui::Button("Camera can move with 'w','a','s','d','up','down'");
    ImGui::Button("Camera can move with 'up','down'");
}

void RendOBJ::UnLoad()
{
    meshes.clear();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //useNormal.r = 1;
}

void RendOBJ::InitBunny()
{
    meshes.push_back(LoadOBJ("../object/bunny_high_poly.obj"));
    meshes[0].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}

void RendOBJ::InitSphere()
{
    meshes.push_back(CreateSphere(60, 60));
    meshes.push_back(CreateSphere(60, 60));
    meshes.push_back(CreateSphere(60, 60));
    meshes.push_back(CreateSphere(60, 60));
    meshes.push_back(CreateSphere(60, 60));
    meshes.push_back(CreateSphere(60, 60));
    meshes.push_back(CreateSphere(60, 60));
    meshes.push_back(CreateSphere(60, 60));

    meshes[1].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 2,0,0 }, { 0.2f,0.2f,0.2f }, { 0,0,0 },false);
    meshes[2].init("../shaders/triangle.vert", "../shaders/triangle.frag", { -2,0,0 }, { 0.2f,0.2f,0.2f }, { 0,0,0 }, false);
    meshes[3].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 0,0,2 }, { 0.2f,0.2f,0.2f }, { 0,0,0 }, false);
    meshes[4].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 0,0,-2 }, { 0.2f,0.2f,0.2f }, { 0,0,0 }, false);
    meshes[5].init("../shaders/triangle.vert", "../shaders/triangle.frag", { sqrt(2),0,-sqrt(2) }, { 0.2f,0.2f,0.2f }, { 0,0,0 }, false);
    meshes[6].init("../shaders/triangle.vert", "../shaders/triangle.frag", { -sqrt(2),0,-sqrt(2) }, { 0.2f,0.2f,0.2f }, { 0,0,0 }, false);
    meshes[7].init("../shaders/triangle.vert", "../shaders/triangle.frag", { sqrt(2),0,sqrt(2) }, { 0.2f,0.2f,0.2f }, { 0,0,0 }, false);
    meshes[8].init("../shaders/triangle.vert", "../shaders/triangle.frag", { -sqrt(2),0,sqrt(2) }, { 0.2f,0.2f,0.2f }, { 0,0,0 }, false);

}

void RendOBJ::InitOrbit()
{
    meshes.push_back(CreateOrbit(100));
    meshes[9].initLine("../shaders/line.vert", "../shaders/line.frag", { 0,0,0 }, { 1.f,1.f,1.f }, { 0,0,0 });
}

void RendOBJ::Init4Sphere()
{
    meshes.push_back(LoadOBJ("../object/4Sphere.obj"));
    meshes[10].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}

void RendOBJ::Initcube2()
{
    meshes.push_back(LoadOBJ("../object/cube2.obj"));
    meshes[11].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}

void RendOBJ::InitSphere_()
{
    meshes.push_back(LoadOBJ("../object/sphere.obj"));
    meshes[12].init("../shaders/triangle.vert", "../shaders/triangle.frag");
}

void RendOBJ::InitSphereModified()
{
    meshes.push_back(LoadOBJ("../object/sphere_modified.obj"));
    meshes[13].init("../shaders/triangle.vert", "../shaders/triangle.frag");
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
    light = { 0.0f, 0.0f, 3.0f };

    //view = glm::rotate(view, PI, glm::vec3(0.0f, 1.0f, 0.0f));

    //view = glm::rotate(view, PI, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, camera.eye);
    projection = glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f);

}

void RendOBJ::DrawBeforeImGui()
{
    if (meshSwitch[0])
        meshes[0].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    else if (meshSwitch[1])
        meshes[10].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    else if (meshSwitch[2])
        meshes[11].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    else if (meshSwitch[3])
        meshes[12].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    else if (meshSwitch[4])
        meshes[13].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });

    if (vertxNrm[0])
        meshes[0].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[0])
        meshes[0].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    if (vertxNrm[1])
        meshes[10].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[1])
        meshes[10].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    if (vertxNrm[2])
        meshes[11].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[2])
        meshes[11].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    if (vertxNrm[3])
        meshes[12].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[3])
        meshes[12].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    if (vertxNrm[4])
        meshes[13].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
    if (faceNrm[4])
        meshes[13].drawFaceLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });

    meshes[1].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    meshes[2].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    meshes[3].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    meshes[4].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    meshes[5].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    meshes[6].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    meshes[7].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });
    meshes[8].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 0,0 });

    meshes[9].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye(), { 1,0 });
}
