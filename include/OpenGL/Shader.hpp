#ifndef __SHADER__HPP
#define __SHADER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


namespace simpleGL
{
    // Encapsulate a shader program (vertex and fragment shader).
    class SIMPLEGL_API Shader
    {
    private:
        unsigned int m_id;

        void ConstructProgram(std::string vertexPath, std::string fragPath);
        void CheckForCompileErrors(GLuint _shader, std::string _type);

    public:
        Shader() {};  // Allows lazy initialization
        Shader(std::string vertexPath, std::string fragPath);
        ~Shader();

        void Use();
        unsigned int ID() const {return m_id;}

        // Unifrom functions
        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;
        void SetFloat(const std::string &name, float value) const;
        void SetFloat4(const std::string &name, float value[4]) const;
        void SetFloat3(const std::string &name, float value[3]) const;
        void SetVec4(const std::string &name, const glm::vec4 &value) const;
        void SetVec4(const std::string &name, float x, float y, float z, float w);
        void SetMat2(const std::string &name, const glm::mat2 &mat) const;
        void SetMat3(const std::string &name, const glm::mat3 &mat) const;
        void SetMat4(const std::string &name, const glm::mat4 &mat) const;

        static int GetMaxAttributeNb();
    };
}
#endif
