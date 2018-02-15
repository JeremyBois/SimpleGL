#ifndef __SIMPLEGL__HPP
#define __SIMPLEGL__HPP

// PUBLIC API

// Managers
#include "GameManager.hpp"
#include "NodeManager.hpp"
#include "SceneFSM.hpp"

// Base
#include "Node.hpp"
#include "Components/ShapeRenderer.hpp"

// Interface prototype
#include "Interface/IScene.hpp"



// SimpleGL PUBLIC API for OpenGl specific
// 2D
#include "OpenGL/2D/Triangle.hpp"
#include "OpenGL/2D/Quad.hpp"

// 3D
#include "OpenGL/3D/Cuboid.hpp"

// Others
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "OpenGL/Material.hpp"


#endif
