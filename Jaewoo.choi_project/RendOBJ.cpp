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

    meshes.push_back(loadOBJ("../object/bunny_high_poly.obj"));
    meshes[0].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 0,-1,-2 }, { 1,1,1 }, { 0,0,0 });
    SetView();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RendOBJ::Update(float )
{
}

void RendOBJ::Draw()
{
    glClearColor(1.f, 1.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(10.f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Demo");

    meshes[0].draw(useNormal, view, projection, light, -eye);

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
    eye = { 0.0f, 0.0f, -3.0f };
    light = { 0.0f, 0.0f, 3.0f };

    view = glm::translate(view, eye);
    projection = glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f);

}
