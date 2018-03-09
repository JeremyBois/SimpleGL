#ifndef __STARTINGSCENE__HPP
#define __STARTINGSCENE__HPP

#include "simpleGL.hpp"



class StartingScene: public simpleGL::IScene
{
private:
    simpleGL::Node*         m_pNodes[5];

    simpleGL::Triangle*     m_pTriangles[2];
    simpleGL::Quad*         m_pQuad;
    simpleGL::Cuboid*       m_pCuboid;

    simpleGL::CameraDebug*   m_pCam;

    static double s_lastX, s_lastY;

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

    virtual void ProcessInput();

    // @TODO Must be defined in IScene
    static void MyKeyEventHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
    static void MyMousePosEventHandler(GLFWwindow* _window, double _xpos, double _ypos);
    static void MyScrollEventHandler(GLFWwindow* _window, double _xoffset, double _yoffset);
};
#endif
