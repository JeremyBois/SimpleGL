#ifndef __ILIGHTMANAGER__HPP
#define __ILIGHTMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Light.hpp"

#include <unordered_map>
#include <string>

namespace simpleGL
{
    // Life cycle is controlled by a node not here --> raw pointer used.
    typedef std::unordered_map<std::string, Light*> LightContainer;
    typedef LightContainer::iterator LightContainerIt;
    typedef LightContainer::const_iterator LightContainerConstIt;


    /// Interface for DataManager implementations
    class SIMPLEGL_LOCAL ILightManager
    {
    public:
        virtual ~ILightManager() = default;

        virtual bool Init() = 0;
        virtual bool Update() = 0;
        virtual bool Render() = 0;
        virtual bool Quit() = 0;
    };
}

#endif
