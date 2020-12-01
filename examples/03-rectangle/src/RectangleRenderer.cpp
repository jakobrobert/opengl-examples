#include "RectangleRenderer.hpp"

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

bool RectangleRenderer::onInit()
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
        0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   // right top, blue
        -0.5f, 0.5f,    1.0f, 1.0f, 1.0f    // left top, white
    };
    m_vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    m_vertexBuffer->bind();

    // specify vertex layout by setting the vertex attributes
    // vertex array and vertex buffer need to be bound
    // vertex attributes are part of the state of the vertex array
    unsigned int positionSize = 2;
    unsigned int colorSize = 3;
    unsigned int vertexSize = positionSize + colorSize;
    unsigned int positionLocation = m_shader->getAttributeLocation("position");
    unsigned int offset = 0;
    m_vertexArray->setVertexAttribute(positionLocation, positionSize, vertexSize, offset);
    offset += positionSize;
    unsigned int colorLocation = m_shader->getAttributeLocation("color");
    m_vertexArray->setVertexAttribute(colorLocation, colorSize, vertexSize, offset);

    // create index buffer
    unsigned int indices[6] {
        // counter-clockwise order
        0, 1, 2,    // right bottom triangle
        2, 3, 0     // left top triangle
    };
    m_indexBuffer = new IndexBuffer(indices, 6);

    m_vertexBuffer->unbind();
    m_vertexArray->unbind();

    // black background
    glClearColor(0.0f, 0.0, 0.0f, 1.0f);

    return true;
}

void RectangleRenderer::onDestroy()
{
    // clean up: delete all opengl objects
    delete m_shader;
    delete m_vertexArray;
    delete m_vertexBuffer;
    delete m_indexBuffer;
}

void RectangleRenderer::onDraw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // draw the triangle
    // binding and unbinding not necessary because they are the same objects each time
    // just to keep it more organized, easier to extend
    m_shader->bind();
    m_vertexArray->bind();
    m_indexBuffer->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
    m_shader->unbind();
    m_vertexArray->unbind();
    m_indexBuffer->unbind();
}
