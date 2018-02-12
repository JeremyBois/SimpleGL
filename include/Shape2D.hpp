#ifndef __SHAPE2D__HPP
#define __SHAPE2D__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape.hpp"

#include "glm.hpp"


namespace simpleGL
{
    // Abstract class for any 2D shapes
    class SIMPLEGL_LOCAL Shape2D: public Shape
    {
    private:
        glm::vec3 m_refRotOrigin;

    protected:
        glm::vec3 m_rotOrigin;
        glm::vec3 m_eulerAngles;


        virtual void ConstructModelMatrix();

    public:
        Shape2D();
        virtual ~Shape2D();

        virtual void SetYawPitchRollAngles(glm::vec3 _eulerAngles, glm::vec3 _origin=glm::vec3(0.0f, 0.0f, 0.0f));
        virtual void SetRotationX(float _degrees);
        virtual void SetRotationY(float _degrees);
        virtual void SetRotationZ(float _degrees);

        const glm::vec3 GetYawPitchRollAngles() const;

        virtual void Draw();
    };
}
#endif
