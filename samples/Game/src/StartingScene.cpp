#include "StartingScene.hpp"

#include "math.h"

StartingScene::StartingScene()
{
    m_pContainer =  new simpleGL::NodeManager();
    m_pFirstNode =  new simpleGL::Node();

    // Test implementation of shaders (OpenGl must be init first)
    m_pColorShader =  simpleGL::Shader("../shaders/basic.vert",
                                          "../shaders/colorFromProgram.frag");

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

    float pos1[] =
    {
        // Position
        0.4f, 0.4f, 0.0f,
        0.4f,  0.8f, 0.0f,
        0.8f, 0.4f, 0.0f
    };

    float pos2[] =
    {
        -0.8f, -0.8f, 0.0f,
        -0.8f,  -0.4f, 0.0f,
        -0.4f, -0.8f, 0.0f
    };

    float color1[] =
    {
        // Color
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    m_pTriangles[0]->Create(pos1, color1);
    m_pTriangles[1]->Create(pos2);
    m_pTriangles[1]->SetShader(&m_pColorShader);

    // Populate container
    m_pFirstNode->AddGameObject(m_pTriangles[0]);
    m_pFirstNode->AddGameObject(m_pTriangles[1]);
    m_pContainer->AddNode(m_pFirstNode);
}

bool StartingScene::OnUpdate()
{
    ChangeGreenOverTime(m_pColorShader);
}

bool StartingScene::OnQuit()
{
    // Game Manager reset to null if none exist
    // delete m_pContainer;
    delete m_pFirstNode;
    return true;
}

void StartingScene::OnRender()
{

}

