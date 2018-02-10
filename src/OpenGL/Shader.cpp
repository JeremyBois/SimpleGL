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
        // Load an compile vertex shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        std::string vertexShaderString = StreamUtility::ReadFile(vertexPath);
        const char* vertexShaderSource = vertexShaderString.c_str();
        // Attach source code to object (vertexShaderSource)
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        CheckForCompileErrors(vertexShader, "VERTEX");

        // Load an compile fragment shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        std::string fragShaderString = StreamUtility::ReadFile(fragPath);
        const char* fragShaderSource = fragShaderString.c_str();
        glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
        glCompileShader(fragmentShader);
        CheckForCompileErrors(vertexShader, "FRAGMENT");

        // Create a shader program that link vertex and fragment together
        m_id = glCreateProgram();
        glAttachShader(m_id, vertexShader);
        glAttachShader(m_id, fragmentShader);
        glLinkProgram(m_id);
        CheckForCompileErrors(vertexShader, "PROGRAM");

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

    void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
    }

    void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // Get the maximum number of attributes (each attribute is a vec4)
    // you can declare per shader
    int Shader::GetMaxAttributeNb()
    {
        GLint nbAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nbAttributes);
        return nbAttributes;
    }

    void Shader::CheckForCompileErrors(GLuint shader, std::string type)
    {
        const unsigned int infoSizeMax = 1024;
        GLint success;
        GLchar infoLog[infoSizeMax];

        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, infoSizeMax, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, infoSizeMax, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}
