cmake_minimum_required(VERSION 3.0)
project(MXCROPROJ VERSION 0.0.1)

add_executable(MXCROPROJ src/main.cpp)

target_include_directories(MXCROPROJ
    PUBLIC mxcro/include
    PUBLIC src/
)

add_subdirectory(mxcro)
target_link_libraries(MXCROPROJ
PUBLIC
    MXCRO
    GLAD
)

set_target_properties(MXCROPROJ PROPERTIES CXX_STANDARD 17)