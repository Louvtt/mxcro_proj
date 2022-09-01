cmake_minimum_required(VERSION 3.0)
project(MXCROPROJ VERSION 0.0.1)

add_subdirectory(ext)

add_executable(MXCROPROJ src/main.cpp)

target_include_directories(MXCROPROJ
    PUBLIC ext/mxcro/include
    PUBLIC ext/mxphsx/include
    PUBLIC src/
)

target_link_libraries(MXCROPROJ
PUBLIC
    MXCRO
    MXPHSX
    GLAD
)

set_target_properties(MXCROPROJ PROPERTIES CXX_STANDARD 17)