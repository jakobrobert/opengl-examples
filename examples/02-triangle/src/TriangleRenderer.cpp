#include "TriangleRenderer.hpp"

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

bool TriangleRenderer::onInit()
{
    // create vertex array
    m_vertexArray = new VertexArray();
    m_vertexArray->bind();

    // create vertex buffer
    float vertices[] = {
        // counter-clockwise order
        // position     color
        -0.5f, -0.5f, 1.0, 0.0, 0.0, // left bottom, red
        0.5f, -0.5f, 0.0, 1.0, 0.0,  // right bottom, green
        0.0f, 0.5, 0.0, 0.0, 1.0     // center top, blue
    };
    m_vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    m_vertexBuffer->bind();

    // TODO retrieve attrib locations from shader by name, better than hardcoding (remove layout specifier in shader source)
    // vertex array and vertex buffer need to be bound while setting the vertex attributes
    // vertex attributes are part of the state of the vertex array
    int positionLocation = 0;
    int colorLocation = 1;
    m_vertexArray->setVertexAttrib(positionLocation, 2, 5, 0);
    m_vertexArray->setVertexAttrib(colorLocation, 3, 5, 2);
    
    m_vertexBuffer->unbind();
    m_vertexArray->unbind();

    // TODO load shader source from file
    // create shader
    std::string vertexShaderSource = R"(
            #version 330 core

            layout(location = 0) in vec2 position;
            layout(location = 1) in vec3 color;
            out vec3 fragColor;

            void main()
            {
                gl_Position = vec4(position, 0.0, 1.0);
                fragColor = color;
            }
        )";

    std::string fragmentShaderSource = R"(
            #version 330 core

            in vec3 fragColor;
            out vec4 outColor;

            void main()
            {
                outColor = vec4(fragColor, 1.0);
            }
        )";
    m_shader = new ShaderProgram(vertexShaderSource, fragmentShaderSource);

    // black background
    glClearColor(0.0f, 0.0, 0.0f, 1.0f);

    return true;
}

void TriangleRenderer::onDestroy()
{
    // clean up: delete all opengl objects
    delete m_vertexArray;
    delete m_vertexBuffer;
    delete m_shader;
}

void TriangleRenderer::onDraw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // draw the triangle
    // binding and unbinding not necessary because they are the same objects each time
    // just to keep it more organized, easier to extend
    m_vertexArray->bind();
    m_shader->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_vertexArray->unbind();
    m_shader->unbind();
}
