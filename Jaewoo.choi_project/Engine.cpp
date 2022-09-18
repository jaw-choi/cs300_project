/* !
@file    Engine.cpp
@author  jaewoo.choi@digipen.edu
@date    15/09/2022

Note: 

*//*__________________________________________________________________________*/
#include "Engine.h"
#include "glhelper.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "RendOBJ.h"
Engine::Engine()
{
    obj = new RendOBJ();
    if (!GLHelper::init(1600, 1000, "Jaewoo.choi_Project"))
    {
	std::cout << "Unable to create OpenGL context" << std::endl;
	std::exit(EXIT_FAILURE);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(GLHelper::ptr_window, true);
    const char* glsl_version = "#version 450";
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();
    
}

Engine::~Engine()
{
    GLHelper::cleanup();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void Engine::init()
{
    obj->init();
}

void Engine::Update()
{
    glfwPollEvents();
    //double delta_time = GLHelper::update_time(1.0);
    //tests[current]->Update(static_cast<float>(delta_time));
}

void Engine::Draw()
{

    //tests[current]->Draw();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //TODO : make helper function with whole imgui
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();

    obj->Draw();

    //ImGui::Begin("Demo");
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(GLHelper::ptr_window);
}

bool Engine::ShouldClose()
{
    return glfwWindowShouldClose(GLHelper::ptr_window);
}
