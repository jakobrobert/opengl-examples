# Add source files to core
add_library(core
    src/Window.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
)
# Add include directory to core
target_include_directories(core PUBLIC include)

# Add glad library to core
add_library(glad vendor/glad/src/glad.c)
target_include_directories(glad PRIVATE vendor/glad/include)
target_include_directories(core PUBLIC vendor/glad/include)
target_link_libraries(core PUBLIC glad ${CMAKE_DL_LIBS})

# Add glfw library to core
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_INSTALL OFF)
add_subdirectory(vendor/glfw)
target_include_directories(core PUBLIC vendor/glfw/include)
target_compile_definitions(core PRIVATE GLFW_INCLUDE_NONE) # prevent glfw from loading gl functions, we use glad for that
target_link_libraries(core PUBLIC glfw ${glfw_LIBRARIES})
