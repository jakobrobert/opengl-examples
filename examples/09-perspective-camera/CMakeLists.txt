add_executable(09-perspective-camera
    src/main.cpp
    src/PerspectiveCameraRenderer.cpp
)
target_link_libraries(09-perspective-camera PRIVATE core)

# copy assets from source directory to build directory
# important to leave out trailing slash in source directory,
# else, the content of "assets" directory is copied directly
# but without the "assets" directory level
file(COPY "./assets" DESTINATION "./")
