// Add Glad first
#include <glad/glad.h>

// Include open Gl under the hood
// Also correct window specific to OS
#include <GLFW/glfw3.h>

// Standard output
#include <string>       // std::string
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <sstream>      // std::stringstream


using std::cout;
using std::endl;

// Ref
// http://www.glfw.org/docs/latest/

// Tuto
// https://learnopengl.com/Getting-started/Creating-a-window
// https://learnopengl.com/Getting-started/Hello-Window


void Framebuffer_size_callback(GLFWwindow* _window, int _width, int _height);
void ProcessInput(GLFWwindow *window);

// Shader helper
std::string ReadFile(std::string filePath);
unsigned int CompileAndLinkShader(std::string vertexPath, std::string fragPath);



// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main(void)
{
    // Init should be called first
    glfwInit();

    // Specify we use OpenGL 3.3 core version
    // http://www.glfw.org/docs/latest/window.html#window_hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Mac users

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My first OpenGL Window", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD: Load all OpenGL function pointers
    // We pass GLAD the function to load the adress of the OpenGL function pointers which is OS-specific
    // glfwGetProcAddress find the correct one based on the OS
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Define the drawing area based on the window coordinates
    // y start at the bottom of the viewport
    // Note that processed coordinates in OpenGL are between -1 and 1
    // so we effectively map from the range (-1 to 1) to (0, SCR_WIDTH) and (0, SCR_HEIGHT).
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    // We register the callback functions after we've created the window
    // and before the game loop is initiated.
    glfwSetFramebufferSizeCallback(window, Framebuffer_size_callback);


    // Construct and use a specific shader program
    unsigned int blueShader, orangeShader;
    blueShader = CompileAndLinkShader("../src/Shaders/basicShader.vert",
                                         "../src/Shaders/blueShader.frag");
    orangeShader = CompileAndLinkShader("../src/Shaders/basicShader.vert",
                                         "../src/Shaders/orangeShader.frag");

    // Two triangles
    float vertices1[] =
    {
        -0.8f, -0.8f, 0.0f,
        -0.8f,  -0.4f, 0.0f,
        -0.4f, -0.8f, 0.0f
    };

    float vertices2[] =
    {
        0.4f, 0.4f, 0.0f,
        0.4f,  0.8f, 0.0f,
        0.8f, 0.4f, 0.0f
    };


    // // Quad with indexed buffer
    // float vertices[] =
    // {
    //      0.5f,  0.5f, 0.0f,  // top right
    //      0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left
    // };
    // unsigned int indices[] =
    // {
    //     0, 1, 3,   // first triangle
    //     1, 2, 3    // second triangle
    // };

    // // Quad using strip
    // float vertices[] =
    // {
    //     -0.5f, -0.5f, 0.0f,
    //     -0.5f,  0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.5f,  0.5f, 0.0f
    // };

    // // Quad using fan
    // float vertices[] =
    // {
    //     -0.5f, -0.5f, 0.0f,
    //     -0.5f,  0.5f, 0.0f,
    //     0.5f,  0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f
    // };

    unsigned int VBO2, VAO2, VBO1, VAO1, EBO;

    // Create a vertex array buffer (VAO), a vertex buffer object (VBO),
    // and an Element Buffer Object (EBO).
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    // // Bind the VAO first to store any subsequent calls to VBO glVertexAttribPointer
    // // glEnableVertexAttribArray inside the currently bound VAO.
    // glBindVertexArray(VAO1);

    // // Bind and set vertex buffers using VBO
    // glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // Bind and set index buffer using EBO
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // Configure vertex attributes.
    // // 0 refer to shader location (see .vert layout)
    // // Then we specify the data as 3 floats without normalization
    // // Last parameter is the pointeur offset (here 0)
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // Store inside the first VAO
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Store inside the second VAO
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Enable culling and set it to front mode.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    // Start glory game loop by checking for close at each loop
    while (!glfwWindowShouldClose(window))
    {
        // Handles inputs
        ProcessInput(window);

        // Rendering
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Select shader program for the draw call
        glUseProgram(orangeShader);
        // Select VAO to use for passing object to GPU
        glBindVertexArray(VAO1);
        // Draw vertices using only VBO
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Select shader program for the draw call
        glUseProgram(blueShader);
        // Select VAO to use for passing object to GPU
        glBindVertexArray(VAO2);
        // Draw vertices using only VBO
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // // Draw vertices using VBO and EBO
        // glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        // Swap buffer
        glfwSwapBuffers(window);

        // Event pool (keyboard, mouse, ...)
        glfwPollEvents();
    }

    // De-allocate all ressources once done with them.
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}



















// Callback to adjust drawing area based on window area.
// window used in the callback call
void Framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}


void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        // Send close event.
        glfwSetWindowShouldClose(window, true);
    }

    // Switch wireframe / fill / point mode
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
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
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
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


// Read a file from start to end and return the content
std::string ReadFile(std::string filePath)
{
    std::string content;
    std::ifstream readStream(filePath, std::ios::in);

    if(!readStream.is_open())
    {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    // Get content of stream buffer loaded in sstr
    std::stringstream sstr;
    sstr << readStream.rdbuf();
    content =  sstr.str();

    readStream.close();
    return content;
}

// Return index assigned to program shader created.
unsigned int CompileAndLinkShader(std::string vertexPath, std::string fragPath)
{
    // To handle errors
    int  success;
    char infoLog[512];

    // Load an compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Should first store string then convert to char pointer
    // WHY ???
    std::string vertexShaderString = ReadFile(vertexPath);
    const char* vertexShaderSource = vertexShaderString.c_str();
    // Attach source code to object (vertexShaderSource)
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        // Get error and store it in as a char array
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "*** Vertex Shader definition ***" << std::endl;
        std::cout << vertexShaderString << std::endl;
    }

    // Load an compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragShaderString = ReadFile(fragPath);
    const char* fragShaderSource = fragShaderString.c_str();
    glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        // Get error and store it in as a char array
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "*** Fragment Shader definition ***" << std::endl;
        std::cout << fragShaderString << std::endl;
    }

    // Create a shader program that link vertex and fragment together
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // We can use it now and remove unused shaders parts
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
