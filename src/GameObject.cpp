#include "GameObject.hpp"


namespace simpleGL
{
    unsigned int GameObject::s_nextID = 0;

    GameObject::GameObject()
    {
        m_id = s_nextID++;
    }

    GameObject::~GameObject()
    {

    }
}
