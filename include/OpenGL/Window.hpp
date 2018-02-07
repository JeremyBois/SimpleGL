#ifndef __WINDOW__HPP
#define __WINDOW__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/IWindow.hpp"

namespace simpleGL
{
    // @TODO should manage time (delta)
    class SIMPLEGL_LOCAL Window: public IWindow
    {
    private:
        unsigned int m_width, m_height;

        void ProcessInput();
        void SetDefaultFlag();

        // We only one a single instance but no singleton
        static bool instantiated_;
        static void Framebuffer_size_callback(GLFWwindow* _window, int _width, int _height);


    protected:
        int const m_versionMajor = 3;
        int const m_versionMinor = 3;
        int const m_profile = GLFW_OPENGL_CORE_PROFILE;

        std::string m_name;
        float m_clearColor[4];

        GLFWwindow* m_pWindow;

    public:
        Window(unsigned int _width, unsigned int _height, std::string _name);
        ~Window();

        virtual bool Init();
        virtual bool Update();
        virtual bool Quit();
        virtual void Render();

        virtual inline const GLFWwindow& GetWindow() const {return *m_pWindow;}
    };
}
#endif
