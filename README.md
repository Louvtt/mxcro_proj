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
- Simple batching of colored squares, lines and points (filled circles) [ContextRender class](ext/mxcro/include/mx/contextRender.h)
- Simple support for showing texture [Texture class](ext/mxcro/include/mx/texture.h)
- Simple support for shaders and SSBO (vertex and fragment) see [Shader class](ext/mxcro/include/mx/shader.h)
- Simple support for custom Shapes [ShapeDrawData class l.75](ext/mxcro/include/mx/buffers.h)
- Events throught registering function (i.e `registerOnKeyPress` in the [Context class](ext/mxcro/include/mx/context.h))
