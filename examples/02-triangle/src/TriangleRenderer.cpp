#include "TriangleRenderer.hpp"

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

#include "core/util/VertexLayout.hpp"

bool TriangleRenderer::onInit()
{
    // create shader
    std::string shaderFilename = "assets/shaders/vertex_color";
    m_shader = new ShaderProgram(shaderFilename + ".vert", shaderFilename + ".frag");

    // create vertex array
    m_vertexArray = new VertexArray();
    m_vertexArray->bind();

    // create vertex buffer
    float vertices[] = {
        // counter-clockwise order
        // position         color
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   // left bottom, red
        0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   // right bottom, green
        0.0f, 0.5f,     0.0, 0.0f, 1.0f     // center top, blue
    };
    m_vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    m_vertexBuffer->bind();

    // specify vertex layout
    VertexLayout layout;
    layout.addAttribute(m_shader->getAttributeLocation("a_position"), 2);
    layout.addAttribute(m_shader->getAttributeLocation("a_color"), 3);
    // connect vertex layout to vertex array
    m_vertexArray->setVertexLayout(layout);

    // unbind objects to leave a clean state
    m_vertexArray->unbind();
    m_vertexBuffer->unbind();

    // black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return true;
}

void TriangleRenderer::onDestroy()
{
    // clean up: delete all opengl objects
    delete m_shader;
    delete m_vertexArray;
    delete m_vertexBuffer;
}

void TriangleRenderer::onDraw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // draw the triangle
    // binding and unbinding not necessary because they are the same objects each time
    // just to keep it more organized, easier to extend
    m_shader->use();
    m_vertexArray->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_shader->unuse();
    m_vertexArray->unbind();
}
