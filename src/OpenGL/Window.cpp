#include "OpenGL/Window.hpp"

#include <assert.h>
#include "GameManager.hpp"


namespace simpleGL
{
    bool Window::instantiated_ = false;

    Window::Window(unsigned int _width, unsigned int _height, std::string _name)
        : m_width(_width), m_height(_height), m_name(_name)
    {
        assert(!instantiated_);
        instantiated_ = true;

        m_clearColor[0] = 0.2f;
        m_clearColor[1] = 0.2f;
        m_clearColor[2] = 0.2f;
        m_clearColor[3] = 1.0f;
    }

    Window::~Window()
    {
        instantiated_ = false;
    }

    bool Window::Init()
    {
        // Init should be called first
        glfwInit();

        // Specify we use OpenGL 3.3 core version
        // http://www.glfw.org/docs/latest/window.html#window_hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_versionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_versionMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, m_profile);

        #if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Mac users
        #endif

        m_pWindow = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
        if (m_pWindow == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(m_pWindow);

        // GLAD: Load all OpenGL function pointers
        // We pass GLAD the function to load the adress of the OpenGL function pointers which is OS-specific
        // glfwGetProcAddress find the correct one based on the OS
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // Define the drawing area based on the window coordinates
        // y start at the bottom of the viewport
        // Note that processed coordinates in OpenGL are between -1 and 1
        // so we effectively map from the range (-1 to 1) to (0, m_width) and (0, m_height).
        glViewport(0, 0, m_width, m_height);
        // We register the callback functions after we've created the window
        // and before the game loop is initiated.
        glfwSetFramebufferSizeCallback(m_pWindow, Framebuffer_size_callback);

        SetDefaultFlag();

        return true;
    }

    bool Window::Update()
    {
        while (!glfwWindowShouldClose(m_pWindow))
        {
            // @TODO Handles inputs using external class
            ProcessInput();

            GameManager::GetNodeMgr().Update();

            Render();

            // Event pool (keyboard, mouse, ...)
            glfwPollEvents();
        }
    }

    bool Window::Quit()
    {
        glfwTerminate();
        return true;
    }

    void Window::Render()
    {
        glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // Recursive call to draw of all nodes.
        GameManager::GetNodeMgr().Draw();

        // Swap buffer
        glfwSwapBuffers(m_pWindow);
    }

    void Window::SetDefaultFlag()
    {
        // Enable culling and set it to front mode.
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }

    // Callback to adjust drawing area based on window area.
    void Window::Framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
    {
        glViewport(0, 0, _width, _height);
    }

    void Window::ProcessInput()
    {
        if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            // Send close event.
            glfwSetWindowShouldClose(m_pWindow, true);
        }

        // Switch wireframe / fill / point mode
        if (glfwGetKey(m_pWindow, GLFW_KEY_F) == GLFW_PRESS)
        {
            GLint result[2];
            glGetIntegerv(GL_POLYGON_MODE, result);
            switch (result[0])
            {
                case GL_LINE:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                    break;
                case GL_POINT:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;
                case GL_FILL:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    break;
            }
        }
        // Switch culling mode
        if (glfwGetKey(m_pWindow, GLFW_KEY_C) == GLFW_PRESS)
        {
            GLint result;
            glGetIntegerv(GL_CULL_FACE_MODE, &result);
            switch (result)
            {
                case GL_BACK:
                    glCullFace(GL_FRONT);
                    break;
                case GL_FRONT:
                    glCullFace(GL_FRONT_AND_BACK);
                    break;
                case GL_FRONT_AND_BACK:
                    glCullFace(GL_BACK);
                    break;
            }
        }
    }
}
