#include "EmptyRenderer.hpp"

#include <glad/glad.h>

bool EmptyRenderer::onInit()
{
    // magenta background
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    return true;
}

void EmptyRenderer::onResize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void EmptyRenderer::onDraw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);
}
