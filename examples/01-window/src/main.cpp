#include <iostream>

#include "core/Window.hpp"

int main()
{
    try {
        Window window("01 - Window", 800, 800);

        glClearColor(1.0f, 0.0, 1.0f, 1.0f);

        while (!glfwWindowShouldClose(window.getWindow())) {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
