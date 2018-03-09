#ifndef __CAMERADEBUG__HPP
#define __CAMERADEBUG__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Camera.hpp"


namespace simpleGL
{
    /// https://www.3dgep.com/understanding-the-view-matrix/
    /// A camera is a component that implement the ICamera interface
    class SIMPLEGL_API CameraDebug: public Camera
    {
    public:
        CameraDebug();
        ~CameraDebug() = default;

        virtual void Strafe(float _units);
        virtual void Fly(float _units);
        virtual void Walk(float _units);
        virtual void Yaw(float degrees);
        virtual void Pitch(float degrees);
        virtual void Roll(float degrees);

        virtual bool Draw() {};
        virtual bool Init() {};
        virtual bool Update(){};
        virtual bool Quit(){};
        virtual Component* Clone() {return new CameraDebug(*this);};
    };
}

#endif
