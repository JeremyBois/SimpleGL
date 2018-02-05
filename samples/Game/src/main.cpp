#include "simpleGL.hpp"
namespace sGL = simpleGL;

#include <string>
#include <iostream>

using std::cout;
using std::endl;

typedef sGL::GameManager Game;

int main(void)
{
    // Test implementation of Game Manager / Window
    Game::Init(800, 600, "My OpenGl window");
    sGL::NodeManager* nodeManager = new sGL::NodeManager();
    Game::Provide(nodeManager);

    // // Test implementation of shaders (OpenGl must be init first)
    // sGL::Shader myShader = sGL::Shader("../shaders/basic.vert",
    //                                    "../shaders/colorFromProgram.frag");

    sGL::Node* myNode = new sGL::Node();

    // Create a triangle
    sGL::Triangle* myTriangle = new sGL::Triangle();
    myTriangle->Create();
    // myTriangle->SetShader(&myShader);

    // Populate container
    myNode->AddGameObject(myTriangle);
    Game::GetNodeMgr().AddNode(myNode);

    Game::GetWindow().Update();
    Game::GetWindow().Quit();


    delete nodeManager;

    return 0;
}
