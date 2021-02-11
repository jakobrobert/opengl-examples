add_executable(08-multiple-objects
    src/main.cpp
    src/MultipleObjectsRenderer.cpp
)
target_link_libraries(08-multiple-objects PRIVATE core)

# copy assets from source directory to build directory
# important to leave out trailing slash in source directory,
# else, the content of "assets" directory is copied directly
# but without the "assets" directory level
file(COPY "./assets" DESTINATION "./")
