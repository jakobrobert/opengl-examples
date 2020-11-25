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

    // define vertex layout (is stored in state of vertex array)
    glEnableVertexAttribArray(0); // 0 = location in shader of "position" attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1); // 1 = location in shader of "color" attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

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
    m_shader->bind();

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

    // TODO: move bind and unbind calls into here

    // draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
