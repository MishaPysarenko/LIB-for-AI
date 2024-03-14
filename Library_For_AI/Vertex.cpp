#include "Vertex.h"

ai::Vertex::Vertex(bool(*activationFuncPtr)(long double)) : activationFunc(activationFuncPtr)
{
    listEdges = std::make_shared<std::list<std::shared_ptr<Edges>>>();
    counterPrt = 0;
}

bool ai::Vertex::ActivationFunc(long double value, bool(*activationFunc)(long double))
{
    // Проверяем, установлен ли указатель на функцию
    if (activationFunc != nullptr)
    {
        // Вызываем переданную функцию с переданным значением
        return activationFunc(value);
    }
    else
    {
        if (value <= 0.5)
            return false;
        return true;
    }
}
