# Resources
# http://florian-goujeon.developpez.com/cours/cmake/initiation/
# https://tuannguyen68.gitbooks.io/learning-cmake-a-beginner-s-guide/content/chap1/chap1.html
# http://ttroy50.github.io/cmake-examples/

# ------------------------------------------------------------------------------
# OUT OF SOURCE BUILD
# https://cmake.org/Wiki/CMake_FAQ#What_is_an_.22out-of-source.22_build.3F
# ------------------------------------------------------------------------------
# cd build/ && cmake .. -G "Unix Makefiles"


# ------------------------------------------------------------------------------
# Start Cmake syntax
# ------------------------------------------------------------------------------
# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)

# Project's name --> Set PROJECT_NAME variable
project("Learning OpenGL")



# ------------------------------------------------------------------------------
# Provide default build type (Debug)
# ------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# Use clang if None exists
if(NOT CMAKE_C_COMPILER AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting C compiler to 'clang' as none was specified.")
  set(CMAKE_C_COMPILER clang CACHE STRING "Choose the compiler." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_C_COMPILER PROPERTY STRINGS "clang" "gcc")
endif()

# Use clang++ if None exists
if(NOT CMAKE_CXX_COMPILER AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting C++ compiler to 'clang++' as none was specified.")
  set(CMAKE_CXX_COMPILER clang++ CACHE STRING "Choose the compiler." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_CXX_COMPILER PROPERTY STRINGS "clang++" "gcc++")
endif()


# # ------------------------------------------------------------------------------
# # Specific flags based on operating system (old way / not recommanded)
# # ------------------------------------------------------------------------------
# if (UNIX)
#   message(status " *** Setting GCC flags")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -Wall -Wextra")
#   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O -Wall -Wextra -fexceptions -pedantic -g -Wno-unused-parameter")
# else()
#   message(status " *** Setting MSVC flags")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
# endif()
# message(status " *** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
# message(status " *** CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")




# ------------------------------------------------------------------------------
# Open GL from system
# ------------------------------------------------------------------------------
find_package(OpenGL
    3.3
    REQUIRED
)
if(OPENGL_FOUND)
    message(status " *** OPENGL: ${OPENGL_gl_LIBRARY}")
else()
    message(FATAL_ERROR "OPENGL 3.3 library not found - required for GLFW")
endif()


# ------------------------------------------------------------------------------
# GLFW
# See http://www.glfw.org/docs/3.0/build.html#build_link_cmake_pkgconfig
# See https://github.com/PixarAnimationStudios/OpenSubdiv/blob/master/cmake/FindGLFW.cmake
# ------------------------------------------------------------------------------
if (UNIX)
    message(status " *** Checking for Linux required files for GLFW.")
    find_package(PkgConfig REQUIRED)
    find_package(Threads REQUIRED)
    find_package(X11 REQUIRED)
    if(NOT X11_Xrandr_FOUND)
        message(FATAL_ERROR "Xrandr library not found - required for GLFW")
    endif()

    if(NOT X11_xf86vmode_FOUND)
        message(FATAL_ERROR "xf86vmode library not found - required for GLFW")
    endif()

    if(NOT X11_Xcursor_FOUND)
        message(FATAL_ERROR "Xcursor library not found - required for GLFW")
    endif()

    if(NOT X11_Xinerama_FOUND)
        message(FATAL_ERROR "Xinerama library not found - required for GLFW")
    endif()

    if(NOT X11_Xi_FOUND)
        message(FATAL_ERROR "Xi library not found - required for GLFW")
    endif()

    # All needed by GLFW
    list(APPEND GLFW_x11_LIBRARY "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xcursor_LIB}"
                                 "${X11_Xinerama_LIB}" "${X11_Xi_LIB}" "${X11_LIBRARIES}"
                                 "${CMAKE_THREAD_LIBS_INIT}" -lrt -ldl)
endif()

pkg_search_module(GLFW REQUIRED glfw3)
message(status " *** GLFW: ${GLFW_LIBRARIES} ${GLFW_x11_LIBRARY}")






# ------------------------------------------------------------------------------
# Where to find sources
# ------------------------------------------------------------------------------
file(
    GLOB
    binary_SOURCES
    src/*
    ${PROJECT_SOURCE_DIR}/extern/GLAD/src/*   // From GLAD
)


# ------------------------------------------------------------------------------
# Create a executable target
# ------------------------------------------------------------------------------
add_executable(
    OpenGl-Tuto1 ${binary_SOURCES}
)

# Command to add include directories for a specifc target (replace include_directories)
# See https://learnopengl.com/Getting-started/Creating-a-window for GLAD
target_include_directories(OpenGl-Tuto1
    PRIVATE
        ${GLFW_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/extern/KHR
        ${PROJECT_SOURCE_DIR}/extern/GLAD/include
    PRIVATE
        BEFORE ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(OpenGl-Tuto1
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
)


target_link_libraries(OpenGl-Tuto1
    ${OPENGL_gl_LIBRARY}
    ${GLFW_x11_LIBRARY}
    ${GLFW_LIBRARIES}
)

target_compile_definitions(OpenGl-Tuto1
    PUBLIC
        fexceptions
        Wall
        Wextra
)



# # ------------------------------------------------------------------------------
# # Create a static and shared library target.
# # ------------------------------------------------------------------------------
# file(
#     GLOB
#     library_SOURCES
#     src/*
#     ${PROJECT_SOURCE_DIR}/extern/GLAD/src/*   // From GLAD
# )

# # Static
# add_library(OpenGl_lib_static STATIC ${library_SOURCES})

# target_include_directories(OpenGl_lib_static
#     PUBLIC ${PROJECT_SOURCE_DIR}/include
#     PRIVATE
#         ${GLFW_INCLUDE_DIRS}
#         ${PROJECT_SOURCE_DIR}/extern/KHR
#         ${PROJECT_SOURCE_DIR}/extern/GLAD/include
# )

# set_target_properties(OpenGl_lib_static
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
# )

# target_link_libraries(OpenGl_lib_static
#     ${OPENGL_gl_LIBRARY}
#     ${GLFW_x11_LIBRARY}
#     ${GLFW_LIBRARIES}
# )

# # Read only alias
# add_library(OpenGL::static_lib ALIAS OpenGl_lib_static)


# # Dynamic
# add_library(OpenGl_lib_shared SHARED ${library_SOURCES})

# target_include_directories(OpenGl_lib_shared
#     PUBLIC ${PROJECT_SOURCE_DIR}/include
#     PRIVATE
#         ${GLFW_INCLUDE_DIRS}
#         ${PROJECT_SOURCE_DIR}/extern/KHR
#         ${PROJECT_SOURCE_DIR}/extern/GLAD/include
# )

# set_target_properties(OpenGl_lib_shared
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
# )

# target_link_libraries(OpenGl_lib_shared
#     ${OPENGL_gl_LIBRARY}
#     ${GLFW_x11_LIBRARY}
#     ${GLFW_LIBRARIES}
# )

# # Read only alias
# add_library(OpenGL::shared_lib ALIAS OpenGl_lib_shared)


# # ------------------------------------------------------------------------------
# # Link library to another binary (for example lib == engine and exe == game)
# # A better idea will be to create another CMakeLists.txt in the Game folder...
# # ------------------------------------------------------------------------------

# file(
#     GLOB
#     game_binary_SOURCES
#     samples/Game/src/*
# )

# add_executable(
#     OpenGl-Game ${game_binary_SOURCES}
# )

# # Command to add include directories (replace include_directories)
# # See https://learnopengl.com/Getting-started/Creating-a-window for GLAD
# target_include_directories(OpenGl-Game
#     PRIVATE
#         BEFORE ${PROJECT_SOURCE_DIR}/samples/Game/include
# )

# set_target_properties(OpenGl-Game
#     PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/samples/Game/bin/${CMAKE_BUILD_TYPE}"
# )

# # Using dynamic lib
# target_link_libraries(OpenGl-Game
#     OpenGL::shared_lib
# )

# # # Using static lib
# # target_link_libraries(OpenGl-Game
# #     PRIVATE OpenGL::static_lib
# # )



