#include "Vertex.h"

ai::Vertex::Vertex(long double(*activationFuncPtr)(long double), unsigned long long int iterFunc) : activationFunc(activationFuncPtr)
{
    listEdges = std::make_shared<std::list<std::shared_ptr<Edges>>>();
    this->iterFunc = iterFunc;
    counterPrt = 0;
}

long double ai::Vertex::ActivationFunc(long double value, long double(*activationFunc)(long double))
{
    if (value == NULL)
    {
        value = this->value;
    }
    // ���������, ���������� �� ��������� �� �������
    if (this->activationFunc != nullptr)
    {
        // �������� ���������� ������� � ���������� ���������
        return this->activationFunc(value);
    }
    else
    {
        return value;
    }
}
