#ifndef __STARTINGSCENE__HPP
#define __STARTINGSCENE__HPP

#include "simpleGL.hpp"
#include "memory"



class StartingScene: public simpleGL::IScene
{
private:
    simpleGL::NodeManager   m_container;
    simpleGL::Node*         m_pNodes[4];

    simpleGL::Triangle*     m_pTriangles[2];
    simpleGL::Quad*         m_pQuad;
    simpleGL::Cuboid*       m_pCuboid;

    // Material (shader + texture)
    simpleGL::Material*     m_pBasicMat;
    simpleGL::Material*     m_pColorMat;
    simpleGL::Material*     m_pUVMat;
    simpleGL::Material*     m_pVertexMat;

    simpleGL::Shader        m_basicShader;
    simpleGL::Shader        m_colorShader;
    simpleGL::Shader        m_uvShader;
    simpleGL::Shader        m_colorVertexShader;

    simpleGL::Texture       m_textureWall;
    simpleGL::Texture       m_textureContainer;
    simpleGL::Texture       m_textureSmile;

    // To enable texture zoom
    float m_zoomScale = 1.0f;

    void ChangeGreenOverTime(simpleGL::Shader& _shader);
    void ZoomUVOverTime(simpleGL::Shader& _shader);
    void ZoomUV(simpleGL::Shader& _shader, bool _zoom);

public:
    StartingScene();
    virtual ~StartingScene();

    virtual bool OnInit();
    virtual bool OnUpdate();
    virtual bool OnQuit();
    virtual void OnRender();

    // @TODO Must be defined in IScene
    static void MyKeyEventHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
};
#endif
