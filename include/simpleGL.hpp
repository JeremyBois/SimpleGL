#ifndef __SIMPLEGL__HPP
#define __SIMPLEGL__HPP

// Managers
#include "GameManager.hpp"
#include "Services/NodeManager.hpp"
#include "Services/SceneManager.hpp"


// Interface prototype
#include "Interface/IScene.hpp"


// Components
#include "Node.hpp"
// Renderers
#include "Components/ShapeRenderer.hpp"
// Cameras
#include "Components/CameraDebug.hpp"
#include "Components/CameraFPS.hpp"
// Lights
#include "Components/Light.hpp"
#include "Components/DirectionalLight.hpp"
#include "Components/PointLight.hpp"
#include "Components/SpotLight.hpp"


// OpenGL resources
// Shapes 2D
#include "OpenGL/2D/Triangle.hpp"
#include "OpenGL/2D/Quad.hpp"
// Shapes 3D
#include "OpenGL/3D/Cuboid.hpp"
#include "OpenGL/3D/Plane.hpp"
// Models
#include "OpenGL/Mesh.hpp"
#include "OpenGL/Model.hpp"
// Assets
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "OpenGL/Material.hpp"


#endif
