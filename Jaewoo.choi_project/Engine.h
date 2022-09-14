#pragma once

class Engine
{
public:
    Engine();
    ~Engine();
    void init();
    void Update();

    void Draw();
    bool ShouldClose();


};