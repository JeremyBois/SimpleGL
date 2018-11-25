#ifndef __TOOLS__HPP
#define __TOOLS__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

namespace simpleGL
{
    // Collection of function to manipulate stream and files.
    class SIMPLEGL_LOCAL Tools
    {
    private:
        Tools();

    public:
        Tools(Tools const&) = delete;           // C++ 11
        void operator=(Tools const&) = delete;  // C++ 11

        template<typename T> static void SafeDelete(T* &a) {delete a; a = nullptr;};
    };

    template<class Child, class Parent>
    struct Derived_from
    {
        static void constraints(Child* p) { Parent* pb = p; }
        Derived_from() { void(*p)(Child*) = constraints; }
    };
}
#endif
