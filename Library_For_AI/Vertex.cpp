#include "Vertex.h"

ai::Vertex::Vertex(bool(*activationFuncPtr)(long double), unsigned long long int iterFunc) : activationFunc(activationFuncPtr)
{
    listEdges = std::make_shared<std::list<std::shared_ptr<Edges>>>();
    this->iterFunc = iterFunc;
    counterPrt = 0;
}

bool ai::Vertex::ActivationFunc(long double value, bool(*activationFunc)(long double))
{
    // Проверяем, установлен ли указатель на функцию
    if (this->activationFunc != nullptr)
    {
        // Вызываем переданную функцию с переданным значением
        return this->activationFunc(value);
    }
    else
    {
        if (value <= 0.5)
            return false;
        return true;
    }
}
