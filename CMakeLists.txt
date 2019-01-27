# Resources
# http://florian-goujeon.developpez.com/cours/cmake/initiation/
# https://tuannguyen68.gitbooks.io/learning-cmake-a-beginner-s-guide/content/chap1/chap1.html
# http://ttroy50.github.io/cmake-examples/

# ------------------------------------------------------------------------------
# OUT OF SOURCE BUILD
# https://cmake.org/Wiki/CMake_FAQ#What_is_an_.22out-of-source.22_build.3F
# ------------------------------------------------------------------------------
# cd build/ && cmake .. -G "Unix Makefiles"
# cd build/ && cmake .. -G "MinGW Makefiles" -DCMAKE_SH=CMAKE_SH-NOTFOUND


# ------------------------------------------------------------------------------
# Start Cmake syntax
# ------------------------------------------------------------------------------
# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)

# Project's name*** Set PROJECT_NAME variable
project("Learning OpenGL")


# ------------------------------------------------------------------------------
# Provide default
# ------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("*** Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# Use clang if None exists
if(NOT CMAKE_C_COMPILER AND NOT CMAKE_CONFIGURATION_TYPES)
  message("*** Setting C compiler to 'clang' as none was specified.")
  set(CMAKE_C_COMPILER clang CACHE STRING "Choose the compiler." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_C_COMPILER PROPERTY STRINGS "clang" "gcc" "MSVC")
endif()

# Use clang++ if None exists
if(NOT CMAKE_CXX_COMPILER AND NOT CMAKE_CONFIGURATION_TYPES)
  message("*** Setting C++ compiler to 'clang++' as none was specified.")
  set(CMAKE_CXX_COMPILER clang++ CACHE STRING "Choose the compiler." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_CXX_COMPILER PROPERTY STRINGS "clang++" "gcc++" "MSVC")
endif()

# GLFW3
if(NOT GLFW_LOCATION AND NOT CMAKE_CONFIGURATION_TYPES)
  message("*** Setting default location to find GLFW.")
  set(GLFW_LOCATION "C:/Program Files (x86)/GLFW/" CACHE STRING "Choose GLFW location." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE GLFW_LOCATION PROPERTY STRINGS)
endif()

# ASSIMP
if(NOT ASSIMP_LOCATION AND NOT CMAKE_CONFIGURATION_TYPES)
  message("*** Setting default location to find ASSIMP.")
  set(ASSIMP_LOCATION "C:/Program Files (x86)/Assimp/" CACHE STRING "Choose ASSIMP location." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE ASSIMP_LOCATION PROPERTY STRINGS)
endif()


# # Informations (Debug)
# message("Your C++ compiler supports these C++ features:")
# foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
#     message("${i}")
# endforeach()

# message("Your CMake version supports these C++ features:")
# get_property(known_features GLOBAL PROPERTY CMAKE_CXX_KNOWN_FEATURES)
# foreach(i ${known_features})
#     message("${i}")
# endforeach()


# Get lib version from header
function(ParseGLFWVersion FILENAME VARNAME)
        set(PATTERN "^#define ${VARNAME}.*$")
        file(STRINGS "${GLFW_INCLUDE_DIR}/${FILENAME}" TMP REGEX ${PATTERN})
        string(REGEX MATCHALL "[0-9]+" TMP ${TMP})
        set(${VARNAME} ${TMP} PARENT_SCOPE)
endfunction()



# # ------------------------------------------------------------------------------
# # Specific flags based on operating system (old way / not recommanded)
# # ------------------------------------------------------------------------------
# if (UNIX)
#   message("*** Setting GCC flags")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -Wall -Wextra")
#   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O -Wall -Wextra -fexceptions -pedantic -g -Wno-unused-parameter")
# else()
#   message("*** Setting MSVC flags")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
# endif()
# message("*** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
# message("*** CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")




# ------------------------------------------------------------------------------
# Open GL from system
# ------------------------------------------------------------------------------

if (UNIX)
    if(NOT DEFINED OpenGL_GL_PREFERENCE)
        set(OpenGL_GL_PREFERENCE "GLVND")
    elseif(NOT OpenGL_GL_PREFERENCE MATCHES "^(GLVND|LEGACY)$")
          message(FATAL_ERROR
            "OpenGL_GL_PREFERENCE value '${OpenGL_GL_PREFERENCE}' not recognized.  "
            "Allowed values are 'GLVND' only ('LEGACY' is not allowed)."
            )
    endif()

    find_package(OpenGL
        3.3
        REQUIRED
    )
else()
    find_package(OpenGL REQUIRED)
endif()

# Status message
if(OPENGL_FOUND)
    message("*** Found GLFW")
    message("     OPENGL Library:  ${OPENGL_LIBRARIES}")
else()
    message(FATAL_ERROR "OPENGL 3.3 library not found - required for GLFW")
endif(OPENGL_FOUND)

# ------------------------------------------------------------------------------
# GLFW
# See http://www.glfw.org/docs/3.0/build.html#build_link_cmake_pkgconfig
# See https://github.com/PixarAnimationStudios/OpenSubdiv/blob/master/cmake/FindGLFW.cmake
# ------------------------------------------------------------------------------
if (UNIX)
    message("*** Checking for Linux required files for GLFW.")
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

    pkg_search_module(GLFW REQUIRED glfw3)
# WIN32
else(UNIX)
    # Look after headers
    find_path( GLFW_INCLUDE_DIR
        NAMES
            GLFW/glfw3.h
        HINTS
            "${GLFW_LOCATION}/include"
            "$ENV{GLFW_LOCATION}/include"
        PATHS
            "$ENV{PROGRAMFILES}/GLFW/include"
            "$ENV{PROGRAMFILES}/GLFW/include"
        DOC
            "The GLFW3 includes directory"
        )
    # Look after lib
    find_library(GLFW_LIBRARY
            NAMES
                glfw3
            HINTS
                "${GLFW_LOCATION}/lib"
                "$ENV{GLFW_LOCATION}/lib"
            PATHS
                "$ENV{PROGRAMFILES}/GLFW/lib"
            DOC
                "The GLFW3 library directory"
        )

    # Assume first that package is not found
    set( GLFW_FOUND "NO" )

    if(GLFW_LIBRARY)
        set( GLFW_LIBRARIES "${GLFW_LIBRARY}")
        set( GLFW_INCLUDE_DIRS "${GLFW_INCLUDE_DIR}")
        set( GLFW_FOUND "YES" )
    endif(GLFW_LIBRARY)

endif(UNIX)

if(NOT GLFW_FOUND)
    message(FATAL_ERROR "GLFW3 library not found")
else()
    message("*** Found GLFW ${glfw3_VERSION}")
    message("     GLFW Library: ${GLFW_LIBRARIES} ${GLFW_x11_LIBRARY}")
    message("     GLFW Headers: ${GLFW_INCLUDE_DIRS}")

    # Populate versions for GLFW
    if(EXISTS "${GLFW_INCLUDE_DIRS}/GLFW/glfw3.h")
        ParseGLFWVersion(GLFW/glfw3.h GLFW_VERSION_MAJOR)
        ParseGLFWVersion(GLFW/glfw3.h GLFW_VERSION_MINOR)
        ParseGLFWVersion(GLFW/glfw3.h GLFW_VERSION_REVISION)
    endif()
endif()


# # ------------------------------------------------------------------------------
# # Assimp
# # ------------------------------------------------------------------------------
# # # ASSIMP search path
# # set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_LIST_DIR}/assimp/)

# if(UNIX)
#     pkg_search_module(ASSIMP REQUIRED assimp)

#     set(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})
#     set(ASSIMP_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIR})

# else(UNIX)
#     # Look after headers
#     find_path( ASSIMP_INCLUDE_DIR
#         NAMES
#             assimp/postprocess.h
#             assimp/scene.h
#             assimp/version.h
#             assimp/config.h
#             assimp/cimport.h
#         HINTS
#             "${ASSIMP_LOCATION}/include"
#             "$ENV{ASSIMP_LOCATION}/include"
#         PATHS
#             "$ENV{PROGRAMFILES}/Assimp/include"
#         DOC
#             "The ASSIMP includes directory"
#         )
#     # Look after lib
#     find_library( ASSIMP_LIBRARY
#             NAMES
#                 libassimp
#             HINTS
#                 "${ASSIMP_LOCATION}/lib"
#                 "$ENV{ASSIMP_LOCATION}/lib"
#             PATHS
#                 "$ENV{PROGRAMFILES}/Assimp/lib"
#             DOC
#                 "The ASSIMP library directory"
#         )

#     # Assume first that package is not found
#     set( ASSIMP_FOUND "NO" )

#     if(ASSIMP_LIBRARY)
#         set( ASSIMP_LIBRARIES "${ASSIMP_LIBRARY}")
#         set( ASSIMP_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIR})
#         set( ASSIMP_FOUND "YES" )
#     endif(ASSIMP_LIBRARY)

# endif(UNIX)

# if(NOT ASSIMP_FOUND)
#     message(FATAL_ERROR "ASSIMP library not found - required for model loading")
# else()
#     message("*** Found ASSIMP")
#     message("     ASSIMP Library: ${ASSIMP_LIBRARIES}")
#     message("     ASSIMP Headers: ${ASSIMP_INCLUDE_DIRS}")
# endif()




# # ------------------------------------------------------------------------------
# # Create a executable target
# # ------------------------------------------------------------------------------
# file(
#     GLOB
#     library_SOURCES
#     src/Interface/*
#     src/Components/*
#     src/Services/*
#     src/OpenGL/*
#     src/OpenGL/2D/*
#     src/OpenGL/3D/*
#     src/Utility/*
#     src/*
#     ${PROJECT_SOURCE_DIR}/extern/GLAD/src/*   #[[ From GLAD (http://glad.dav1d.de/) ]]
#     ${PROJECT_SOURCE_DIR}/extern/STB/src/*    #[[ From stb_image (https://github.com/nothings/stb) ]]
# )

# add_executable(
#     SimpleGL ${binary_SOURCES}
# )

# # Command to add include directories for a specifc target (replace include_directories)
# # See https://learnopengl.com/Getting-started/Creating-a-window for GLAD
# target_include_directories(SimpleGL
#     PRIVATE
#         ${GLFW_INCLUDE_DIRS}
#         ${PROJECT_SOURCE_DIR}/extern/KHR
#         ${PROJECT_SOURCE_DIR}/extern/GLAD/include
#         ${PROJECT_SOURCE_DIR}/extern/STB/include
#     PRIVATE
#         BEFORE ${PROJECT_SOURCE_DIR}/include
# )

# set_target_properties(SimpleGL
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
# )


# target_link_libraries(SimpleGL
#     ${OPENGL_LIBRARIES}
#     ${GLFW_x11_LIBRARY}
#     ${GLFW_LIBRARIES}
#     ${ASSIMP_LIBRARIES}
# )

# target_compile_definitions(SimpleGL
#     PRIVATE
#         fexceptions
#         Wall
#         Wextra
# )



# ------------------------------------------------------------------------------
# Create a static and shared library target.
# ------------------------------------------------------------------------------
# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
set (LIB_TYPE STATIC)  # Set the LIB_TYPE variable to STATIC
set (MY_LIB_NAME SimpleGL_Static)
if (BUILD_SHARED_LIBS)
    set (LIB_TYPE SHARED)  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
    set (MY_LIB_NAME SimpleGL_Shared)
endif (BUILD_SHARED_LIBS)
message("*** Library will be build as: ${LIB_TYPE}")


file(
    GLOB
    library_SOURCES
    src/Interface/*
    src/Components/*
    src/Services/*
    src/OpenGL/*
    src/OpenGL/2D/*
    src/OpenGL/3D/*
    src/Utility/*
    src/*
    ${PROJECT_SOURCE_DIR}/extern/GLAD/src/*   #[[ From GLAD (http://glad.dav1d.de/) ]]
    ${PROJECT_SOURCE_DIR}/extern/STB/src/*    #[[ From stb_image (https://github.com/nothings/stb) ]]
)

add_library(${MY_LIB_NAME} ${LIB_TYPE} ${library_SOURCES})


# See https://cmake.org/pipermail/cmake/2016-May/063400.html
if (BUILD_SHARED_LIBS)
    # Shared library
    target_include_directories(${MY_LIB_NAME}
        PRIVATE BEFORE ${PROJECT_SOURCE_DIR}/include
        PRIVATE
            ${GLFW_INCLUDE_DIRS}
            ${ASSIMP_INCLUDE_DIRS}
            ${PROJECT_SOURCE_DIR}/extern/KHR
            ${PROJECT_SOURCE_DIR}/extern/GLAD/include
            ${PROJECT_SOURCE_DIR}/extern/STB/include
            ${PROJECT_SOURCE_DIR}/extern/GLM           #[[ https://glm.g-truc.net/0.9.8/index.html ]]
    )

    # Set pre processor command for Shared lib export
    target_compile_definitions(${MY_LIB_NAME}
    PRIVATE
        SIMPLEGL_SHARED="USED"
        SIMPLEGL_SHARED_EXPORTS="USED"
    )


else()
    # Static library
    target_include_directories(${MY_LIB_NAME}
        PUBLIC BEFORE ${PROJECT_SOURCE_DIR}/include
        PUBLIC
            ${GLFW_INCLUDE_DIRS}
            ${ASSIMP_INCLUDE_DIRS}
            ${PROJECT_SOURCE_DIR}/extern/KHR
            ${PROJECT_SOURCE_DIR}/extern/GLAD/include
            ${PROJECT_SOURCE_DIR}/extern/STB/include
            ${PROJECT_SOURCE_DIR}/extern/GLM
    )
endif()

set_target_properties(${MY_LIB_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${MY_LIB_NAME}
    ${OPENGL_LIBRARIES}
    ${GLFW_x11_LIBRARY}
    ${GLFW_LIBRARIES}
    ${ASSIMP_LIBRARIES}
)

# Read only alias
add_library(OpenGL::lib ALIAS ${MY_LIB_NAME})


# ------------------------------------------------------------------------------
# Link library to another binary (for example lib == engine and exe == game)
# A better idea will be to create another CMakeLists.txt in the Game folder
# but a new Sublime project will have to be created ...
# ------------------------------------------------------------------------------

file(
    GLOB
    game_binary_SOURCES
    ${PROJECT_SOURCE_DIR}/samples/Game/src/*
)

add_executable(
    OpenGl-Game ${game_binary_SOURCES}
)

# See https://cmake.org/pipermail/cmake/2016-May/063400.html
if (BUILD_SHARED_LIBS)
    # Shared lib need to know includes directories
    message("*** Using shared library: GLFW, GLAD, stb_image, and SimpleGl headers will be included.")
    target_include_directories(OpenGl-Game
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
            ${GLFW_INCLUDE_DIRS}
            ${ASSIMP_INCLUDE_DIRS}
            ${PROJECT_SOURCE_DIR}/extern/KHR
            ${PROJECT_SOURCE_DIR}/extern/GLAD/include
            ${PROJECT_SOURCE_DIR}/extern/STB/include
            ${PROJECT_SOURCE_DIR}/extern/GLM
            ${PROJECT_SOURCE_DIR}/samples/Game/include
    )

    # Set pre processor command for Shared lib import
    target_compile_definitions(OpenGl-Game
    PRIVATE
        SIMPLEGL_SHARED="USED"
    )
else()
    target_include_directories(OpenGl-Game
        PRIVATE
            ${PROJECT_SOURCE_DIR}/samples/Game/include
    )
endif()


set_target_properties(OpenGl-Game
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/samples/Game/bin/${CMAKE_BUILD_TYPE}"
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Using dynamic or static lib based on previous flag (see ${MY_LIB_NAME})
target_link_libraries(OpenGl-Game
    PRIVATE OpenGL::lib
)


# # Get all flags
# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
