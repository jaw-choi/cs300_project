/******************************************************************************/
/*!
\file   mesh.hpp
\par    Purpose: Library for generating polygonal meshes.
\par    Language: C++
\par    Platform: Visual Studio 2019, Windows 10 64-bit
\author Sang Le
\par    Email: sang.le\@digipen.edu, jaewoo.choi@digipen.edu
\par    DigiPen login: sang.le, jaewoo.choi
\date   15/09/2022
*/
/******************************************************************************/
#pragma once
#include <vector>
#include <GL/glew.h> 
#include"math.h"
#include"glslshader.h"
#include "Camera.h"



/*  Mesh function(s) */
enum MeshID { BUNNY, SPHERE, SPHERE4, CUBE2, SPHERE_MODIFIED, NUM_MESHES };
enum Primitive { TRIANGLE, LINE, FACE, NUM_MESH };
struct Vertex
{
    Vertex(glm::vec3 pos, glm::vec3 nrm, glm::vec3 uv) : pos(pos), nrm(nrm), uv(uv) {}

    Vertex() { }

    glm::vec3 pos{ 0 }, nrm{ 0 };
    glm::vec2 uv{ 0 };
    glm::vec3 color{ 0 };
};

const int vertexSize = sizeof(Vertex);
const int indexSize = sizeof(int);


/*  The layouts for specifying the offsets of a vertex
    when it is copied into the graphics pipeline. */
struct VertexLayout
{
    int location;
    int size;
    int type;
    bool normalized;
    int offset;
};

const VertexLayout vLayout[] =
{
    { 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos) },
    { 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, nrm) },
    { 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv) },
    {3, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, color) }

};

struct MinMax
{
    glm::vec3 min = { 0,0,0 };
    glm::vec3 max = { 0,0,0 };
};

struct LengthMinMax
{
    float lenX = 0;
    float lenY = 0;
    float lenZ = 0;
};
const int layoutSize = sizeof(VertexLayout);
const int numAttribs = sizeof(vLayout) / layoutSize;    // for now numAttribs = 1: only pos


typedef std::vector<Vertex> VertexBufferType;
typedef std::vector<int> IndexBufferType;
typedef std::vector<glm::vec3> FaceBufferType;

/*  Mesh format */
struct Mesh
{
    Mesh() : numVertices(0), numTris(0), numIndices(0), position{ 0 }, scale{ 1 }, rotation{ 0 }, VBO{ 0 }, VAO{ 0 }
    { }

    /*  Storing the actual vertex/index data */
    VertexBufferType vertexBuffer;
    IndexBufferType indexBuffer;
    VertexBufferType faceBuffer;
    VertexBufferType vertexBufferForVertexNrm;
    VertexBufferType vertexBufferForFaceNrm;
    

    int meshtype = -1;

    int numVertices=0;
    int numTris=0;
    int numIndices=0;
    int numVerticesLine=0;
    int numVerticesFaceLine=0;
    

    GLuint VAO;
    GLuint VAOL;
    GLuint VAOFL;
    GLuint VBO;
    GLuint VBOL;
    GLuint VBOFL;
    GLuint IBO;
    GLSLShader renderProg{ GLSLShader() };

    GLint modelLoc = 0;
    GLint viewLoc = 0;
    GLint projectionLoc = 0;
    GLint LightLoc = 0;
    GLint colorLoc = 0;
    GLint ViewPosLoc = 0;
    GLint TriOrLine = 0;

    glm::vec3 position{ 0,0,0 };
    glm::vec3 scale = { 1,1,1 };
    glm::vec3 rotation{ 0,0,0 };

    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
    void init(const char* vertex_file_path, const char* fragment_file_path, glm::vec3 Pos = { 0,0,0 }, glm::vec3 Scale = { 1,1,1 }, glm::vec3 Rotate = { 0,0,0 }, bool obj = true);
    void initLine(const char* vertex_file_path, const char* fragment_file_path, glm::vec3 Pos = { 0,0,0 }, glm::vec3 Scale = { 1,1,1 }, glm::vec3 Rotate = { 0,0,0 });
    
    void SendVertexData();
    void SendVertexDataForLine();
    void SendVertexDataForFaceLine();
    void setup_shdrpgm(std::string shader);
    //void setup_mesh();
    //void compute_matrix(float delta_time);
    void draw(glm::vec3 color, glm::mat4 view, glm::mat4 projection, glm::vec3 light_pos, glm::vec3 view_pos, glm::vec2 type_);
    void drawLine(glm::vec3 color, glm::mat4 view, glm::mat4 projection, glm::vec3 light_pos, glm::vec3 view_pos, glm::vec2 type_);
    void drawFaceLine(glm::vec3 color, glm::mat4 view, glm::mat4 projection, glm::vec3 light_pos, glm::vec3 view_pos, glm::vec2 type_);
    void set_position(glm::vec3 pos)
    {
        position = pos;
        update_flag = true;
    }
    void set_rotation(glm::vec3 angle)
    {
        rotation = angle;
        update_flag = true;
    }
    glm::vec3& Get_position() { return position; }
    glm::vec3& Get_scale() { return scale; }
    glm::vec3& Get_Rotation() { return rotation; }

    int* get_stack_slice() { return stack_slice; }
    int stack_slice[2] = { 0 };
    bool update_flag = true;
    Camera camera;
};

Mesh LoadOBJ(const char* path);
void ReadOBJ(const char* path, Mesh& mesh, MinMax& m, LengthMinMax& lm);
Mesh CalculateMesh(Mesh& mesh, MinMax& m, LengthMinMax& lm);
Mesh CreatePlane(int stacks, int slices);
Mesh CreateCube(int stacks, int slices);
Mesh CreateSphere(int stacks, int slices);
Mesh CreateTorus(int stacks, int slices, float startAngle, float endAngle);
Mesh CreateCylinder(int stacks, int slices);
Mesh CreateCone(int stacks, int slices);
Mesh CreateOrbit(int num);

void BuildIndexBuffer(int stacks, int slices, Mesh& mesh);
void addVertex(Mesh& mesh, const Vertex& v);
void addIndex(Mesh& mesh, int index);

void CalculateMinMax(Vertex v, MinMax& m);
void MoveToOrigin(Mesh& mesh,glm::vec3& origin, MinMax& m);
/******************************************************************************/
/*  Pre-defined shapes                                                        */
/******************************************************************************/


