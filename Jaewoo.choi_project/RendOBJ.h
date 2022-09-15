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


    void SetView();
    //bool loadOBJ(
    //    const char* path,
    //    std::vector < glm::vec3 >& out_vertices,
    //    std::vector < glm::vec3 >& out_indicies,
    //    std::vector < glm::vec2 >& out_uvs,
    //    std::vector < glm::vec3 >& out_normals
    //);
    std::vector<Mesh> meshes;

    const GLfloat bgColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    //const GLfloat one = 1.0f;
    Vec4 useNormal = Vec4(1.f, 0.2f, 0.4f, -1.0f);

private:
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 eye;
    glm::vec3 light;

    std::vector< unsigned int > vertexIndices;
    std::vector< glm::vec3 > temp_vertices;


    // Read our .obj file
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec3 > indicies;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals; // Won't be used at the moment.

    bool res;
    //bool meshSwitch[NUM_MESHES] = { true,true,true,true,true/*,true*/ };
    //bool is_switch_pressed(const char* buttonName, bool& buttonType);
    //void onOffSwitch();
};