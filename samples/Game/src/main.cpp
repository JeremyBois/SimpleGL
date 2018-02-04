#include "simpleGL.hpp"
namespace sGL = simpleGL;

#include <string>
#include <iostream>

using std::cout;
using std::endl;



int main(void)
{
    // Test implementation of Game Manager / Window / NodeManager
    sGL::GameManager* GameM = sGL::GameManager::Instance();
    GameM->Init(800, 600, "My OpenGl window.");

    // Test implementation of shaders (OpenGl must be init first)
    sGL::Shader myShader = sGL::Shader("../Shaders/basic.vert",
                                       "../Shaders/colorFromProgram.frag");


    GameM->GetWindow().Update();
    GameM->GetWindow().Quit();

    return 0;
}
