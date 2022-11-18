#version 450 core

/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: PhongShading.vert
Purpose: <This file contains layout,uniform value,and set gl position with normal vector>
Language: <c++>
Platform: <Visual studio 2019, OpenGL 4.5, Window 64 bit>
Project: <jaewoo.choi_CS300_2>
Author: <Jaewoo Choi, jaewoo.choi, 55532>
Creation date: 04/11/2022
End Header --------------------------------------------------------*/

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 nrm;
layout (location = 2) in vec2 uv;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    mat4 model;
};
uniform int typeMapping;

void main()
{
    gl_Position = projection * view *  model * vec4(pos, 1.0f);
    FragPos = vec3(model * vec4(pos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * nrm;
    if(typeMapping==0){
        TexCoords=uv;
    }
    else if(typeMapping==1){
        TexCoords = vec2((pos.x + 1.f)/2.f,(pos.z + 1.f)/2.f);
    }
    else if(typeMapping==2){
        float r = sqrt((pos.x*pos.x) +(pos.z*pos.z));
        float theta = degrees(atan(pos.z/pos.x))+180.f;
        TexCoords = vec2(theta/360.f,(pos.y + 1.f)/2.f);
    }
    else if(typeMapping==3){
        float r = sqrt((pos.x*pos.x) +(pos.y*pos.y)+(pos.z*pos.z));
        float theta = degrees(atan(pos.z/pos.x))+180.f;
        float phi = degrees(acos(pos.y/r));
        TexCoords = vec2(theta/360.f,1.f-(phi/180.f));
    }
    else if(typeMapping==4){
        vec2 UV;
        vec3 absVector = abs(pos);

        if(absVector.x >= absVector.y && absVector.x >= absVector.z)
        {
            if(pos.x < 0.0f)
                UV.x = pos.z/absVector.x;
            else
                UV.x = -pos.z/absVector.x;

            UV.y = pos.y/absVector.x;
        }
        else if(absVector.y >= absVector.x && absVector.y >= absVector.z)
        {
            if(pos.y < 0.0f)
                UV.y = pos.z/absVector.y;
            else
                UV.y = -pos.z/absVector.y;

            UV.x = pos.x/absVector.y;
        }
        else if(absVector.z >= absVector.x && absVector.z >= absVector.y)
        {
            if(pos.z < 0.0f)
                UV.x = -pos.x/absVector.z;
            else
                UV.x = pos.x/absVector.z;

            UV.y = pos.y/absVector.z;
        }

        TexCoords = (UV+vec2(1))/2.0;
    }
    
}