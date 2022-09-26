//Name: Jaewoo Choi
//Assignment name: Assignment_1
//Course name: CS300
//Term & Year : 2022&Fall
/*!
@file    RendOBJ.cpp
@author  Jaewoo.choi
@date    15/09/2022

Note :

*//*__________________________________________________________________________*/
#include "RendOBJ.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

RendOBJ::RendOBJ() :view{ 0 }, projection{ 0 }, light{ 0 }, eye{ 0 }{}

RendOBJ::~RendOBJ(){}

void RendOBJ::init()
{
    meshes.push_back(LoadOBJ("../object/bunny_high_poly.obj"));
    meshes.push_back(LoadOBJ("../object/bunny_high_poly.obj"));
    meshes.push_back(LoadOBJ("../object/bunny_high_poly.obj"));

    meshes.push_back(CreateSphere(60,60));
    meshes.push_back(CreateSphere(60,60));
    meshes.push_back(CreateSphere(60,60));
    meshes.push_back(CreateSphere(60,60));
    meshes.push_back(CreateSphere(60,60));
    meshes.push_back(CreateSphere(60,60));
    meshes.push_back(CreateSphere(60,60));
    meshes.push_back(CreateSphere(60,60));
     
    meshes.push_back(CreateOrbit(100));

    
    meshes[0].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 0,0,0 }, { 1,1,1 }, { 0,0,0 });
    meshes[1].initLine("../shaders/line.vert", "../shaders/line.frag", { 0,0,0 }, { 1,1,1 }, { 0,0,0 });
    meshes[2].initFace("../shaders/line.vert", "../shaders/line.frag", { 0,0,0 }, { 1,1,1 }, { 0,0,0 });

    meshes[3].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 2,0,0 }, { 0.2f,0.2f,0.2f }, { 0,0,0 });
    meshes[4].init("../shaders/triangle.vert", "../shaders/triangle.frag", { -2,0,0 }, { 0.2f,0.2f,0.2f }, { 0,0,0 });
    meshes[5].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 0,0,2 }, { 0.2f,0.2f,0.2f }, { 0,0,0 });
    meshes[6].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 0,0,-2 }, { 0.2f,0.2f,0.2f }, { 0,0,0 });
    meshes[7].init("../shaders/triangle.vert", "../shaders/triangle.frag", { sqrt(2),0,-sqrt(2) }, { 0.2f,0.2f,0.2f }, { 0,0,0 });
    meshes[8].init("../shaders/triangle.vert", "../shaders/triangle.frag", { -sqrt(2),0,-sqrt(2) }, { 0.2f,0.2f,0.2f }, { 0,0,0 });
    meshes[9].init("../shaders/triangle.vert", "../shaders/triangle.frag", { sqrt(2),0,sqrt(2) }, { 0.2f,0.2f,0.2f }, { 0,0,0 });
    meshes[10].init("../shaders/triangle.vert", "../shaders/triangle.frag", { -sqrt(2),0,sqrt(2) }, { 0.2f,0.2f,0.2f }, { 0,0,0 });

    meshes[11].initLine("../shaders/line.vert", "../shaders/line.frag", { 0,0,0 }, { 1,1,1 }, { 0,0,0 });

    


    camera = { {0.f, 0.f, 10.0f} };
    SetView();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
}

void RendOBJ::Update(float deltaTime)
{
    camera.Update(deltaTime);

    for (int i = 3; i <= 10; i++)
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
    
    meshes[0].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());
    
    //meshes[1].drawLine(useNormal, view, projection, light, eye);
    
    //meshes[2].drawFaceLine(useNormal, view, projection, light, eye);

    meshes[3].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());
    meshes[4].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());
    meshes[5].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());
    meshes[6].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());
    meshes[7].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());
    meshes[8].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());
    meshes[9].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());
    meshes[10].draw(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());

    meshes[11].drawLine(useNormal, camera.GetViewMatrix(), projection, light, camera.GetEye());


}

void RendOBJ::OnImGuiRender()
{
}

void RendOBJ::UnLoad()
{
    meshes.clear();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //useNormal.r = 1;
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
    eye = { 0.f, 0.f, 10.0f };
    light = { 0.0f, 0.0f, 3.0f };

    //view = glm::rotate(view, PI, glm::vec3(0.0f, 1.0f, 0.0f));
    //view = glm::rotate(view, SIXTEENTH_PI, glm::vec3(0.0f, 1.0f, 0.0f));

    view = glm::translate(view, camera.eye);
    projection = glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f);

}
