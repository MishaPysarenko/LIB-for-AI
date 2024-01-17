#pragma once
#include <string>
#include "Vertex.h"

class Vertex;

class Edges 
{
public:
	Vertex* nextVertex;
	std::string indexEdges;//для индексации ребер
	long double weightEdges;//вес ребра, множитель
	long double tempValue;//временное значение при вычесление для следущего нейрона, мб в будущем убрать
};

