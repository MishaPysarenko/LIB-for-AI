#include "Vertex.h"

bool Vertex::ActivationFunc(long double vaule)
{
    if(vaule < 0.5)
        return false;
    return true;
}
