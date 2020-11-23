#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(const char* title, int width, int height);
    ~Window();

    // TODO: only temporary
    GLFWwindow* getWindow() const { return m_window; }
private:
    GLFWwindow* m_window = nullptr;
};
