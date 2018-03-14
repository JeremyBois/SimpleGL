#ifndef __TRANSFORM__HPP
#define __TRANSFORM__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Component.hpp"

#include "glm.hpp"
#include "gtc/quaternion.hpp"

namespace simpleGL
{
    /// Control local to world transformation.
    /// Attached to every Node at their creation.
    class SIMPLEGL_API Transform: public Component
    {
    protected:
        // Store rotation as a quaternion but keep track of local basis
        glm::vec3 m_look;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::quat m_orientation;
        glm::vec3 m_position;
        glm::vec3 m_scale;

        // Local model --> world matrix
        glm::mat4 m_localToWorld;


        virtual void ConstructModelMatrix();

    public:

        static const glm::vec3 XAxis, YAxis, ZAxis;

        Transform();
        virtual ~Transform();

        inline virtual const glm::mat4& GetModelMatrix() const {return m_localToWorld;}

        inline         const glm::vec3  GetPosition()    const {return m_position;}
        inline         const glm::quat  GetRotation()    const {return m_orientation;}
        inline         const glm::vec3  GetScale()       const {return m_scale;}
        inline         const glm::vec3  GetLook() const {return m_look;}
        inline         const glm::vec3  GetUp() const {return m_up;}
        inline         const glm::vec3  GetRight() const {return m_right;}
        const                glm::vec3  GetYawPitchRollAngles() const;

        // Set common transformations
        void SetPosition(const glm::vec3 _position);
        void SetScale(const glm::vec3 _scale);
        void SetRotationX(float _degrees);
        void SetRotationY(float _degrees);
        void SetRotationZ(float _degrees);
        void SetRotation(const glm::quat _rotation);
        void SetRotation(float _degrees, const glm::vec3 _axe);
        void SetRotation(const glm::vec3 _eulerAngles);

        virtual bool Init() {return true;}
        virtual bool Draw() {return true;}
        virtual bool Update() {return true;}
        virtual bool Quit() {return true;}

        virtual Component* Clone() {return new Transform(*this);}
        virtual bool       SetParent(Node* _pNode);
    };
}
#endif
