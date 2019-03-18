#ifndef __CAMERAFPS__HPP
#define __CAMERAFPS__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Camera.hpp"


namespace simpleGL
{
    /// https://www.3dgep.com/understanding-the-view-matrix/
    /// A camera is a component that implement the ICamera interface
    class SIMPLEGL_API CameraFPS: public Camera
    {
    public:
        CameraFPS();
        ~CameraFPS() = default;

        virtual void Strafe(float _units);
        virtual void Fly(float _units);
        virtual void Walk(float _units);
        virtual void Yaw(float degrees);
        virtual void Pitch(float degrees);
        virtual void Roll(float degrees);

        virtual bool Init() {return true;}
        virtual bool Update(){return true;}
        virtual bool Quit(){return true;}
        virtual Component* Clone() {return new CameraFPS(*this);};
    };
}

#endif
