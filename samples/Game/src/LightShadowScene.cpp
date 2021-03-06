#include "LightShadowScene.hpp"
#include "StartingScene.hpp"

#include "math.h"
#include "glm.hpp"

#include "gtx/string_cast.hpp" // For debug

namespace GL = simpleGL;
typedef GL::GameManager Game;


double LightShadowScene::s_lastX = 0.0f;
double LightShadowScene::s_lastY = 0.0f;

LightShadowScene::LightShadowScene()
{
    m_pCuboid = new GL::Cuboid();
    m_lightShape = new GL::Cuboid();
    m_pPlane = new GL::Plane();

    // Create shapes
    m_pCuboid->Create(0.5f, 0.5f, 0.5f);
    m_lightShape->Create(0.1f, 0.1f, 0.1f);
    m_pPlane->Create(40.0f, 80.0f, 8, 16, 2.0f);
    m_pPlane->SetUnclampedUV();
}

LightShadowScene::~LightShadowScene()
{

}


bool LightShadowScene::OnInit()
{
    auto* container = new GL::NodeManager();
    GL::GameManager::AttachNodeMgr(container);

    GL::Material* cubeMat = Game::GetDataMgr().GetMaterial("BoxLight");

    glm::vec3 m_cubePositions[] =
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    GL::ShapeRenderer* temp;
    for (int i = 0; i < 10; ++i)
    {
        m_pNodes[i] = container->CreateNode();
        m_pNodes[i]->GetTransform().SetPosition(m_cubePositions[i]);
        m_pNodes[i]->GetTransform().SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
        float angle = 20.0f * i;
        m_pNodes[i]->GetTransform().SetRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));

        temp = m_pNodes[i]->AddComponent<GL::ShapeRenderer>();
        temp->LinkShape(m_pCuboid);
        temp->LinkMaterial(cubeMat);
    }
    // Set cube color
    cubeMat->SetAmbiant(glm::vec3(0.2f, 0.2f, 0.2f));
    cubeMat->SetDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
    cubeMat->SetShininess(64.0f);
    cubeMat->SetGlossiness(5.0f);

    // Add camera
    m_pNodes[10] = container->CreateNode();
    m_pCam = m_pNodes[10]->AddComponent<GL::CameraFPS>();
    m_pNodes[10]->GetTransform().SetPosition(glm::vec3(-2.0f, 1.0f, 5.0f));
    m_pCam->LookAt(glm::vec3(0.0f, 0.0f, -3.0f));

    // Add Spot light attached to the camera
    m_pSpotLight = m_pNodes[10]->AddComponent<GL::SpotLight>();

    // Add directional Light
    m_pNodes[11] = container->CreateNode();
    m_pNodes[11]->GetTransform().SetPosition(glm::vec3(0.5f, 1.0f, 5.5f));
    m_pDirLight = m_pNodes[11]->AddComponent<GL::DirectionalLight>();
    temp = m_pNodes[11]->AddComponent<GL::ShapeRenderer>();
    temp->LinkShape(m_lightShape);
    temp->LinkMaterial(Game::GetDataMgr().GetMaterial("LightGizmo"));

    // Add Point light
    m_pNodes[12] = container->CreateNode();
    m_pNodes[12]->GetTransform().SetPosition(glm::vec3(-2.0f, -0.5f, -1.5f));
    m_pPointLight = m_pNodes[12]->AddComponent<GL::PointLight>();
    temp = m_pNodes[12]->AddComponent<GL::ShapeRenderer>();
    temp->LinkShape(m_lightShape);
    temp->LinkMaterial(Game::GetDataMgr().GetMaterial("LightGizmo"));

    // Add floor
    m_pNodes[13] = container->CreateNode();
    m_pNodes[13]->GetTransform().SetPosition(glm::vec3(2.0f, -5.0f, -6.0f));
    temp = m_pNodes[13]->AddComponent<GL::ShapeRenderer>();
    temp->LinkShape(m_pPlane);
    temp->LinkMaterial(Game::GetDataMgr().GetMaterial("Floor"));

    // Add callback for key events
    Game::GetWindow().AttachKeyEventCallback(MyKeyEventHandler);

    // Add callback for Mouse position
    Game::GetWindow().AttachMousePosEventCallback(MyMousePosEventHandler);
    Game::GetWindow().SetCursorPos(LightShadowScene::s_lastX, LightShadowScene::s_lastY);

    // Add callback for Mouse Scroll
    Game::GetWindow().AttachScrollEventCallback(MyScrollEventHandler);

    return true;
}

bool LightShadowScene::OnUpdate()
{
    GL::Material* cubeMat = Game::GetDataMgr().GetMaterial("BoxLight");

    // Change light color with time
    glm::vec3 lightColor;
    lightColor.x = (float)sin(glfwGetTime() * 2.0) / 2.0f + 0.5f;
    lightColor.y = (float)sin(glfwGetTime() * 0.7) / 2.0f + 0.5f;
    lightColor.z = (float)sin(glfwGetTime() * 1.3) / 2.0f + 0.5f;
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.7f); // decrease the influence
    m_pDirLight->SetColor(diffuseColor);

    return true;
}

bool LightShadowScene::OnQuit()
{
    // Detach obsolete services
    GL::GameManager::DetachNodeMgr();

    return true;
}

void LightShadowScene::OnRender()
{

}

// @TODO Replace with set
void LightShadowScene::MyKeyEventHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    if (_key == GLFW_KEY_1 && _action == GLFW_PRESS)
    {
        Game::GetSceneMgr().Change(new StartingScene());
        return;
    }
}

void LightShadowScene::MyMousePosEventHandler(GLFWwindow* _window, double _xpos, double _ypos)
{
    float xoffset = (float)(s_lastX - _xpos);
    float yoffset = (float)(s_lastY - _ypos);  // Reversed since y-coordinates go from bottom to top
    s_lastX = _xpos;
    s_lastY = _ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Update main camera
    Game::GetWindow().mainCam->Yaw(-xoffset);
    Game::GetWindow().mainCam->Pitch(-yoffset);
}

void LightShadowScene::MyScrollEventHandler(GLFWwindow* _window, double _xoffset, double _yoffset)
{
    GL::Camera* mainCam = Game::GetWindow().mainCam;
    mainCam->SetFov(mainCam->GetFov() - (float)_yoffset);
}

void LightShadowScene::ProcessInput()
{
    GL::Window window = Game::GetWindow();
    GL::Camera* mainCam = Game::GetWindow().mainCam;

    float cameraSpeed = (float)(2.5 * Game::GetWindow().GetDeltaTime());

    if (window.GetKey(GLFW_KEY_UP) == GLFW_PRESS)
    {
        mainCam->Walk(cameraSpeed);
    }
    if (window.GetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mainCam->Walk(-cameraSpeed);
    }
    if (window.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        mainCam->Strafe(cameraSpeed);
    }
    if (window.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mainCam->Strafe(-cameraSpeed);
    }
}
