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
    // TODO: change to 2D-coord
    float vertices[3 * 3] = {
        // in xy-plane, counter-clockwise order
        -0.5f, -0.5f, 0.0f, // left bottom
        0.5f, -0.5f, 0.0f,  // right bottom
        0.0f, 0.5, 0.0f,    // center top
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // define vertex layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    // create shader
    GLuint shader = createShader("foo", "bar");
    if (!shader) {
        return 1;
    }

    glClearColor(0.0f, 0.0, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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

    GLFWwindow* window = glfwCreateWindow(1280, 720, "02 - Triangle", nullptr, nullptr);
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

        std::cerr << "Failed to link program!" << std::endl;
        std::cerr << infoLog.data() << std::endl;

        return 0;
    }

    // clean up, do not need temporary compile results
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return program;
}
