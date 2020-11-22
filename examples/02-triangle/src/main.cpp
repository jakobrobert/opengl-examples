#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

#include "core/Core.hpp"

static GLFWwindow* createWindow();
static void errorCallback(int error, const char* description);
static GLuint createShader(const std::string& vertexSource, const std::string& fragmentSource);

int main()
{
    GLFWwindow* window = createWindow();
    if (!window) {
        return 1;
    }

    // create vertex array
    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // create vertex buffer, bind it to the vertex array and copy data into it
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // define vertex data and upload it to buffer
    float vertices[] = {
        // counter-clockwise order
        // position     color
        -0.5f, -0.5f, 1.0, 0.0, 0.0,    // left bottom, red
        0.5f, -0.5f, 0.0, 1.0, 0.0,     // right bottom, green
        0.0f, 0.5, 0.0, 0.0, 1.0        // center top, blue
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // define vertex layout
    glEnableVertexAttribArray(0);   // 0 = location in shader of "position" attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);   // 1 = location in shader of "color" attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

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

    GLuint shader = createShader(vertexSource, fragmentSource);
    if (!shader) {
        return 1;
    }
    glUseProgram(shader);

    // black background
    glClearColor(0.0f, 0.0, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        // clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up: delete all opengl resources
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteProgram(shader);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static GLFWwindow* createWindow()
{
    glfwSetErrorCallback(errorCallback);
    
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "02 - Triangle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize glad!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    return window;
}

static void errorCallback(int error, const char* description)
{
    std::cout << "GLFW error " << error << ": " << description << std::endl;
}

static GLuint createShader(const std::string& vertexSource, const std::string& fragmentSource)
{
    // compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSourceCStr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCStr, 0);
    glCompileShader(vertexShader);

    // check for compile errors
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
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
    const GLchar* fragmentSourceCStr = fragmentSource.c_str();
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
