#include "Components/ShapeRenderer.hpp"
#include "Node.hpp"

namespace simpleGL
{
    ShapeRenderer::ShapeRenderer()
    {
        m_pShape = nullptr;
        m_pMaterial = nullptr;
    }

    ShapeRenderer::~ShapeRenderer()
    {
    }

    Component* ShapeRenderer::Clone()
    {
        ShapeRenderer* shapeR = new ShapeRenderer();
        shapeR->m_pMaterial = m_pMaterial;
        shapeR->m_pShape = m_pShape;

        return shapeR;
    }

    bool ShapeRenderer::Draw()
    {
        if (!IsActive())
        {
            return false;
        }

        if (m_pMaterial != nullptr && m_pShape != nullptr)
        {
            m_pMaterial->Use(*(GetNode().GetComponent<Transform>()));
            m_pShape->Draw();
            return true;
        }
        return false;
    }


    void ShapeRenderer::LinkShape(Shape* _pShape)
    {
        m_pShape = _pShape;
    }

    void ShapeRenderer::LinkMaterial(Material* _pMaterial)
    {
        m_pMaterial = _pMaterial;
    }

}
