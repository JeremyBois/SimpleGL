#ifndef __SPOTLIGHT__HPP
#define __SPOTLIGHT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Components/Light.hpp"
#include "OpenGL/Texture.hpp"

#include <vector>


namespace simpleGL
{
    /// Create a light with a position with a given position somewhere that
    /// illuminates in a specific direction where the light rays fade out over distance.
    class SIMPLEGL_API SpotLight: public Light
    {
    protected:
        static std::vector<SpotLight*> SpotLightContainer;

        float m_constCoef, m_linearCoef, m_quadraticCoef;
        float m_cutOffAngle, m_outerCutOffAngle;

    public:
        SpotLight();
        virtual ~SpotLight();

        // Direction from transform

        // Coefficients
        float GetConstCoef() const {return m_constCoef;}
        float GetLinearCoef() const {return m_linearCoef;}
        float GetQuadraticCoef() const {return m_quadraticCoef;}

        void SetAmbient(float _constCoef) {m_constCoef = _constCoef;}
        void SetDiffuse(float _linearCoef) {m_linearCoef = _linearCoef;}
        void SetSpecular(float _quadraticCoef) {m_quadraticCoef = _quadraticCoef;}

        // Angles
        float GetInnerAngle() const {return m_cutOffAngle;}
        float GetOuterAngle() const {return m_outerCutOffAngle;}

        void SetInnerAngle(float _degrees) {m_cutOffAngle = _degrees;}
        void SetOuterAngle(float _degrees) {m_outerCutOffAngle = _degrees;}

        // Set light in properties inside the shader
        virtual void Use(const Shader& _shader, int _lightIndex=0) const;

        virtual SpotLight* Clone() {return new SpotLight(*this);}

        static void UseAll(const Shader& _shader);
    };
}
#endif
