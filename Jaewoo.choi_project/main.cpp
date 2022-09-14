#include"Engine.h"

int main(void)
{
    Engine engine;

    engine.init();
    while (!engine.ShouldClose())
    {
        engine.Update();
        engine.Draw();
    }

    return 0;
}