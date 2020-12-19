#include "RectangleRenderer.hpp"

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

bool RectangleRenderer::onInit()
{
    // create shader
    std::string shaderFilename = "assets/shaders/uniform_color";
    m_shader = new ShaderProgram(shaderFilename + ".vert", shaderFilename + ".frag");
    // get uniform locations
    m_colorUniformLocation = m_shader->getUniformLocation("u_color");

    // create vertex array
    m_vertexArray = new VertexArray();
    m_vertexArray->bind();

    // create vertex buffer 
    float vertices[] = {
        // counter-clockwise order
        // position
        -0.5f, -0.5f,   // left bottom
        0.5f, -0.5f,    // right bottom
        0.5f, 0.5f,     // right top
        -0.5f, 0.5f,    // left top
    };
    m_vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    // connect vertex buffer to vertex array
    m_vertexBuffer->bind();

    // specify vertex layout
    VertexLayout layout;
    layout.addAttribute(m_shader->getAttributeLocation("a_position"), 2);
    // connect vertex layout to vertex array
    m_vertexArray->setVertexLayout(layout);

    // create index buffer
    unsigned int indices[6] {
        // counter-clockwise order
        0, 1, 2,    // right bottom triangle
        2, 3, 0     // left top triangle
    };
    m_indexBuffer = new IndexBuffer(indices, 6);
    // connect index buffer to vertex array
    m_indexBuffer->bind();
    
    // unbind objects to leave a clean state
    m_vertexArray->unbind();
    m_vertexBuffer->unbind();
    m_indexBuffer->unbind();

    // black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

    // draw the rectangle
    // binding and unbinding not necessary because they are the same objects each time
    // just to keep it more organized, easier to extend
    m_shader->bind();
    glUniform3f(m_colorUniformLocation, 1.0f, 0.0f, 0.0f);  // red
    m_vertexArray->bind();
    glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
    m_shader->unbind();
    m_vertexArray->unbind();
}
