#include "StartingScene.hpp"

#include "math.h"
#include "glm.hpp"

namespace GL = simpleGL;
typedef GL::GameManager Game;



StartingScene::StartingScene()
{
    m_pNodes[0] =  new GL::Node();
    m_pNodes[1] =  new GL::Node();
    m_pNodes[2] =  new GL::Node();
    m_pNodes[2]->GetTransform().SetYawPitchRollAngles(glm::vec3(-55.0f, 0.0f, 0.0f));

    m_pNodes[3] =  new GL::Node();
    m_pNodes[3]->GetTransform().SetPosition(glm::vec3(-2.0f, 0.0f, -2.0f));
    m_pNodes[3]->GetTransform().SetScale(glm::vec3(1.0f, 1.0f, 3.0f));

    // Create shaders
    m_basicShader = GL::Shader("shaders/basic.vert",
                               "shaders/basic.frag");

    m_colorShader =  GL::Shader("shaders/basic.vert",
                                      "shaders/colorFromProgram.frag");
    float color[] = {0.0f, 1.0f, 0.0f, 1.0f};
    m_colorShader.Use();
    m_colorShader.SetFloat4("ourColor", color);

    m_uvShader =  GL::Shader("shaders/basic.vert",
                                   "shaders/UVscale.frag");
    m_uvShader.Use();
    m_uvShader.SetFloat("uvScale", 1.0f);
    m_uvShader.SetInt("tex0", 0);
    m_uvShader.SetInt("tex1", 1);

    m_colorVertexShader = GL::Shader("shaders/positionColor.vert",
                                           "shaders/colorFromVertex.frag");

    // Create textures
    m_textureWall.Load("data/images/wall.jpg");
    m_textureContainer.Load("data/images/container.jpg", false, true);
    m_textureSmile.Load("data/images/awesomeface.png", true, true);


    // Create shapes
    m_pTriangles[0] = new GL::Triangle();
    m_pTriangles[1] = new GL::Triangle();
    m_pQuad = new GL::Quad();
    m_pCuboid = new GL::Cuboid();


    // Create materials
    m_pBasicMat = new GL::Material();
    m_pBasicMat->LinkShader(&m_basicShader);
    m_pBasicMat->LinkTexture(&m_textureWall);

    m_pColorMat = new GL::Material();
    m_pColorMat->LinkShader(&m_colorShader);

    m_pUVMat = new GL::Material();
    m_pUVMat->LinkShader(&m_uvShader);
    m_pUVMat->LinkTexture(&m_textureContainer, GL_TEXTURE0);
    m_pUVMat->LinkTexture(&m_textureSmile, GL_TEXTURE1);

    m_pVertexMat = new GL::Material();
    m_pVertexMat->LinkShader(&m_colorVertexShader);
}

StartingScene::~StartingScene()
{

}


void StartingScene::ChangeGreenOverTime(GL::Shader& _shader)
{
    float color[] = {0.0f, 1.0f, 0.0f, 1.0f};

    float timeValue = glfwGetTime();
    color[1] =  (std::sin(timeValue) / 2.0f) + 0.5f;
    _shader.Use();
    _shader.SetFloat4("ourColor", color);
}


void StartingScene::ZoomUVOverTime(GL::Shader& _shader)
{
    float timeValue = glfwGetTime();
    float scale = 5.0f * (std::sin(timeValue * 0.25f) / 2.0f + 0.5f);
    _shader.Use();
    _shader.SetFloat("uvScale", scale);
}


void StartingScene::ZoomUV(GL::Shader& _shader, bool _zoom)
{
    m_zoomScale += _zoom ? 0.1f : -0.1f;
    if (m_zoomScale < 0)
    {
        m_zoomScale = 0.0f;
    }
    _shader.Use();
    _shader.SetFloat("uvScale", m_zoomScale);
}


bool StartingScene::OnInit()
{
    // Steal ownership
    GL::GameManager::AttachNodeMgr(&m_container);

    glm::vec3 pos1[]
    {
        {0.4f,  0.8f, 0.0f},
        {0.4f, 0.4f, 0.0f},
        {0.8f, 0.4f, 0.0f}
    };

    glm::vec3 pos2[]
    {
        {-0.8f,  -0.4f, 0.0f},
        {-0.8f, -0.8f, 0.0f},
        {-0.4f, -0.8f, 0.0f}
    };

    glm::vec4 color1[]
    {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f}
    };

    m_pTriangles[0]->Create(pos1, color1);
    m_pTriangles[1]->Create(pos2);


    // Add quad
    m_pQuad->Create(0.8f, 1.2f);

    // Add Cuboid
    m_pCuboid->Create(0.5f, 0.5f, 0.5f);


    // Populate container
    m_container.AddNode(m_pNodes[0]);
    m_container.AddNode(m_pNodes[1]);
    m_container.AddNode(m_pNodes[2]);
    m_container.AddNode(m_pNodes[3]);


    GL::ShapeRenderer* temp;
    temp = m_pNodes[0]->AddComponent<GL::ShapeRenderer>();
    temp->LinkShape(m_pTriangles[0]);
    temp->LinkMaterial(m_pBasicMat);

    temp = m_pNodes[1]->AddComponent<GL::ShapeRenderer>();
    temp->LinkShape(m_pTriangles[1]);
    temp->LinkMaterial(m_pColorMat);

    temp = m_pNodes[2]->AddComponent<GL::ShapeRenderer>();
    temp->LinkShape(m_pQuad);
    temp->LinkMaterial(m_pUVMat);

    temp = m_pNodes[3]->AddComponent<GL::ShapeRenderer>();
    temp->LinkShape(m_pCuboid);
    temp->LinkMaterial(m_pVertexMat);


    // Add callback for key events
    Game::GetWindow().AttachKeyEventCallback(MyKeyEventHandler);

}

bool StartingScene::OnUpdate()
{
    ChangeGreenOverTime(m_colorShader);
    if (Game::GetWindow().GetKey(GLFW_KEY_PAGE_UP) == GLFW_PRESS)
    {
        ZoomUV(m_uvShader, true);
    }
    else if (Game::GetWindow().GetKey(GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
    {
        ZoomUV(m_uvShader, false);
    }

    // Rotate
    float rotation = 360 * (std::cos(glfwGetTime() * 0.5f) * 0.5f + 0.5f);
    m_pNodes[0]->GetTransform().SetRotationZ(rotation);
}

bool StartingScene::OnQuit()
{
    // Detach obsolete services
    GL::GameManager::DetachNodeMgr();

    // Remove event callback
    Game::GetWindow().DetachKeyEventCallback();

    return true;
}

void StartingScene::OnRender()
{

}

// @TODO Replace with set
void StartingScene::MyKeyEventHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    // Change wrap mode
    if (_key == GLFW_KEY_W && _action == GLFW_PRESS)
    {
        // Set texture to affect
        // Get ref to active Scene
        StartingScene* myScene = (StartingScene*)Game::GetSceneMgr().GetCurrent();
        GL::Texture myTexture = myScene->m_textureContainer;

        // Get current wrap mode
        GLint result[1];
        myTexture.Get(GL_TEXTURE_WRAP_S, result);

        switch (result[0])
        {
            case GL_REPEAT:
                myTexture.Set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                myTexture.Set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                cout << "Wrap mode is now: " << "CLAMP TO EDGE" << endl;
                break;
            case GL_CLAMP_TO_EDGE:
                myTexture.Set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                myTexture.Set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                cout << "Wrap mode is now: " << "CLAMP TO BORDER" << endl;
                break;
            case GL_CLAMP_TO_BORDER:
                myTexture.Set(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                myTexture.Set(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
                cout << "Wrap mode is now: " << "MIRRORED REPEAT" << endl;
                break;
            case GL_MIRRORED_REPEAT:
                myTexture.Set(GL_TEXTURE_WRAP_S, GL_REPEAT);
                myTexture.Set(GL_TEXTURE_WRAP_T, GL_REPEAT);
                cout << "Wrap mode is now: " << "REPEAT" << endl;
                break;
        }
    }

    // Change filtering mode
    else if (_key == GLFW_KEY_F && _action == GLFW_PRESS)
    {
        // Set texture to affect
        // Get ref to active Scene
        StartingScene* myScene = (StartingScene*)Game::GetSceneMgr().GetCurrent();
        GL::Texture myTexture = myScene->m_textureContainer;

        // Get current wrap mode
        GLint result[1];
        myTexture.Get(GL_TEXTURE_MIN_FILTER, result);

        switch (result[0])
        {
            case GL_NEAREST:
                myTexture.Set(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                myTexture.Set(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                cout << "Filtering mode is now: " << "LINEAR" << endl;
                break;
            case GL_LINEAR:
                myTexture.Set(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                myTexture.Set(GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                cout << "Filtering mode is now: " << "NEAREST + MIPMAP NEAREST" << endl;
                break;
            case GL_NEAREST_MIPMAP_NEAREST:
                myTexture.Set(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                myTexture.Set(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                cout << "Filtering mode is now: " << "LINEAR + MIPMAP NEAREST" << endl;
                break;
            case GL_LINEAR_MIPMAP_NEAREST:
                myTexture.Set(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                myTexture.Set(GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                cout << "Filtering mode is now: " << "NEAREST + MIPMAP LINEAR" << endl;
                break;
            case GL_NEAREST_MIPMAP_LINEAR:
                myTexture.Set(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                myTexture.Set(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                cout << "Filtering mode is now: " << "LINEAR + MIPMAP LINEAR" << endl;
                break;
            case GL_LINEAR_MIPMAP_LINEAR:
                myTexture.Set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                myTexture.Set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                cout << "Filtering mode is now: " << "NEAREST" << endl;
                break;
        }
    }
}

