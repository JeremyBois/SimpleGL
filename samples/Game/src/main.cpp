#include "simpleGL.hpp"
namespace sGL = simpleGL;

#include <string>
#include <iostream>
#include "math.h"

using std::cout;
using std::endl;


typedef sGL::GameManager Game;

void ChangeGreenOverTime(sGL::Shader& _shader);


int main(void)
{
    // Test implementation of Game Manager / Window
    Game::Init(800, 600, "My OpenGl window");
    sGL::NodeManager* nodeManager = new sGL::NodeManager();
    Game::Provide(nodeManager);

    // Test implementation of shaders (OpenGl must be init first)
    sGL::Shader colorFromProgram = sGL::Shader("../shaders/basic.vert",
                                               "../shaders/colorFromProgram.frag");

    sGL::Node* myNode = new sGL::Node();

    // Create a triangle
    sGL::Triangle* topRightTriangle = new sGL::Triangle();
    sGL::Triangle* bottomLeftTriangle = new sGL::Triangle();
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

    topRightTriangle->Create(pos1, color1);
    bottomLeftTriangle->Create(pos2);
    bottomLeftTriangle->SetShader(&colorFromProgram);
    ChangeGreenOverTime(colorFromProgram);

    // Populate container
    myNode->AddGameObject(topRightTriangle);
    myNode->AddGameObject(bottomLeftTriangle);
    Game::GetNodeMgr().AddNode(myNode);


    // Start loop
    Game::GetWindow().Update();
    Game::GetWindow().Quit();


    delete nodeManager;

    return 0;
}


// Cannot work because we can enter the window loop
// @TODO FSM for scenes
void ChangeGreenOverTime(sGL::Shader& _shader)
{
    float color[] = {0.0f, 1.0f, 0.0f, 1.0f};

    float timeValue = glfwGetTime();
    color[1] =  (std::sin(timeValue) / 2.0f) + 0.5f;
    _shader.Use();
    _shader.SetFloat4("ourColor", color);
}
