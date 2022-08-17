add_library(GLAD STATIC
    glad/include/glad/gl.h
    glad/src/gl.c
)

target_link_libraries(
	GLAD
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)