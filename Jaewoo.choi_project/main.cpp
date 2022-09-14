#include"Engine.h"

int main(void)
{
    Engine engine;

    while (!engine.ShouldClose())
    {
        engine.Update();
        engine.Draw();
    }

    return 0;
}