#ifndef __SHAPERENDERER__HPP
#define __SHAPERENDERER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Component.hpp"
#include "Shape.hpp"
#include "OpenGL/Material.hpp"



namespace simpleGL
{
    /// Componenent which can draw any shape object.
    class SIMPLEGL_API ShapeRenderer: public Component
    {
    private:
        Shape*    m_pShape;
        Material* m_pMaterial;

    public:
        ShapeRenderer();
        virtual ~ShapeRenderer();

        void LinkShape(Shape* _shape);
        void LinkMaterial(Material* _material);

        virtual bool Draw(Component *_pcomp);
        virtual bool Init() {return true;}
        virtual bool Update(){return true;}
        virtual bool Quit(){return true;}

        virtual Component* Clone();
    };
}
#endif
