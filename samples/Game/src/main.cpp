#include "simpleGL.hpp"
#include "StartingScene.hpp"
#include "LightShadowScene.hpp"

// Handle Windows and Linux environments
#ifdef __unix__
    #include <unistd.h>
    #define __delimiter "/"
#else
    #include <direct.h>
    #define getcwd _getcwd
    #define chdir _chdir
    #define __delimiter "\\"
#endif


void ChangeWorkingDirectory(const std::string& _path, const std::string& _toAdd);
void LoadData();


namespace GL = simpleGL;
typedef GL::GameManager Game;


int main(int argc, char** argv)
{
    ChangeWorkingDirectory(__FILE__, "../../../");

    // Test implementation of Game Manager / Window
    Game::Init(1200, 800, "My OpenGl window");

    LoadData();

    // Create a simple SceneManager with a starting scene
    // StartingScene* firstScene = new StartingScene();
    LightShadowScene* firstScene = new LightShadowScene();
    simpleGL::SceneManager* mySceneManager = new simpleGL::SceneManager(*firstScene);
    simpleGL::GameManager::AttachSceneMgr(mySceneManager);

    // Start loop
    Game::Start();


    return 0;
}



void ChangeWorkingDirectory(const std::string& _path, const std::string& _toAdd)
{
    // Change directory based on binary path
    std::string workingDir = _path.substr(0, _path.find_last_of(__delimiter) + 1);
    workingDir += _toAdd;
    chdir(workingDir.c_str());

    // // For debug purpose
    // char cwd[1024];
    // getcwd(cwd, sizeof(cwd));
    // cout << "Current working directory: " << cwd << endl;
}


void LoadData()
{
    // Load textures
    Game::GetDataMgr().CreateTexture("Wall", "data/images/wall.jpg", false, true);
    Game::GetDataMgr().CreateTexture("Container", "data/images/container.jpg", true, true);
    Game::GetDataMgr().CreateTexture("Awesomeface", "data/images/awesomeface.png", true, true);
    Game::GetDataMgr().CreateTexture("ContainerDiffuseMap", "data/images/container2_diffuse.png", true, true);
    Game::GetDataMgr().CreateTexture("ContainerSpecularMap", "data/images/container2_specular.png", true, true);
    Game::GetDataMgr().CreateTexture("ContainerEmissionMap", "data/images/container2_emission.jpg", true, true);


    // Load shaders
    GL::Shader* shaderPtr;

    shaderPtr = Game::GetDataMgr().CreateShader("ColorFromProgram",
                                    "shaders/basic.vert", "shaders/colorFromProgram.frag");
    float color[] = {0.0f, 1.0f, 0.0f, 1.0f};

    shaderPtr->Use();
    shaderPtr->SetFloat4("ourColor", color);

    shaderPtr = Game::GetDataMgr().CreateShader("UVscale",
                                                "shaders/basic.vert", "shaders/UVscale.frag");
    shaderPtr->Use();
    shaderPtr->SetFloat("uvScale", 1.0f);
    shaderPtr->SetInt("tex0", 3);
    shaderPtr->SetInt("tex1", 4);

    shaderPtr = Game::GetDataMgr().CreateShader("ColorFromVertex",
                                                "shaders/positionColor.vert", "shaders/colorFromVertex.frag");

    shaderPtr = Game::GetDataMgr().CreateShader("WithAmbiantLight",
                                                "shaders/lighting.vert", "shaders/lighting.frag");

    // Load materials
    GL::Material* pMat;
    pMat = Game::GetDataMgr().CreateMaterial("Wall", "Default");
    pMat->LinkTexture(Game::GetDataMgr().GetTexture("Wall"), GL_TEXTURE3);
    Game::GetDataMgr().GetShader("Default")->Use();
    Game::GetDataMgr().GetShader("Default")->SetInt("tex0", 3);
    Game::GetDataMgr().GetShader("Default")->SetInt("tex1", 4);

    Game::GetDataMgr().CreateMaterial("ColorFromProgram", "ColorFromProgram");

    pMat = Game::GetDataMgr().CreateMaterial("UV", "UVscale");
    pMat->LinkTexture(Game::GetDataMgr().GetTexture("Container"), GL_TEXTURE3);
    pMat->LinkTexture(Game::GetDataMgr().GetTexture("Awesomeface"), GL_TEXTURE4);

    Game::GetDataMgr().CreateMaterial("ColorFromVertex", "ColorFromVertex");

    pMat = Game::GetDataMgr().CreateMaterial("Box", "Default");
    pMat->LinkTexture(Game::GetDataMgr().GetTexture("Awesomeface"), GL_TEXTURE4);

    pMat = Game::GetDataMgr().CreateMaterial("BoxLight", "WithAmbiantLight");
    pMat->LinkDiffuseMap(Game::GetDataMgr().GetTexture("ContainerDiffuseMap"));
    pMat->LinkSpecularMap(Game::GetDataMgr().GetTexture("ContainerSpecularMap"));
    pMat->LinkEmissionMap(Game::GetDataMgr().GetTexture("ContainerEmissionMap"));
    pMat->SetEmission(glm::vec3(0.3f, 0.3f, 0.3f));
}
