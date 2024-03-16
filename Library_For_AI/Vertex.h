#pragma once
#include "Edges.h"

#include <string>
#include <list>//лист для сохранения индексов ребер 
#include <memory>//умные указатели

namespace ai
{
	struct Edges;

	class Vertex
	{
		bool (*activationFunc)(long double);
	public:
		Vertex(bool (*activationFuncPtr)(long double) = nullptr);
		//индекс нейрона или имя
		std::string indexVertex;
		//лист для сохранения индексов ребер 
		std::shared_ptr<std::list<std::shared_ptr<Edges>>> listEdges;
		bool ActivationFunc(long double value, bool(*activationFunc)(long double) = nullptr);
		//
		unsigned long long int counterPrt;

		bool value;
	};
}