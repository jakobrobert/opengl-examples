#include <iostream>
#include <string>
#include <vector>

#include <core/Window.hpp>

#include "TextureRenderer.hpp"

int main()
{
    try
    {
        TextureRenderer renderer;
        Window window("05 - Texture", 800, 800, &renderer);
        window.runEventLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
