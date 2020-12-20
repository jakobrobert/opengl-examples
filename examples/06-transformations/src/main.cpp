#include <iostream>
#include <string>
#include <vector>

#include <core/Window.hpp>

#include "TransformationsRenderer.hpp"

int main()
{
    try
    {
        TransformationsRenderer renderer;
        Window window("06 - Transformations", 800, 800, &renderer);
        window.runRenderLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
