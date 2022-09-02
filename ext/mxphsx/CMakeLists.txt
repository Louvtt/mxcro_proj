set(HEADER_FILES
    include/mxphsx/math.h
    include/mxphsx/world.h
    include/mxphsx/rigidbody.h
    include/mxphsx/colliders.h
    include/mxphsx/narrowphase.h
    include/mxphsx/broadphase.h
)

set(SRC_FILES
    src/math.cpp
    src/colliders.cpp
    src/rigidbody.cpp
    src/world.cpp
    src/broadphase.cpp
    src/narrowphase.cpp
)

add_library(
    MXPHSX STATIC
    ${HEADER_FILES}
    ${SRC_FILES}
)
set_property(TARGET MXPHSX PROPERTY CXX_STANDARD 17)

target_include_directories(MXPHSX
PUBLIC
    include
)
