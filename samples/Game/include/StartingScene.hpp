#ifndef __STARTINGSCENE__HPP
#define __STARTINGSCENE__HPP

#include "simpleGL.hpp"
#include "memory"


class StartingScene: public simpleGL::IScene
{
private:
    simpleGL::Node*         m_pFirstNode;
    simpleGL::NodeManager*  m_pContainer;
    simpleGL::Triangle*     m_pTriangles[2];

    simpleGL::Shader        m_colorShader;
    simpleGL::Texture       m_textureWall;


    void ChangeGreenOverTime(simpleGL::Shader& _shader);

public:
    StartingScene();
    virtual ~StartingScene();

    virtual bool OnInit();
    virtual bool OnUpdate();
    virtual bool OnQuit();
    virtual void OnRender();
};
#endif
