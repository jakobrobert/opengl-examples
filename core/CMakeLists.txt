# Add source files to core
add_library(core
    src/Window.cpp
    src/gl/ShaderProgram.cpp
    src/gl/VertexArray.cpp
    src/gl/VertexBuffer.cpp
    src/gl/VertexLayout.cpp
    src/gl/IndexBuffer.cpp
    src/gl/Texture.cpp
    src/Transform2D.cpp
    src/Transform3D.cpp
    src/OrthographicCamera.cpp
    src/PerspectiveCamera.cpp
)

# Add include directory to core
# Make it public so client code can access it
target_include_directories(core PUBLIC include)

# Add glad library to core
add_library(glad vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)
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

# Add glm library to core
add_subdirectory(vendor/glm)
target_include_directories(core PUBLIC vendor/glm)
target_link_libraries(core PRIVATE glm)

# Add stb_image library to core
add_library(stb_image vendor/stb_image/src/stb_image.c)
target_include_directories(stb_image PUBLIC vendor/stb_image/include)
target_link_libraries(core PRIVATE stb_image)
