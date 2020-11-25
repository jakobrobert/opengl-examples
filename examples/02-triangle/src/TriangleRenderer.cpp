#include "TriangleRenderer.hpp"

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

static GLuint createShader(const std::string &vertexSource, const std::string &fragmentSource);

bool TriangleRenderer::onInit()
{
    // create vertex array
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);

    // create vertex buffer (is part of state of vertex array)
    float vertices[] = {
        // counter-clockwise order
        // position     color
        -0.5f, -0.5f, 1.0, 0.0, 0.0, // left bottom, red
        0.5f, -0.5f, 0.0, 1.0, 0.0,  // right bottom, green
        0.0f, 0.5, 0.0, 0.0, 1.0     // center top, blue
    };
    m_vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    m_vertexBuffer->bind();

    /*
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    */

    // define vertex layout (is part of state of vertex array)
    glEnableVertexAttribArray(0); // 0 = location in shader of "position" attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1); // 1 = location in shader of "color" attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));

    // create shader
    std::string vertexSource = R"(
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

    std::string fragmentSource = R"(
            #version 330 core

            in vec3 fragColor;
            out vec4 outColor;

            void main()
            {
                outColor = vec4(fragColor, 1.0);
            }
        )";

    m_shader = createShader(vertexSource, fragmentSource);
    if (!m_shader) {
        return false;
    }
    glUseProgram(m_shader);

    // black background
    glClearColor(0.0f, 0.0, 0.0f, 1.0f);

    return true;
}

void TriangleRenderer::onDestroy()
{
    // clean up: delete all opengl resources
    glDeleteVertexArrays(1, &m_vertexArray);
    delete m_vertexBuffer;
    glDeleteProgram(m_shader);
}

void TriangleRenderer::onDraw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

static GLuint createShader(const std::string &vertexSource, const std::string &fragmentSource)
{
    // compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertexSourceCStr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCStr, 0);
    glCompileShader(vertexShader);

    // check for compile errors
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        // get error message
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // clean up
        glDeleteShader(vertexShader);

        std::cerr << "Failed to compile vertex shader!" << std::endl;
        std::cerr << infoLog.data() << std::endl;

        return 0;
    }

    // compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragmentSourceCStr = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceCStr, 0);
    glCompileShader(fragmentShader);

    // check for compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        // get error message
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // clean up
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        std::cerr << "Failed to compile fragment shader!" << std::endl;
        std::cerr << infoLog.data() << std::endl;

        return 0;
    }

    // link vertex and fragment shader into program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // check for link errors
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        // get error message
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // clean up
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        std::cerr << "Failed to link shader program!" << std::endl;
        std::cerr << infoLog.data() << std::endl;

        return 0;
    }

    // clean up, do not need temporary compile results
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
