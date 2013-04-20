#ifndef INC_ADVANCED2D_A2DLIST_HPP
#define INC_ADVANCED2D_A2DLIST_HPP

#include <list>
using std::list;

namespace Advanced2D
{
    // Temporary
    // TODO: define own data structure depending platform
    template<class T>
    class A2DList
        : public list<T>
    {
    };
}; // namespace
#endif //INC_ADVANCED2D_A2DLIST_HPP