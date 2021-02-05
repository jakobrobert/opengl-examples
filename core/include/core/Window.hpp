#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <core/Renderer.hpp>

class Window
{
public:
    Window(const std::string& title, int width, int height, Renderer* renderer);
    ~Window();

    void runRenderLoop();
    int getKey(int keyCode) const;
private:
    GLFWwindow* m_window = nullptr;
    Renderer* m_renderer = nullptr;
};
