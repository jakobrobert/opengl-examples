add_executable(03-rectangle
    src/main.cpp
    src/RectangleRenderer.cpp
)
target_link_libraries(03-rectangle PRIVATE core)

# copy assets from source directory to build directory
# important to leave out trailing slash in source directory,
# else, the content of "assets" directory is copied directly
# but without the "assets" directory level
file(COPY "./assets" DESTINATION "./")
