add_executable(05-texture
    src/main.cpp
    src/TextureRenderer.cpp
)
target_link_libraries(05-texture PRIVATE core)

# copy assets from source directory to build directory
# important to leave out trailing slash in source directory,
# else, the content of "assets" directory is copied directly
# but without the "assets" directory level
file(COPY "./assets" DESTINATION "./")
