add_executable(02-triangle
    src/main.cpp
    src/TriangleRenderer.cpp
)
target_link_libraries(02-triangle PRIVATE core)

# copy assets from source directory to build directory
# important to leave out trailing slash in source directory,
# else, the content of "assets" directory is copied directly
# but without the "assets" directory level
file(COPY "./assets" DESTINATION "./")
