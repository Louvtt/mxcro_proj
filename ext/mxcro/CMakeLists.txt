find_package(OpenGL REQUIRED)
add_subdirectory(ext)

## SETUP FILES

set(HEADER_FILES
    include/mx/buffers.h
    include/mx/context.h
    include/mx/math.h
    include/mx/shader.h
    include/mx/types.h
    include/mx/contextRender.h
    include/mx/renderAttributeTypes.h
    include/mx/uniformBuffer.h
    include/mx/texture.h
)

set(SRC_FILES
    src/buffers.cpp
    src/math.cpp
    src/shader.cpp

    src/context.cpp
    src/contextRender.cpp
    src/renderAttributeTypes.cpp
    src/uniformBuffer.cpp

    src/texture.cpp
)

find_package(X11 REQUIRED)
if(X11_FOUND)
    list(APPEND SRC_FILES src/context_x11.cpp)
endif()
if(WIN32)
    list(APPEND SRC_FILES src/context_win32.cpp)
endif()

## BUILD LIB

add_library(
    MXCRO STATIC
    ${HEADER_FILES}
    ${SRC_FILES}
)
set_property(TARGET MXCRO PROPERTY CXX_STANDARD 17)

target_link_libraries(MXCRO
    PUBLIC GLAD
)

target_include_directories(MXCRO
PUBLIC
    include
    ext/glad/include
    ext/stb/include
)

## Platform support

if(X11_FOUND)
    target_link_libraries(MXCRO PUBLIC X11 ${X11_LIBRARIES})
endif()
if(WIN32)
    target_link_libraries(MXCRO PRIVATE "Dwmapi.lib")
endif()
