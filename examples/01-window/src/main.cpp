#include <iostream>

#include "core/Window.hpp"

#include "EmptyRenderer.hpp"

int main()
{
    try {
        EmptyRenderer renderer;
        Window window("01 - Window", 800, 800, &renderer);
        window.runEventLoop();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
