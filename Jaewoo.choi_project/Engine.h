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
    RendOBJ *cube;

};