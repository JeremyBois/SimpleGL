#ifndef __SHADER__HPP
#define __SHADER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"

#include "glm.hpp"


namespace simpleGL
{
    // Encapsulate a shader program (vertex and fragment shader).
    class SIMPLEGL_API Shader: public GameObject
    {
    private:
        unsigned int m_shaderID;

        void ConstructProgram(const std::string _vertexPath, const std::string _fragPath);
        void CheckForCompileErrors(GLuint _shader, const std::string _type);

    public:
        Shader() {};  // Allows lazy initialization
        Shader(const std::string vertexPath, const std::string fragPath);
        ~Shader();

        void Use();
        unsigned int ShaderID() const {return m_shaderID;}

        // Unifrom functions
        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;

        void SetFloat(const std::string &name, const float value) const;
        void SetFloat2(const std::string &name, const float value[2]) const;
        void SetFloat3(const std::string &name, const float value[3]) const;
        void SetFloat4(const std::string &name, const float value[4]) const;

        void SetVec2(const std::string &name, const glm::vec2 &value) const;
        void SetVec3(const std::string &name, const glm::vec3 &value) const;
        void SetVec4(const std::string &name, const glm::vec4 &value) const;
        void SetVec4(const std::string &name, float x, float y, float z, float w) const;

        void SetMat2(const std::string &name, const glm::mat2 &mat) const;
        void SetMat3(const std::string &name, const glm::mat3 &mat) const;
        void SetMat4(const std::string &name, const glm::mat4 &mat) const;

        static int GetMaxAttributeNb();
    };
}
#endif
