# Leaning OpenGl by implementing an engine

**Last update 2018-02-10**

## Getting started

```
# Build
cd build/
cmake .. -G "Unix Makefiles"
make

# Run
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


## Notes

Last released of GLM (**9.9.5**) does not recognize GCC 7.3.

`glm/simd/platform.h` should be updated with the following in the gcc section:
```
#   elif (__GNUC__ == 7) && (__GNUC_MINOR__ == 3)
#       define GLM_COMPILER (GLM_COMPILER_GCC72)
```
