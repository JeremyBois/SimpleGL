#ifndef __SHAPERENDERER__HPP
#define __SHAPERENDERER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Component.hpp"
#include "Shape.hpp"
#include "OpenGL/Material.hpp"



namespace simpleGL
{
    // Can be used to construct and draw a triangle
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

        virtual bool Draw();
        virtual bool Init() {};
        virtual bool Update(){};
        virtual bool Quit(){};
        virtual Component* Clone() {return new ShapeRenderer();}
    };
}
#endif
