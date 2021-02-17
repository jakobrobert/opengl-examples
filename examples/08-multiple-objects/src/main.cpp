#include <iostream>
#include <string>
#include <vector>

#include <core/Window.hpp>

#include "MultipleObjectsRenderer.hpp"

int main()
{
    try {
        MultipleObjectsRenderer renderer;
        Window window("08 - Multiple Objects", 800, 600, &renderer);
        window.runRenderLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
