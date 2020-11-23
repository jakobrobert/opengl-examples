#include <iostream>
#include <string>
#include <vector>

#include "core/Window.hpp"

#include "TriangleRenderer.hpp"

static GLuint createShader(const std::string& vertexSource, const std::string& fragmentSource);

int main()
{
    try
    {
        TriangleRenderer renderer;
        Window window("02 - Triangle", 800, 800, &renderer);
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
