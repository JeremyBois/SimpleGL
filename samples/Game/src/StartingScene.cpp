#include "StartingScene.hpp"

#include "math.h"


using POS3 = simpleGL::GL_POS3;
using COLOR3 = simpleGL::GL_COLOR3;


StartingScene::StartingScene()
{
    m_pContainer =  new simpleGL::NodeManager();
    m_pFirstNode =  new simpleGL::Node();

    // Compile shader
    m_colorShader =  simpleGL::Shader("../shaders/basic.vert",
                                      "../shaders/colorFromProgram.frag");

    // Get a texture
    m_textureWall.Load("../data/images/wall.jpg");
    // m_textureWall.Load("../data/images/container.jpg");

}

StartingScene::~StartingScene()
{

}


void StartingScene::ChangeGreenOverTime(simpleGL::Shader& _shader)
{
    float color[] = {0.0f, 1.0f, 0.0f, 1.0f};

    float timeValue = glfwGetTime();
    color[1] =  (std::sin(timeValue) / 2.0f) + 0.5f;
    _shader.Use();
    _shader.SetFloat4("ourColor", color);
}



bool StartingScene::OnInit()
{
    simpleGL::GameManager::Provide(m_pContainer);

    // Create a triangle
    m_pTriangles[0] = new simpleGL::Triangle();
    m_pTriangles[1] = new simpleGL::Triangle();

    POS3 pos1[]
    {
        {0.4f, 0.4f, 0.0f},
        {0.4f,  0.8f, 0.0f},
        {0.8f, 0.4f, 0.0f}
    };

    POS3 pos2[]
    {
        {-0.8f, -0.8f, 0.0f},
        {-0.8f,  -0.4f, 0.0f},
        {-0.4f, -0.8f, 0.0f},
    };

    COLOR3 color1[]
    {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
    };

    m_pTriangles[0]->Create(pos1, color1);
    m_pTriangles[0]->LinkTexture(&m_textureWall);

    m_pTriangles[1]->Create(pos2);
    m_pTriangles[1]->LinkShader(&m_colorShader);

    // Populate container
    m_pFirstNode->AddGameObject(m_pTriangles[0]);
    m_pFirstNode->AddGameObject(m_pTriangles[1]);
    m_pContainer->AddNode(m_pFirstNode);
}

bool StartingScene::OnUpdate()
{
    ChangeGreenOverTime(m_colorShader);
}

bool StartingScene::OnQuit()
{
    // Game Manager reset service to null if
    delete m_pContainer;
    m_pContainer = nullptr;
    delete m_pFirstNode;
    return true;
}

void StartingScene::OnRender()
{

}

