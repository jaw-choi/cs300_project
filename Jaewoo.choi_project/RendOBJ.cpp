#include "RendOBJ.h"

RendOBJ::RendOBJ() :view{ 0 }, projection{ 0 }, light{ 0 }, eye{ 0 }{}

RendOBJ::~RendOBJ(){}

void RendOBJ::init()
{
    meshes.push_back(CreateCube(2, 2));
    meshes[0].init("triangle", { 0,-1,-2 }, { 1,1,1 }, { 0,0,0 });
    SetView();
}

void RendOBJ::Update(float deltaTime)
{
}

void RendOBJ::Draw()
{
    glClearColor(1.f, 1.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(10.f);


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
