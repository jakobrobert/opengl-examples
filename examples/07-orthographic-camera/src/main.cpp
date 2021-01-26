#include <iostream>
#include <string>
#include <vector>

#include <core/Window.hpp>

#include "OrthographicCameraRenderer.hpp"

int main()
{
    try
    {
        OrthographicCameraRenderer renderer;
        Window window("07 - Orthographic Camera", 800, 600, &renderer);
        window.runRenderLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
