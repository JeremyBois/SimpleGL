# Leaning OpenGl by implementing an engine

**Last update 2018-02-17**

## Getting started

**Build:**
```
mkdir build && cd build/
cmake .. -G "Unix Makefiles"
make
```

**Run:**
```
../samples/Game/bin/Debug/OpenGl-Game
```



## Try it out

**Assume a US keyboard layout**

*Global control*:

  - **C** --> Change culling mode
  - **V** --> Change Fill mode


*Control the container*:

  - **W** --> Change wrap mode
  - **F** --> Change filtering
  - **PageUp** --> Scale UV up
  - **PageUp** --> Scale UV down


*Control the debug camera*:

  - **Mouse movements** --> Rotations
  - **Mouse scroll**    --> Zoom
  - **Arrow keys**      --> Move


## Notes

Last released of GLM (**9.8.5**) does not recognize GCC 7.3.

`glm/simd/platform.h` has been updated with the following in the gcc section:
```
#   elif (__GNUC__ == 7) && (__GNUC_MINOR__ == 3)
#       define GLM_COMPILER (GLM_COMPILER_GCC72)
```
