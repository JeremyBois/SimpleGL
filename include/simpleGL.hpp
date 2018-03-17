#ifndef __SIMPLEGL__HPP
#define __SIMPLEGL__HPP

// Managers
#include "GameManager.hpp"
#include "Services/NodeManager.hpp"
#include "Services/SceneManager.hpp"


// Components
#include "Node.hpp"
// Renderers
#include "Components/ShapeRenderer.hpp"
// Cameras
#include "Components/CameraDebug.hpp"
// Lights
#include "Components/Light.hpp"
#include "Components/DirectionalLight.hpp"
#include "Components/PointLight.hpp"
#include "Components/SpotLight.hpp"


// Interface prototype
#include "Interface/IScene.hpp"


// OpenGL resources
// Shapes
#include "OpenGL/2D/Triangle.hpp"
#include "OpenGL/2D/Quad.hpp"
#include "OpenGL/3D/Cuboid.hpp"
#include "OpenGL/3D/Plane.hpp"

// Assets
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "OpenGL/Material.hpp"


#endif
