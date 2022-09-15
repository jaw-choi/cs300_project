#include "RendOBJ.h"

RendOBJ::RendOBJ() :view{ 0 }, projection{ 0 }, light{ 0 }, eye{ 0 }{}

RendOBJ::~RendOBJ(){}

void RendOBJ::init()
{
    //res = loadOBJ("../object/4Sphere.obj", vertices, indicies, uvs, normals);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    meshes.push_back(loadOBJ("../object/4Sphere.obj"));
    meshes[0].init("../shaders/triangle.vert", "../shaders/triangle.frag", { 0,-1,-2 }, { 1,1,1 }, { 0,0,0 });
    SetView();
}

void RendOBJ::Update(float )
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

//bool RendOBJ::loadOBJ(const char* path, std::vector<glm::vec3>& out_vertices, std::vector < glm::vec3 >& out_indicies, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
//{
//
//    FILE* file = fopen(path, "r");
//    if (file == NULL) {
//        printf("There is no suitable file!\n");
//        return false;
//    }
//
//    while (true) {
//
//        char lineHeader[128];
//        // read the first word of the line
//        int res = fscanf(file, "%s", lineHeader);
//        if (res == EOF)
//            break; // EOF = End Of File. Quit the loop.
//
//        // else : parse lineHeader
//
//        if (strcmp(lineHeader, "v") == 0) {
//            glm::vec3 vertex;
//            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
//            out_vertices.push_back(vertex);
//        }
//        else if (strcmp(lineHeader, "f") == 0) {
//            std::string vertex1, vertex2, vertex3;
//            unsigned int vertexIndex[3];
//            int matches = fscanf(file, "%d %d %d \n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
//            if (matches != 3) {
//                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//                return false;
//            }
//            vertexIndices.push_back(vertexIndex[0]);
//            vertexIndices.push_back(vertexIndex[1]);
//            vertexIndices.push_back(vertexIndex[2]);
//
//            // For each vertex of each triangle
//        }
//    }
//
//    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
//
//        unsigned int vertexIndex = vertexIndices[i];
//        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
//        out_indicies.push_back(vertex);
//    }
//    //glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(glm::vec3), &out_vertices[0], GL_STATIC_DRAW);
//    return true;
//}