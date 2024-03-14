#pragma once
#include "Vertex.h"

#include <string>
#include <memory>//умные указатели
namespace ai
{
	class Vertex;

	struct Edges
	{
		std::shared_ptr<Vertex> nextVertex;
		//индекс ребра или имя
		std::string indexEdges;
		//вес ребра, множитель
		long double weightEdges;
	};
}