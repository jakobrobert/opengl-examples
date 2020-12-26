add_executable(06-transformations
    src/main.cpp
    src/TransformationsRenderer.cpp
)
target_link_libraries(06-transformations PRIVATE core)

# copy assets from source directory to build directory
# important to leave out trailing slash in source directory,
# else, the content of "assets" directory is copied directly
# but without the "assets" directory level
file(COPY "./assets" DESTINATION "./")
