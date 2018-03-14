#ifndef __LIGHTSHADOWSCENE__HPP
#define __LIGHTSHADOWSCENE__HPP

#include "simpleGL.hpp"



class LightShadowScene: public simpleGL::IScene
{
private:
    simpleGL::Node*         m_pNodes[13];
    simpleGL::Cuboid*       m_pCuboid;

    simpleGL::CameraDebug*   m_pCam;

    // Light
    simpleGL::DirectionalLight*    m_pDirLight;
    simpleGL::PointLight*          m_pPointLight;
    simpleGL::Cuboid*   m_lightShape;

    static double s_lastX, s_lastY;

public:
    LightShadowScene();
    virtual ~LightShadowScene();

    virtual bool OnInit();
    virtual bool OnUpdate();
    virtual bool OnQuit();
    virtual void OnRender();

    virtual void ProcessInput();

    static void MyKeyEventHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
    static void MyMousePosEventHandler(GLFWwindow* _window, double _xpos, double _ypos);
    static void MyScrollEventHandler(GLFWwindow* _window, double _xoffset, double _yoffset);

};
#endif
