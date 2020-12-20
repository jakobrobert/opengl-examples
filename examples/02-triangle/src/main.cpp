#include <iostream>
#include <string>
#include <vector>

#include <core/Window.hpp>

#include "TriangleRenderer.hpp"

int main()
{
    try
    {
        TriangleRenderer renderer;
        Window window("02 - Triangle", 800, 800, &renderer);
        window.runRenderLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
