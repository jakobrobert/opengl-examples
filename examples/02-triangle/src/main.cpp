#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "core/Core.hpp"

static GLFWwindow* createWindow();
static void errorCallback(int error, const char* description);

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