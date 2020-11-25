#include "core/gl/ShaderProgram.hpp"

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

ShaderProgram::ShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
    // TODO Refactor, extract compileShader(type, source)

    // compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertexSourceCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCStr, 0);
    glCompileShader(vertexShader);

    // check for compile errors
    int isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        // get error message
        int maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // clean up
        glDeleteShader(vertexShader);

        // TODO combine message into exception?
        std::cerr << "Failed to compile vertex shader!" << std::endl;
        std::cerr << infoLog.data() << std::endl;

        throw std::runtime_error("Failed to compile vertex shader!");
    }

    // compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSourceCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceCStr, 0);
    glCompileShader(fragmentShader);

    // check for compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        // get error message
        int maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // clean up
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        // TODO combine message into exception?
        std::cerr << "Failed to compile fragment shader!" << std::endl;
        std::cerr << infoLog.data() << std::endl;

        throw std::runtime_error("Failed to compile fragment shader!");
    }

    // link vertex and fragment shader into program
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // check for link errors
    int isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        // get error message
        int maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // clean up
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // TODO combine message into exception?
        std::cerr << "Failed to link shader program!" << std::endl;
        std::cerr << infoLog.data() << std::endl;

        throw std::runtime_error("Failed to link shader program!");
    }

    // clean up, do not need temporary compile results
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_id = program;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

void ShaderProgram::bind() const
{
    glUseProgram(m_id);
}

void ShaderProgram::unbind() const
{
    glUseProgram(0);
}
