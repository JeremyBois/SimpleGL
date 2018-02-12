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
        glm::vec3 m_position;
        glm::vec3 m_scale;
        glm::vec3 m_rotOrigin;
        glm::vec3 m_eulerAngles;


        virtual void ConstructLocalToWorldMatrix();

    public:
        Shape2D();
        virtual ~Shape2D();

        virtual void SetYawPitchRollAngles(glm::vec3 _eulerAngles, glm::vec3 _origin=glm::vec3(0.0f, 0.0f, 0.0f));
        virtual void SetRotationX(float _degrees);
        virtual void SetRotationY(float _degrees);
        virtual void SetRotationZ(float _degrees);
        virtual void SetPosition(glm::vec3 _position);
        virtual void SetScale(glm::vec3 _scale);

        const glm::vec3         GetYawPitchRollAngles() const;
        inline const glm::vec3  GetPosition() const {return m_position;}
        inline const glm::vec3  GetScale()    const {return m_scale;}
        inline const glm::mat4& GetLocalToWorldMatrix() const {return m_localToWorld;};

        virtual void Draw();
    };
}
#endif
