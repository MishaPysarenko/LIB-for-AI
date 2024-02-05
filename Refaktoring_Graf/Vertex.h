#pragma once
#include "Edges.h"
#include <string>
#include <list>//лист для сохранения индексов ребер 

class Edges;

class Vertex
{
public:
	std::string indexVertex;//для индексации нейронов
	std::list<Edges*> listEdges;//лист для сохранения индексов ребер 
	bool value;
	bool ActivationFunc(long double vaule);
};

