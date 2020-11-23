#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.hpp"

class Window
{
public:
    Window(const char* title, int width, int height, Renderer* renderer);
    ~Window();
private:
    GLFWwindow* m_window = nullptr;
};
