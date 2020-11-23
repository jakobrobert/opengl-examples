#include "core/Window.hpp"

#include <iostream>
#include <stdexcept>

static void errorCallback(int error, const char* description)
{
    std::cout << "GLFW error " << error << ": " << description << std::endl;
}

Window::Window(const char* title, int width, int height, Renderer* renderer)
{
    glfwSetErrorCallback(errorCallback);
    
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGL()) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize glad!");
    }

    // TODO: extract loop into public function
    renderer->onInit();

    while (!glfwWindowShouldClose(m_window)) {
        renderer->onDraw();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    renderer->onDestroy();
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
