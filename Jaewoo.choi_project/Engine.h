/* !
@file    Engine.h
@author  jaewoo.choi@digipen.edu
@date    15/09/2022


*//*__________________________________________________________________________*/
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