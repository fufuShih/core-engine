#include "Core/Engine.hpp"
#include <iostream>

int main()
{
    auto &engine = Engine::GetInstance();

    if (!engine.Initialize())
    {
        std::cout << "Failed to initialize engine" << std::endl;
        return -1;
    }

    engine.Run();
    engine.Shutdown();

    return 0;
}