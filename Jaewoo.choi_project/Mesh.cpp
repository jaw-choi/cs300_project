//Name: Jaewoo Choi
//Assignment name: Class project
//Course name: CS300
//Term & Year : 2022&Fall
/******************************************************************************/
/*!
\file   mesh.cpp
\par    Purpose: Library for generating polygonal meshes.
\par    Language: C++
\par    Platform: Visual Studio 2013, Windows 7 64-bit
\author Sang Le,
\par    Email: sang.le\@digipen.edu,
\par    DigiPen login: sang.le,
\date   YOUR_COMPLETION_DATE
*/
/******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.h"
#include "glhelper.h"
/*  Function prototype(s) */

Mesh CreatePlane(int stacks, int slices)
{
    Mesh mesh;
    mesh.stack_slice[0] = stacks;
    mesh.stack_slice[1] = slices;
    for (int stack = 0; stack <= stacks; ++stack)
    {
        float row = (float)stack / stacks;

        for (int slice = 0; slice <= slices; ++slice)
        {
            float col = (float)slice / slices;

            Vertex v;

            v.pos = glm::vec3(col - 0.5f, row - 0.5f, 0.0f);
            v.nrm = glm::vec3(0.0f, 0.0f, 1.0f);
            v.uv = glm::vec2(col, row);

            addVertex(mesh, v);
        }
    }

    BuildIndexBuffer(stacks, slices, mesh);

    return mesh;
}

Mesh CreateCube(int stacks, int slices)
{
    Mesh planeMesh = CreatePlane(stacks, slices);
    Mesh mesh;
    mesh.stack_slice[0] = stacks;
    mesh.stack_slice[1] = slices;
    Vec3 const translateArray[] =
    {
        Vec3(+0.0f, +0.0f, +0.5f), // Z+
        Vec3(+0.0f, +0.0f, -0.5f), // Z-
        Vec3(+0.5f, +0.0f, +0.0f), // X+
        Vec3(-0.5f, +0.0f, +0.0f), // X-
        Vec3(+0.0f, +0.5f, +0.0f), // Y+
        Vec3(+0.0f, -0.5f, +0.0f), // Y-
    };

    Vec2 const rotateArray[] =
    {
        Vec2(+0.0f, +0.0f),             // Z+
        Vec2(+0.0f, (float)+PI),        // Z-
        Vec2(+0.0f, (float)+HALF_PI),   // X+       
        Vec2(+0.0f, (float)-HALF_PI),   // X-
        Vec2((float)-HALF_PI, +0.0f),   // Y+
        Vec2((float)+HALF_PI, +0.0f)    // Y-
    };


    /*  Transform the plane to 6 positions to form the faces of the cube */
    for (int i = 0; i < 6; ++i)
    {
        Mat4 transformMat = Translate(translateArray[i]) * Rotate(rotateArray[i][YINDEX], { 0,1,0 }) * Rotate(rotateArray[i][XINDEX], { 1,0,0 });

        for (int j = 0; j < planeMesh.numVertices; ++j)
        {
            Vertex v;
            v.pos = Vec3(transformMat * Vec4(planeMesh.vertexBuffer[j].pos, 1.0));
            v.nrm = Vec3(transformMat * Vec4(planeMesh.vertexBuffer[j].nrm, 1.0));
            v.uv = planeMesh.vertexBuffer[j].uv;

            v.pos = RoundDecimal(v.pos);
            v.nrm = RoundDecimal(v.nrm);

            addVertex(mesh, v);
        }

        for (int j = 0; j < planeMesh.numIndices; ++j)
            addIndex(mesh, planeMesh.indexBuffer[j] + planeMesh.numVertices * i);
    }

    return mesh;
}

Mesh CreateSphere(int stacks, int slices)
{
    Mesh mesh;
    mesh.stack_slice[0] = stacks;
    mesh.stack_slice[1] = slices;
    for (int stack = 0; stack <= stacks; ++stack)
    {
        float row = (float)stack / stacks;
        float beta = PI * (row - 0.5f);

        for (int slice = 0; slice <= slices; ++slice)
        {
            float col = (float)slice / slices;
            float alpha = col * PI * 2.0f;
            Vertex v;
            v.uv.x = col;
            v.uv.y = row * (-1.0f);

            v.pos.x = 0.5f * sin(alpha) * cos(beta);
            v.pos.y = 0.5f * sin(beta);
            v.pos.z = 0.5f * cos(alpha) * cos(beta);

            v.nrm.x = v.pos.x;
            v.nrm.y = v.pos.y;
            v.nrm.z = v.pos.z;

            v.nrm /= 0.5;

            addVertex(mesh, v);
        }
    }

    BuildIndexBuffer(stacks, slices, mesh);

    return mesh;
}

Mesh CreateCylinder(int stacks, int slices)
{
    Mesh mesh;
    Vertex vertex;
    mesh.stack_slice[0] = stacks;
    mesh.stack_slice[1] = slices;
    /// For the body

    for (int i = 0; i <= stacks; i++)
    {
        float row = static_cast<float>(i) / stacks;

        for (int j = 0; j <= slices; j++)
        {
            float col = static_cast<float>(j) / slices;
            float alpha = col * 2.0f * PI;
            float sinAlpha = sin(alpha);
            float cosAlpha = cos(alpha);

            vertex.uv.x = row;
            vertex.uv.y = col;

            vertex.pos.x = 0.5f * sinAlpha;
            vertex.pos.y = row - 0.5f;
            vertex.pos.z = 0.5f * cosAlpha;

            vertex.nrm.x = vertex.pos.x / 0.5f;
            vertex.nrm.y = 0;
            vertex.nrm.z = vertex.pos.z / 0.5f;

            addVertex(mesh, vertex);
        }
    }
    BuildIndexBuffer(stacks, slices, mesh);

    int vertex_size = static_cast<int>(mesh.vertexBuffer.size());

    /// For the caps

    for (int i = 0; i <= stacks; i++)
    {
        if (i == 0)
        {
            vertex.pos = Vec3(0.0, 0.5f, 0.0);
            vertex.nrm.x = vertex.pos.x / 0.5f;
            vertex.nrm.y = vertex.pos.y / 0.5f;
            vertex.nrm.z = vertex.pos.z / 0.5f;
        }
        else if (i == 1)
        {
            vertex.pos = Vec3(0.0, -0.5f, 0.0);
            vertex.nrm.x = vertex.pos.x / 0.5f;
            vertex.nrm.y = vertex.pos.y / 0.5f;
            vertex.nrm.z = vertex.pos.z / 0.5f;
        }

        addVertex(mesh, vertex);

        float row = static_cast<float>(i) / stacks;

        for (int j = 0; j <= slices; j++)
        {
            float col = static_cast<float>(j) / slices;
            float alpha = col * 2.0f * PI;
            float sinAlpha = sin(alpha);
            float cosAlpha = cos(alpha);

            vertex.uv.x = row;
            vertex.uv.y = col;

            if (i == 0)
            {
                vertex.pos = Vec3(0.5 * sinAlpha, 0.5f, 0.5f * cosAlpha);

                vertex.nrm.x = vertex.pos.x / 0.5f;
                vertex.nrm.y = vertex.pos.y / 0.5f;
                vertex.nrm.z = vertex.pos.z / 0.5f;
            }
            else if (i == 1)
            {
                vertex.pos = Vec3(0.5f * sinAlpha, -0.5f, 0.5f * cosAlpha);

                vertex.nrm.x = vertex.pos.x / 0.5f;
                vertex.nrm.y = vertex.pos.y / 0.5f;
                vertex.nrm.z = vertex.pos.z / 0.5f;
            }

            addVertex(mesh, vertex);
        }
    }

    for (int i = 0; i <= stacks; i++)
    {
        vertex_size += (i * (slices + 2));

        for (int j = 1; j < slices; j++)
        {
            addIndex(mesh, vertex_size);
            addIndex(mesh, vertex_size + j);
            addIndex(mesh, vertex_size + j + 1);
        }
        addIndex(mesh, vertex_size);
        addIndex(mesh, vertex_size + slices);
        addIndex(mesh, vertex_size + 1);
    }

    return mesh;
}

Mesh CreateTorus(int stacks, int slices, float startAngle, float endAngle)
{
    Mesh mesh;
    mesh.stack_slice[0] = stacks;
    mesh.stack_slice[1] = slices;
    for (int stack = 0; stack <= stacks; ++stack)
    {
        float row = (float)stack / stacks; // [0.0, 1.0]

        float alpha = PI + startAngle + (row * (endAngle - startAngle)); // [0.0, 2¥ð]

        float sinAlpha = sin(alpha);
        float  cosAlpha = cos(alpha);

        for (int slice = 0; slice <= slices; ++slice)
        {
            float col = (float)slice / slices;

            float beta = col * PI * 2.0f;

            Vertex center;
            center.pos = Vec3(0, 0, 0);

            Vertex v;
            v.uv.x = col;
            v.uv.y = row;

            v.pos.x = -(0.35f + (0.15f * cos(beta))) * sinAlpha;
            v.pos.y = -0.15f * sin(beta);
            v.pos.z = -(0.35f + (0.15f * cos(beta))) * cosAlpha;

            v.nrm = v.pos - center.pos;

            v.nrm /= 0.15f;
            addVertex(mesh, v);
        }

    }

    BuildIndexBuffer(stacks, slices, mesh);
    return mesh;
}

Mesh CreateCone(int stacks, int slices)
{
    Mesh mesh;
    Vertex v;
    Mesh top;
    //Mesh bottom;
    mesh.stack_slice[0] = stacks;
    mesh.stack_slice[1] = slices;
    float col = 0;
    float alpha = 0;
    for (int stack = 0; stack <= stacks; ++stack)
    {
        float row = ((float)stack / stacks) - 0.5f; // [0.0, 1.0]

        for (int slice = 0; slice <= slices; ++slice)
        {
            col = (float)slice / slices;
            alpha = col * PI * 2.0f;

            // side
            v.uv.x = row;
            v.uv.y = col;

            v.pos.x = 0.5f * (0.5f - row) * sin(alpha);
            v.pos.y = row;
            v.pos.z = 0.5f * (0.5f - row) * cos(alpha);


            v.nrm.x = v.pos.x / 0.5f;
            v.nrm.y = 0.0;
            v.nrm.z = v.pos.z / 0.5f;

            addVertex(mesh, v);
        }
    }
    BuildIndexBuffer(stacks, slices, mesh);

    //int vertex_size = static_cast<int>(mesh.vertexBuffer.size());

    /////// For the caps

    //for (int i = 0; i < 1; i++)
    //{
    //    if (i == 0)
    //    {
    //        v.pos = Vec3(0.0, -0.5f, 0.0);
    //        v.nrm.x = v.pos.x / 0.5f;
    //        v.nrm.y = v.pos.y / 0.5f;
    //        v.nrm.z = v.pos.z / 0.5f;
    //    }

    //    addVertex(mesh, v);

    //    float row = static_cast<float>(i) / stacks;

    //    for (int j = 0; j <= slices; j++)
    //    {
    //        float col_ = static_cast<float>(j) / slices;
    //        float alpha_ = col_ * 2.0f * PI;
    //        float sinAlpha = sin(alpha_);
    //        float cosAlpha = cos(alpha_);

    //        v.uv.x = row;
    //        v.uv.y = col_;

    //        v.pos = Vec3(0.5 * sinAlpha, -0.5f, 0.5f * cosAlpha);

    //        v.nrm.x = v.pos.x / 0.5f;
    //        v.nrm.y = v.pos.y / 0.5f;
    //        v.nrm.z = v.pos.z / 0.5f;


    //        addVertex(mesh, v);
    //    }
    //}

    //for (int i = 0; i <= stacks; i++)
    //{
    //    vertex_size += (i * (slices + 2));

    //    for (int j = 1; j < slices; j++)
    //    {
    //        addIndex(mesh, vertex_size);
    //        addIndex(mesh, vertex_size + j + 1);
    //        addIndex(mesh, vertex_size + j);
    //    }
    //    addIndex(mesh, vertex_size);
    //    addIndex(mesh, vertex_size + 1);
    //    addIndex(mesh, vertex_size + slices);
    //}


    return  mesh;
}




void BuildIndexBuffer(int stacks, int slices, Mesh& mesh)
{
    //@todo: IMPLEMENT ME
    int p0 = 0, p1 = 0, p2 = 0;
    int p3 = 0, p4 = 0, p5 = 0;

    int stride = slices + 1;
    for (int i = 0; i < stacks; ++i)
    {
        for (int j = 0; j < slices; ++j)
        {
            int current_row = i * stride;
            /*  You need to compute the indices for the first triangle here */
            /*  ... */
            p0 = current_row + j;
            p1 = p0 + 1;
            p2 = p1 + stride;
            // triangle <p3, p4, p5>
            /*  Ignore degenerate triangle */
            if (!DegenerateTri(mesh.vertexBuffer[p0].pos,
                mesh.vertexBuffer[p1].pos,
                mesh.vertexBuffer[p2].pos))
            {
                /*  Add the indices for the first triangle */
                addIndex(mesh, p0);
                addIndex(mesh, p1);
                addIndex(mesh, p2);
            }


            /*  You need to compute the indices for the second triangle here */
            /*  ... */
            p3 = p2;
            p4 = p3 - 1;
            p5 = p0;
            /*  Ignore degenerate triangle */
            if (!DegenerateTri(mesh.vertexBuffer[p3].pos,
                mesh.vertexBuffer[p4].pos,
                mesh.vertexBuffer[p5].pos))
            {
                /*  Add the indices for the second triangle */
                addIndex(mesh, p3);
                addIndex(mesh, p4);
                addIndex(mesh, p5);
            }
        }
    }
}

void addVertex(Mesh& mesh, const Vertex& v)
{
    mesh.vertexBuffer.push_back(v);
    ++mesh.numVertices;
}

void addIndex(Mesh& mesh, int index)
{
    mesh.indexBuffer.push_back(index);
    ++mesh.numIndices;

    if (mesh.numIndices % 3 == 0)
        ++mesh.numTris;
}


void Mesh::setup_shdrpgm(std::string shader)
{
    std::string vert = "../shaders/";
    std::string frag = "../shaders/";
    vert = vert + shader + ".vert";
    frag = frag + shader + ".frag";

    std::vector<std::pair<GLenum, std::string>> shdr_files;
    shdr_files.push_back(std::make_pair(GL_VERTEX_SHADER, vert));
    shdr_files.push_back(std::make_pair(GL_FRAGMENT_SHADER, frag));
    renderProg.CompileLinkValidate(shdr_files);
    if (GL_FALSE == renderProg.IsLinked())
    {
        std::cout << "Unable to compile/link/validate shader programs" << "\n";
        std::cout << renderProg.GetLog() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}



GLuint Mesh::LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::string Line;
        while (getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }
    else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::string Line;
        while (getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }


    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }


    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    std::vector<std::pair<GLenum, std::string>> shdr_files;
    shdr_files.push_back(std::make_pair(GL_VERTEX_SHADER, vertex_file_path));
    shdr_files.push_back(std::make_pair(GL_FRAGMENT_SHADER, fragment_file_path));
    renderProg.CompileLinkValidate(shdr_files);
    if (GL_FALSE == renderProg.IsLinked())
    {
        std::cout << "Unable to compile/link/validate shader programs" << "\n";
        std::cout << renderProg.GetLog() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void Mesh::setup_mesh()
{
    glUseProgram(renderProg.GetHandle());

    /*  Obtain the locations of the variables in the shaders with the given names */
    modelLoc = glGetUniformLocation(renderProg.GetHandle(), "model");
    viewLoc = glGetUniformLocation(renderProg.GetHandle(), "view");
    colorLoc = glGetUniformLocation(renderProg.GetHandle(), "color");
    projectionLoc = glGetUniformLocation(renderProg.GetHandle(), "projection");
    LightLoc = glGetUniformLocation(renderProg.GetHandle(), "lightPos");
    ViewPosLoc = glGetUniformLocation(renderProg.GetHandle(), "viewPos");


        SendVertexData();

        //SendVertexDataForLine();

    /*  Bind framebuffer to 0 to render to the screen (by default already 0) */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /*  Initially drawing using filled mode */

    /*  Hidden surface removal */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // glEnable(GL_CULL_FACE);     /*  For efficiency, not drawing back-face */
}

void Mesh::compute_matrix([[maybe_unused]] float delta_time)
{

}

void Mesh::draw(glm::vec3 color, glm::mat4 view, glm::mat4 projection, glm::vec3 light_pos, glm::vec3 view_pos)
{
    glm::mat4 model = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
    //TODO
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 0.5f, 0.0f));
    model = glm::scale(model, scale);



    glUniform4fv(colorLoc, 1, ValuePtr(color));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3fv(LightLoc, 1, ValuePtr(light_pos));
    glUniform3fv(ViewPosLoc, 1, ValuePtr(view_pos));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

}

//void Mesh::drawLine(glm::vec3 color, glm::mat4 view, glm::mat4 projection, glm::vec3 light_pos, glm::vec3 view_pos)
//{
//    glm::mat4 model = {
//        1,0,0,0,
//        0,1,0,0,
//        0,0,1,0,
//        0,0,0,1
//    };
//    model = glm::translate(model, position);
//    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
//    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
//    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
//    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.5f, 0.0f));
//    model = glm::scale(model,  scale );
//
//
//
//    glUniform4fv(colorLoc, 1, ValuePtr(color));
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//    glUniform3fv(LightLoc, 1, ValuePtr(light_pos));
//    glUniform3fv(ViewPosLoc, 1, ValuePtr(view_pos));
//
//    glBindVertexArray(VAO); 
//    glDrawElements(GL_LINES, numIndicesLine, GL_UNSIGNED_INT, nullptr);
//
//}

void Mesh::init(const char* vertex_file_path, const char* fragment_file_path, glm::vec3 Pos, glm::vec3 Scale, glm::vec3 Rotate)
{
    position = Pos;
    scale = Scale;
    rotation = Rotate;

    LoadShaders(vertex_file_path, fragment_file_path);
    
    setup_mesh();
}

void Mesh::SendVertexData()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*  Copy vertex attributes to GPU */
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(numVertices) * static_cast < GLsizeiptr>(vertexSize), &vertexBuffer[0], GL_DYNAMIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    /*  Copy vertex indices to GPU */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(numIndices) * static_cast < GLsizeiptr>(indexSize), &indexBuffer[0], GL_DYNAMIC_DRAW);


    /*  Send vertex attributes to shaders */
    for (int i = 0; i < numAttribs; ++i)
    {
        glEnableVertexAttribArray(vLayout[i].location);
        glVertexAttribPointer(vLayout[i].location, vLayout[i].size, vLayout[i].type, vLayout[i].normalized, vertexSize, (void*)(uintptr_t)vLayout[i].offset);
    }
}

//void Mesh::SendVertexDataForLine()
//{
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    /*  Copy vertex attributes to GPU */
//    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(numVerticesLine) * static_cast <GLsizeiptr>(vertexSize), &vertexBufferForLines[0], GL_DYNAMIC_DRAW);
//
//    glGenBuffers(1, &IBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//    /*  Copy vertex indices to GPU */
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(numIndicesLine) * static_cast <GLsizeiptr>(indexSize), &indexBufferForLines[0], GL_DYNAMIC_DRAW);
//
//
//    /*  Send vertex attributes to shaders */
//    for (int i = 0; i < numAttribs; ++i)
//    {
//        glEnableVertexAttribArray(vLayout[i].location);
//        glVertexAttribPointer(vLayout[i].location, vLayout[i].size, vLayout[i].type, vLayout[i].normalized, vertexSize, (void*)(uintptr_t)vLayout[i].offset);
//    }
//}


Mesh LoadOBJ(const char* path)
{
    Mesh mesh;
    MinMax m;
    LengthMinMax lm;


    ReadOBJ(path, mesh, m, lm);

    return CalculateMesh(mesh, m, lm);
}

void ReadOBJ(const char* path,Mesh& mesh, MinMax& m, LengthMinMax& lm)
{
    Vertex v;

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("There is no suitable file!\n");
    }

    while (true) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {

            fscanf(file, "%f %f %f\n", &v.pos.x, &v.pos.y, &v.pos.z);
            addVertex(mesh, v);
            CalculateMinMax(v, m);


        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3];
            int matches = fscanf(file, "%d %d %d \n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
            if (matches != 3) {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                //return false;
            }
            addIndex(mesh, vertexIndex[0]-1);
            addIndex(mesh, vertexIndex[1]-1);
            addIndex(mesh, vertexIndex[2]-1);

            // For each vertex of each triangle
        }
    }
    lm.lenX = m.max.x - m.min.x;
    lm.lenY = m.max.y - m.min.y;
    lm.lenZ = m.max.z - m.min.z;
}

Mesh CalculateMesh(Mesh& mesh, MinMax& m, LengthMinMax& lm)
{
    GLushort ia, ib, ic;
    size_t sizeOfIndicies = mesh.numIndices;
    std::vector<int> nb_seen;
    nb_seen.resize(mesh.numVertices, 0);
    std::vector<std::vector<glm::vec3>> prevNormal;
    int doubleNumVertices = mesh.numVertices * 2;
    int NumVertice = mesh.numVertices;
    mesh.faceBuffer.resize(mesh.numTris, { 0,0,0 });
    prevNormal.resize(mesh.numVertices, std::vector<glm::vec3>(0));

    mesh.vertexBufferForLines.resize(mesh.numVertices * 2, { 0,0,0 });
    mesh.indexBufferForLines.resize(mesh.numVertices * 2, 0);
    
    //Move to origin
    glm::vec3 origin = { 0,0,0 };
    MoveToOrigin(mesh, origin, m);

    for (int i = 0; i < mesh.numVertices; i++)
    {

        mesh.vertexBuffer[i].pos.x = 2 * ((mesh.vertexBuffer[i].pos.x- m.min.x) / lm.lenX) -1.f;
        mesh.vertexBuffer[i].pos.y = 2 * ((mesh.vertexBuffer[i].pos.y- m.min.y) / lm.lenY) -1.f;
        mesh.vertexBuffer[i].pos.z = 2 * ((mesh.vertexBuffer[i].pos.z- m.min.z) / lm.lenZ) -1.f;
    }

    for (unsigned int i = 0; i < sizeOfIndicies; i += 3) {

        ia = mesh.indexBuffer[i];
        ib = mesh.indexBuffer[i + 1];
        ic = mesh.indexBuffer[i + 2];

        glm::vec3 normal = Normalize(glm::cross(
            mesh.vertexBuffer[ib].pos - mesh.vertexBuffer[ia].pos,
            mesh.vertexBuffer[ic].pos - mesh.vertexBuffer[ia].pos));

        mesh.faceBuffer[i / 3] = normal;

        int v[3];
        v[0] = ia;
        v[1] = ib;
        v[2] = ic;
        //Averaging normals
        for (int j = 0; j < 3; j++) {
            bool IgnoreParrel = false;
            GLushort cur_v = v[j];
            nb_seen[cur_v]++;
            if (nb_seen[cur_v] == 1)
            {
                mesh.vertexBuffer[cur_v].nrm = normal;
                prevNormal[cur_v].push_back(normal);
            }
            else
            {
                for (int i = 0; i < prevNormal[cur_v].size(); i++)
                {
                    if (prevNormal[cur_v][i] == normal)
                        IgnoreParrel = true;
                }
                // average
                if (IgnoreParrel != true)
                {
                    mesh.vertexBuffer[cur_v].nrm.x = mesh.vertexBuffer[cur_v].nrm.x * (1.0 - 1.0 / nb_seen[cur_v]) + normal.x * 1.0 / nb_seen[cur_v];
                    mesh.vertexBuffer[cur_v].nrm.y = mesh.vertexBuffer[cur_v].nrm.y * (1.0 - 1.0 / nb_seen[cur_v]) + normal.y * 1.0 / nb_seen[cur_v];
                    mesh.vertexBuffer[cur_v].nrm.z = mesh.vertexBuffer[cur_v].nrm.z * (1.0 - 1.0 / nb_seen[cur_v]) + normal.z * 1.0 / nb_seen[cur_v];
                    mesh.vertexBuffer[cur_v].nrm = glm::normalize(mesh.vertexBuffer[cur_v].nrm);
                }
            }
        }
    }


    int j = 0;
    for (int i = 0; i < doubleNumVertices; i+=2)
    {
        mesh.vertexBufferForLines[i] = mesh.vertexBuffer[j].pos;
        mesh.vertexBufferForLines[i+1] = mesh.vertexBuffer[j].pos + mesh.vertexBuffer[j].nrm;

        mesh.indexBufferForLines[i] = i;
        mesh.indexBufferForLines[i + 1] = i + 1;

        j++;
    }

    return mesh;
}


void CalculateMinMax(Vertex v, MinMax& m)
{
    if (v.pos.x < m.min.x)
        m.min.x = v.pos.x;
    if (v.pos.y < m.min.y)
        m.min.y = v.pos.y;
    if (v.pos.z < m.min.z)
        m.min.z = v.pos.z;
    if (v.pos.x > m.max.x)
        m.max.x = v.pos.x;
    if (v.pos.y > m.max.y)
        m.max.y = v.pos.y;
    if (v.pos.z > m.max.z)
        m.max.z = v.pos.z;

}

void MoveToOrigin(Mesh& mesh, glm::vec3& origin, MinMax& m)
{
    for (int i = 0; i < mesh.numVertices; i++)
    {
        origin.x += mesh.vertexBuffer[i].pos.x;
        origin.y += mesh.vertexBuffer[i].pos.y;
        origin.z += mesh.vertexBuffer[i].pos.z;
    }
    origin = origin / static_cast<float>(mesh.numVertices);

    for (int i = 0; i < mesh.numVertices; i++)
    {
        mesh.vertexBuffer[i].pos.x -= origin.x;
        mesh.vertexBuffer[i].pos.y -= origin.y;
        mesh.vertexBuffer[i].pos.z -= origin.z;
    }

    m.min -= origin;
    m.max -= origin;
}
