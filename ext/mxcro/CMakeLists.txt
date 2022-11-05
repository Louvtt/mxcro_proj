find_package(OpenGL REQUIRED)
add_subdirectory(ext)

## SETUP FILES

set(HEADER_FILES
    include/mx/core/context.hpp
    include/mx/core/types.hpp

    include/mx/gfx/buffers.hpp
    include/mx/gfx/shapeDrawData.hpp
    include/mx/gfx/shapeInstance.hpp
    include/mx/gfx/batch.hpp
    include/mx/gfx/shader.hpp
    include/mx/gfx/contextRender.hpp
    include/mx/gfx/contextRender3D.hpp
    include/mx/gfx/renderAttributeTypes.hpp
    include/mx/gfx/uniformBuffer.hpp
    include/mx/gfx/texture.hpp

    include/mx/maths/math.hpp
    include/mx/maths/vec2.hpp
    include/mx/maths/vec3.hpp
    include/mx/maths/mat4.hpp

    include/mx/io/keycodes.hpp
)

set(SRC_FILES
    src/core/context.cpp
    src/core/types.cpp

    src/gfx/buffers.cpp
    src/gfx/shapeDrawData.cpp
    src/gfx/shapeInstance.cpp
    src/gfx/shader.cpp
    src/gfx/contextRender.cpp
    src/gfx/contextRender3D.cpp
    src/gfx/renderAttributeTypes.cpp
    src/gfx/uniformBuffer.cpp
    src/gfx/texture.cpp

    src/maths/math.cpp
    src/maths/vec2.cpp
    src/maths/vec3.cpp
    src/maths/mat4.cpp
)

find_package(X11 REQUIRED)
if(X11_FOUND)
    list(APPEND SRC_FILES src/core/context_x11.cpp)
endif()
if(WIN32)
    list(APPEND SRC_FILES src/core/context_win32.cpp)
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
