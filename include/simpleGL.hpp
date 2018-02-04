#ifndef __SIMPLEGL__HPP
#define __SIMPLEGL__HPP

// SimpleGL PUBLIC API
#include "GameManager.hpp"
#include "Node.hpp"
#include "NodeManager.hpp"


// SimpleGL PUBLIC API for OpenGl specific
#include "OpenGL/Triangle.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Window.hpp"


// SimpleGL PRIVATE API (SIMPLEGL_SHARED set when build as a shared lib)
#include "Utility/StreamUtility.hpp"
#include "Shape.hpp"
#include "Shape2D.hpp"

#endif
