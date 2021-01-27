***

# Discontinued project for [TEFNOUT](https://github.com/JeremyBois/Tefnout)

***

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

***
**Global control**:

  - **C** --> Change culling mode
  - **V** --> Change Fill mode
  - **1** --> Go to scene 1 (with container)
  - **2** --> Go to scene 2 (lighting)

*Control the debug camera*:

  - **Mouse movements** --> Rotations
  - **Mouse scroll**    --> Zoom
  - **Arrow keys**      --> Move



***
**Scene 1**:

*Control the container*:

  - **W** --> Change wrap mode
  - **F** --> Change filtering
  - **PageUp** --> Scale UV up
  - **PageUp** --> Scale UV down





## Notes

Last released of GLM (**9.8.5**) does not recognize GCC 7.3.

`glm/simd/platform.h` has been updated with the following in the gcc section:
```
#   elif (__GNUC__ == 7) && (__GNUC_MINOR__ == 3)
#       define GLM_COMPILER (GLM_COMPILER_GCC72)
```



## Other

  - [GDB](https://betterexplained.com/articles/debugging-with-gdb/)
