/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.h
Purpose: <This file contains declaration of class Engine.>
Language: <c++>
Platform: <Visual studio 2019, OpenGL 4.5, Window 64bit>
Project: <jaewoo.choi_CS300_1>
Author: <Jaewoo Choi, jaewoo.choi, 55532>
Creation date: 14/09/2022
End Header --------------------------------------------------------*/
#pragma once
#include "RendOBJ.h"
class Engine
{
public:
    Engine();
    ~Engine();
    void init();
    void Update();

    void Draw();
    bool ShouldClose();
    RendOBJ *obj;

};