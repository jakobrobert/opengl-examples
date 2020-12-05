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

    // TODO Remove old code
    // specify vertex layout by setting the vertex attributes
    // vertex array and vertex buffer need to be bound
    // vertex attributes are part of the state of the vertex array
    // unsigned int positionSize = 2;
    // unsigned int colorSize = 3;
    // unsigned int vertexSize = positionSize + colorSize;
    // unsigned int positionLocation = m_shader->getAttributeLocation("position");
    // unsigned int offset = 0;
    // m_vertexArray->setVertexAttribute(positionLocation, positionSize, vertexSize, offset);
    // offset += positionSize;
    // unsigned int colorLocation = m_shader->getAttributeLocation("color");
    // m_vertexArray->setVertexAttribute(colorLocation, colorSize, vertexSize, offset);

    // TODO integrate
    VertexLayout layout;
    layout.addAttribute(m_shader->getAttributeLocation("position"), 2);
    layout.addAttribute(m_shader->getAttributeLocation("color"), 3);
    m_vertexArray->setVertexLayout(layout);

    m_vertexBuffer->unbind();
    m_vertexArray->unbind();

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
    m_shader->bind();
    m_vertexArray->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_shader->unbind();
    m_vertexArray->unbind();
}
