add_executable(01-window
    src/main.cpp
    src/EmptyRenderer.cpp
)
target_link_libraries(01-window PRIVATE core)
