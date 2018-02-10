#include "simpleGL.hpp"
#include "StartingScene.hpp"

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


typedef simpleGL::GameManager Game;


int main(int argc, char** argv)
{
    ChangeWorkingDirectory(__FILE__, "../../../");


    // Test implementation of Game Manager / Window
    Game::Init(800, 600, "My OpenGl window");

    // Create a simple SceneManager with a starting scene
    StartingScene* firstScene = new StartingScene();
    simpleGL::SceneFSM* mySceneManager = new simpleGL::SceneFSM(*firstScene);
    simpleGL::GameManager::Provide(mySceneManager);

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
