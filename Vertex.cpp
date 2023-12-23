#include "Graph.h"

unsigned int Graph::Vertex::getAmountEdges()
{
	return ListVertex.size();
}

//void Graph::Vertex::addEdges(Vertex* newVerte1, Vertex* newVertex2, int weightEdges)
//{
//	edgesPoint = new Edges;
//	edgesPoint->nextVertex = newVertex2;
//	edgesPoint->weightEdges = weightEdges;
//	edgesPoint->indexEdges = std::to_string(ListVertex.size()) + ":" + newVerte1->nameVertex + "-" + newVertex2->nameVertex;
//	ListVertex.push_back(edgesPoint);
//	newVerte1->ListVertex.push_back(edgesPoint);
//
//
//
//	std::cout << "addEdges" << '\n';
//}

Graph::Vertex::Edges* Graph::Vertex::addEdges(Vertex* newVerte1, Vertex* newVertex2, int weightEdges = 0)
{
	edgesPoint = new Edges;
	edgesPoint->nextVertex = newVertex2;
	edgesPoint->weightEdges = weightEdges;
	edgesPoint->indexEdges = /*std::to_string(ListVertex.size()) + ":" +*/ newVerte1->nameVertex + "-" + newVertex2->nameVertex;
	ListVertex.push_back(edgesPoint);
	newVerte1->ListVertex.push_back(edgesPoint);

	std::cout << "addEdges" << '\n';

	return edgesPoint;
}

void Graph::Vertex::deleteEdges(Edges* deletedEdges)
{
	ListVertex.remove(deletedEdges);
	delete deletedEdges;
	//nameVertex--;
}
