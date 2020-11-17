set(SRC_FILES
    src/Core.hpp
)

add_library(core STATIC ${SRC_FILES})

# Add glfw library
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_INSTALL OFF)
add_subdirectory(vendor/glfw)
target_include_directories(core PUBLIC vendor/glfw/include)
target_link_libraries(core PUBLIC ${glfw_LIBRARIES})
