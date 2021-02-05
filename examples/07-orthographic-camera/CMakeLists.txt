add_executable(07-orthographic-camera
    src/main.cpp
    src/OrthographicCameraRenderer.cpp
)
target_link_libraries(07-orthographic-camera PRIVATE core)

# copy assets from source directory to build directory
# important to leave out trailing slash in source directory,
# else, the content of "assets" directory is copied directly
# but without the "assets" directory level
file(COPY "./assets" DESTINATION "./")
