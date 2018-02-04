#ifndef __SHADER__HPP
#define __SHADER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition


namespace simpleGL
{
    // Encapsulate a shader program (vertex and fragment shader).
    class SIMPLEGL_API Shader
    {
    private:
        unsigned int m_id;

        void ConstructProgram(std::string vertexPath, std::string fragPath);

    public:
        Shader(std::string vertexPath, std::string fragPath);
        ~Shader();

        void Use();

        // Unifrom functions
        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;
        void SetFloat(const std::string &name, float value) const;
        void SetFloat4(const std::string &name, float value[4]) const;
        void SetFloat3(const std::string &name, float value[3]) const;

        static int GetMaxAttributeNb();
    };
}
#endif
