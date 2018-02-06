#include "OpenGL/Shader.hpp"

#include "Utility/StreamUtility.hpp"


namespace simpleGL
{
    Shader::Shader(std::string vertexPath, std::string fragPath)
    {
        ConstructProgram(vertexPath, fragPath);
    }

    Shader::~Shader()
    {

    }

    void Shader::ConstructProgram(std::string vertexPath, std::string fragPath)
    {
        // To handle errors
        int  success;
        char infoLog[512];

        // Load an compile vertex shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        std::string vertexShaderString = StreamUtility::ReadFile(vertexPath);
        const char* vertexShaderSource = vertexShaderString.c_str();
        // Attach source code to object (vertexShaderSource)
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            // Get error and store it in as a char array
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // else
        // {
        //     std::cout << "*** Vertex Shader definition ***" << std::endl;
        //     std::cout << vertexShaderString << std::endl;
        // }

        // Load an compile fragment shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        std::string fragShaderString = StreamUtility::ReadFile(fragPath);
        const char* fragShaderSource = fragShaderString.c_str();
        glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            // Get error and store it in as a char array
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // else
        // {
        //     std::cout << "*** Fragment Shader definition ***" << std::endl;
        //     std::cout << fragShaderString << std::endl;
        // }

        // Create a shader program that link vertex and fragment together
        m_id = glCreateProgram();
        glAttachShader(m_id, vertexShader);
        glAttachShader(m_id, fragmentShader);
        glLinkProgram(m_id);
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(m_id, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Clean up
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::Use()
    {
        glUseProgram(m_id);
    }

    void Shader::SetBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }
    void Shader::SetInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }
    void Shader::SetFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::SetFloat4(const std::string &name, float value[4]) const
    {
        int vertexColorLocation = glGetUniformLocation(m_id, name.c_str());
        glUniform4f(vertexColorLocation, value[0], value[1], value[2], value[3]);
    }

    void Shader::SetFloat3(const std::string &name, float value[3]) const
    {
        int vertexColorLocation = glGetUniformLocation(m_id, name.c_str());
        glUniform3f(vertexColorLocation, value[0], value[1], value[2]);
    }

    // Get the maximum number of attributes (each attribute is a vec4)
    // you can declare per shader
    int Shader::GetMaxAttributeNb()
    {
        GLint nbAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nbAttributes);
        return nbAttributes;
    }
}
