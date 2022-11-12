# MXCRO PROJECT TEMPLATE

## Build

The build tool is [CMake](http://cmake.org).

> Create a directory for the binaries like so `mkdir bin`
>
> Go inside the directory and run `cmake ..` (with the correct generator)
>
> Then you can build and try to run the project !

## Features

- Linux (Only X11) and Window support
- Simple batching of colored squares, lines and points (filled circles) [ContextRender class](ext/mxcro/include/mx/gfx/contextRender.hpp)
- Simple instanced draw with the [ContextRender3D class](ext/mxcro/include/mx/gfx/contextRender3D.hpp)
- Simple support for showing texture [Texture class](ext/mxcro/include/mx/gfx/texture.hpp)
- Simple support for shaders and [UBO](ext/mxcro/include/mx/gfx/uniformBuffer.hpp) (vertex and fragment) see the [Shader class](ext/mxcro/include/mx/gfx/shader.hpp)
- Simple support for custom Shapes [ShapeDrawData class](ext/mxcro/include/mx/gfx/shapeDrawData.hpp)
- Events throught an EventManager class (see the [EventManager class](ext/mxcro/include/mx/io/eventManager.hpp.hpp))
- Base mathematics utility classes like [mx::vec2](ext/mxcro/include/mx/maths/vec2.hpp), [mx::vec3](ext/mxcro/include/mx/maths/vec3.hpp) and [mx::mat4](ext/mxcro/include/mx/maths/mat4.hpp) (Quaternion in WIP)

## WIP
- Quaternion
- Refactoring of Platform Contexts
- Better abstraction of shape for 2D and 3D draw calls
- FrameBuffers
- SSBO