#include <core/Window.hpp>

#include <iostream>
#include <stdexcept>

static void errorCallback(int error, const char* description);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(const std::string& title, int width, int height, Renderer* renderer)
    : m_renderer(renderer)
{
    glfwSetErrorCallback(errorCallback);
    
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
    }

    // a trick to get access to the renderer in callbacks
    // cannot pass member function as callback
    glfwSetWindowUserPointer(m_window, m_renderer);

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    glfwMakeContextCurrent(m_window);
    
    // disable frame limiter
    glfwSwapInterval(0);

    if (!gladLoadGL()) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize glad!");
    }

    if (!m_renderer->onInit()) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize renderer!");
    }

    // call onResize() callback for initial size
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(m_window, &bufferWidth, &bufferHeight);
    m_renderer->onResize(bufferWidth, bufferHeight);
}

Window::~Window()
{
    m_renderer->onDestroy();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::runRenderLoop()
{
    float prevTime = (float)(glfwGetTime());

    while (!glfwWindowShouldClose(m_window)) {
        double currTime = (float)(glfwGetTime());
        double frameTime = currTime - prevTime;
        prevTime = currTime;

        m_renderer->onUpdate(*this, frameTime);
        m_renderer->onDraw();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

int Window::getKey(int keyCode) const
{
    return glfwGetKey(m_window, keyCode);
}

static void errorCallback(int error, const char *description)
{
    std::cout << "GLFW error " << error << ": " << description << std::endl;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Renderer* renderer = (Renderer*)glfwGetWindowUserPointer(window);
    renderer->onResize(width, height);
}
