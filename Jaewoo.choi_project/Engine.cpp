#include "Engine.h"
#include "glhelper.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
Engine::Engine()
{
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
    //ImGui::Begin("Demo");
    //demo_switch();
    //ImGui::Render();
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(GLHelper::ptr_window);
}

bool Engine::ShouldClose()
{
    return glfwWindowShouldClose(GLHelper::ptr_window);
}
