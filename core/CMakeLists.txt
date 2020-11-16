add_library(core STATIC)

# Add glfw library
add_subdirectory(vendor/glfw)
target_include_directories(core PUBLIC vendor/glfw/include)
target_link_libraries(core PUBLIC ${glfw_LIBRARIES})
