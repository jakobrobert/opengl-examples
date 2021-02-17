#include <iostream>
#include <string>
#include <vector>

#include <core/Window.hpp>

#include "PerspectiveCameraRenderer.hpp"

int main()
{
    try {
        PerspectiveCameraRenderer renderer;
        Window window("09 - Perspective Camera", 800, 600, &renderer);
        window.runRenderLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
