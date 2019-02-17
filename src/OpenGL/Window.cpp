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

        m_pUserKeyCallback = nullptr;

        m_clearColor[0] = 0.1f;
        m_clearColor[1] = 0.1f;
        m_clearColor[2] = 0.1f;
        m_clearColor[3] = 1.0f;

        mainCam = nullptr;


        m_timeLastFrame = 0.0f;
        m_deltaTime = 0.0f;
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
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(m_pWindow);

        // GLAD: Load all OpenGL function pointers
        // We pass GLAD the function to load the adress of the OpenGL function pointers which is OS-specific
        // glfwGetProcAddress find the correct one based on the OS
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        // Define the drawing area based on the window coordinates
        // y start at the bottom of the viewport
        // Note that processed coordinates in OpenGL are between -1 and 1
        // so we effectively map from the range (-1 to 1) to (0, m_width) and (0, m_height).
        glViewport(0, 0, m_width, m_height);
        // We register the callback functions after we've created the window
        // and before the game loop is initiated.
        glfwSetFramebufferSizeCallback(m_pWindow, Framebuffer_size_callback);

        // Register a callback for keys inputs
        glfwSetKeyCallback(m_pWindow, Key_callback);

        SetDefaultFlag();

        // Hide cursor for camera movements
        glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        return true;
    }

    bool Window::Update()
    {
        while (!glfwWindowShouldClose(m_pWindow))
        {
            // Update DeltaTime since last frame
            float currentFrame = (float)glfwGetTime();
            m_deltaTime = currentFrame - m_timeLastFrame;
            m_timeLastFrame = currentFrame;

            ProcessInput();

            GameManager::Update();

            if (mainCam != nullptr)
            {
                m_viewM = mainCam->GetViewMatrix();
                m_projM = mainCam->GetPerspectiveMatrix();
            }

            Render();

            // Event pool (keyboard, mouse, ...)
            glfwPollEvents();
        }

        return true;
    }

    bool Window::Quit()
    {
        GameManager::Quit();

        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
        return true;
    }

    void Window::Render()
    {
        glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Recursive call to draw of all nodes.
        GameManager::Render();

        // Swap buffer
        glfwSwapBuffers(m_pWindow);
    }

    void Window::SetDefaultFlag()
    {
        // Enable culling and set it to front mode.
        // Vertices must be defines in counter-clockwise order for Backface culling
        // to work properly.
        // https://stackoverflow.com/questions/8142388/in-what-order-should-i-send-my-vertices-to-opengl-for-culling#8142461
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Add depth testing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    // Callback to adjust drawing area based on window area.
    void Window::Framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
    {
        glViewport(0, 0, _width, _height);
    }

    void Window::Key_callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
    {
        if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
        {
            // Send close event.
            glfwSetWindowShouldClose(_window, GL_TRUE);
        }

        // Debug event handler
        DebugKeyEventHandler(_window, _key, _scancode, _action, _mods);

        // Let user handle more event
        if (GameManager::GetWindow().m_pUserKeyCallback != nullptr)
        {
            GameManager::GetWindow().m_pUserKeyCallback(_window, _key, _scancode, _action, _mods);
        }
    }

    // To add some inputs to handle
    // For just pressed or just released attach a callback
    void Window::ProcessInput()
    {

    }

    int Window::GetKey(int _key)
    {
        return glfwGetKey(m_pWindow, _key);
    }


    void Window::DebugKeyEventHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
    {
        // Switch wireframe / fill / point mode
        if (_key == GLFW_KEY_V && _action == GLFW_PRESS)
        {
            GLint result[2];
            glGetIntegerv(GL_POLYGON_MODE, result);
            switch (result[0])
            {
                case GL_LINE:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                    cout << "Drawing mode now: POINT" << endl;
                    break;
                case GL_POINT:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    cout << "Drawing mode now: FILL" << endl;
                    break;
                case GL_FILL:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    cout << "Drawing mode now: LINE" << endl;
                    break;
            }
        }
        // Switch culling mode
        if (_key == GLFW_KEY_C && _action == GLFW_PRESS)
        {
            GLint result;
            glGetIntegerv(GL_CULL_FACE_MODE, &result);
            switch (result)
            {
                case GL_BACK:
                    glCullFace(GL_FRONT);
                    cout << "Culling now: FRONT" << endl;
                    break;
                case GL_FRONT:
                    glCullFace(GL_FRONT_AND_BACK);
                    cout << "Culling now: FRONT AND BACK" << endl;
                    break;
                case GL_FRONT_AND_BACK:
                    glCullFace(GL_BACK);
                    cout << "Culling now: BACK" << endl;
                    break;
            }
        }
    }

    GLFWkeyfun Window::AttachKeyEventCallback(GLFWkeyfun _callback)
    {
        GLFWkeyfun oldCallback = m_pUserKeyCallback;
        m_pUserKeyCallback = _callback;
        return oldCallback;
    }

    GLFWcursorposfun Window::AttachMousePosEventCallback(GLFWcursorposfun _callback)
    {
        return glfwSetCursorPosCallback(m_pWindow, _callback);
    }

    GLFWscrollfun Window::AttachScrollEventCallback(GLFWscrollfun _callback)
    {
        return glfwSetScrollCallback(m_pWindow, _callback);
    }

}
