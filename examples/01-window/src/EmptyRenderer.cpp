#include "EmptyRenderer.hpp"

#include <glad/glad.h>

void EmptyRenderer::onInit()
{
    // magenta background
    glClearColor(1.0f, 0.0, 1.0f, 1.0f);
}

void EmptyRenderer::onDraw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);
}
