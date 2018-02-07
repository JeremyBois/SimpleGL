#include "simpleGL.hpp"
#include "StartingScene.hpp"


typedef simpleGL::GameManager Game;


int main(void)
{
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
