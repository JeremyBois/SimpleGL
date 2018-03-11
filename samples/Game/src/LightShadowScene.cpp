#include "LightShadowScene.hpp"
#include "StartingScene.hpp"

#include "math.h"
#include "glm.hpp"

// #include "gtx/string_cast.hpp" // For debug

namespace GL = simpleGL;
typedef GL::GameManager Game;


double LightShadowScene::s_lastX = 0.0f;
double LightShadowScene::s_lastY = 0.0f;

LightShadowScene::LightShadowScene()
{
    m_pCuboid = new GL::Cuboid();
    m_lightShape = new GL::Cuboid();
}

LightShadowScene::~LightShadowScene()
{

}


bool LightShadowScene::OnInit()
{
    auto* container = new GL::NodeManager();
    GL::GameManager::AttachNodeMgr(container);

    // Create a field of boxes
    m_pCuboid->Create(0.5f, 0.5f, 0.5f);
    m_lightShape->Create(0.1f, 0.1f, 0.1f);

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
    // Add cube color
    cubeMat->SetDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
    cubeMat->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

    // Add camera
    m_pNodes[10] = container->CreateNode();
    m_pCam = m_pNodes[10]->AddComponent<GL::CameraDebug>();
    m_pNodes[10]->GetTransform().SetPosition(glm::vec3(-2.0f, 1.0f, 5.0f));
    m_pCam->LookAt(glm::vec3(0.0f, 0.0f, -3.0f));


    // Add light
    m_pNodes[11] = container->CreateNode();
    m_pNodes[11]->GetTransform().SetPosition(glm::vec3(-2.0f, 1.0f, 2.0f));
    m_pLight = m_pNodes[11]->AddComponent<GL::Light>();
    temp = m_pNodes[11]->AddComponent<GL::ShapeRenderer>();
    temp->LinkShape(m_lightShape);
    temp->LinkMaterial(Game::GetDataMgr().GetMaterial("LightGizmo"));

    // Apply light to cubeMat
    m_pLight->Use(cubeMat->GetShader());


    // Add callback for key events
    Game::GetWindow().AttachKeyEventCallback(MyKeyEventHandler);

    // Add callback for Mouse position
    Game::GetWindow().AttachMousePosEventCallback(MyMousePosEventHandler);
    Game::GetWindow().SetCursorPos(LightShadowScene::s_lastX, LightShadowScene::s_lastY);

    // Add callback for Mouse Scroll
    Game::GetWindow().AttachScrollEventCallback(MyScrollEventHandler);
}

bool LightShadowScene::OnUpdate()
{
    GL::Material* cubeMat = Game::GetDataMgr().GetMaterial("BoxLight");

    // Call to update camera position for light calculation
    m_pCam->Use(&cubeMat->GetShader());

    // Change light color with time
    glm::vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f * 0.5f);
    lightColor.y = sin(glfwGetTime() * 0.7f * 0.5f);
    lightColor.z = sin(glfwGetTime() * 1.3f * 0.5f);
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.7f); // decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.3f); // low influence
    m_pLight->SetDiffuse(diffuseColor);
    m_pLight->SetAmbient(ambientColor);
    m_pLight->Use(cubeMat->GetShader());
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

}

void LightShadowScene::MyMousePosEventHandler(GLFWwindow* _window, double _xpos, double _ypos)
{
    float xoffset = s_lastX - _xpos;
    float yoffset = s_lastY - _ypos;  // Reversed since y-coordinates go from bottom to top
    s_lastX = _xpos;
    s_lastY = _ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Update main camera
    Game::GetWindow().mainCam->Yaw(xoffset);
    Game::GetWindow().mainCam->Pitch(yoffset);
}

void LightShadowScene::MyScrollEventHandler(GLFWwindow* _window, double _xoffset, double _yoffset)
{
    GL::Camera* mainCam = Game::GetWindow().mainCam;
    mainCam->SetFov(mainCam->GetFov() - _yoffset);
}

void LightShadowScene::ProcessInput()
{
    GL::Window window = Game::GetWindow();
    GL::Camera* mainCam = Game::GetWindow().mainCam;

    float cameraSpeed = 2.5 * Game::GetWindow().GetDeltaTime();

    if (window.GetKey(GLFW_KEY_1) == GLFW_PRESS)
    {
        Game::GetSceneMgr().Change(new StartingScene());
        return;
    }

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
        mainCam->Strafe(-cameraSpeed);
    }
    if (window.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mainCam->Strafe(cameraSpeed);
    }
}
