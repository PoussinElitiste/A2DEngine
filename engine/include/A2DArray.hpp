#ifndef INC_ADVANCED2D_A2DARRAY_HPP
#define INC_ADVANCED2D_A2DARRAY_HPP

#include <vector>
using std::vector;

namespace Advanced2D
{
    // Temporary
    // TODO: define own data structure depending platform
    template<class T>
    class A2DArray
        : public vector<T>
    {
    };
}; // namespace
#endif //INC_ADVANCED2D_A2DARRAY_HPP