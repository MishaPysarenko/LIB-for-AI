#include "Graph.h"

unsigned int Graph::amountVertex()
{
	return iAmountVertex;
}

Graph::Vertex* Graph::getVertex(std::string nameVertex)
{
	auto it = vectorVertex.find(nameVertex);
	if (it == vectorVertex.end()) {
		return nullptr;
	}
	else {
		return it->second;
	}
}

void Graph::showAllVertex()
{

}

void Graph::drawAllVertex()
{
	
}

//Graph::Graph()
//{
//
//}

Graph::~Graph()
{
	for (auto it = vectorVertex.begin(); it != vectorVertex.end(); ++it)
	{
		std::cout << "Key: " << it->first /*<< ", Value: " << it->second*/ << std::endl;
		if (it->second == nullptr)
		{
			std::cout << "nullptr" << '\n';
		}
		else
		{
			std::cout << it->first << "\n";
			delete it->second;
		}
	}

	std::cout << "\n\nEdges\n";

	for (auto it = heshMapEdges.begin(); it != heshMapEdges.end(); ++it)
	{
		std::cout << "Key: " << it->first /*<< ", Value: " << it->second*/ << std::endl;
		if (it->second == nullptr)
		{
			std::cout << "nullptr" << '\n';
		}
		else
		{
			std::cout << it->first << "\n";
			delete it->second;
		}
	}

	std::cout << "~Graph()\n";
}

void Graph::addVertex()
{
	vertex = new Vertex;
	vertex->nameVertex = std::to_string(iAmountVertex);
	vectorVertex[vertex->nameVertex] = vertex;//добавления в хеш-таблицу
	iAmountVertex++;
}

void Graph::vertexBinding(std::string nameVertex)
{
	vertex = new Vertex;
	auto it = vectorVertex.find(nameVertex);
	if (it == vectorVertex.end())
	{
		delete vertex; 
		return;
	}
	vertex->nameVertex = it->first + "." + std::to_string(it->second->precipitationAmount);

	auto temp = it->second->addEdges(it->second, vertex, 0);
	heshMapEdges[temp->indexEdges] = temp;//добаавления ребра в хеш-таблицу

	it->second->precipitationAmount++;
	iAmountVertex++;
	vectorVertex[vertex->nameVertex] = vertex;
}

void Graph::deleteVertex(std::string nameVertex)
{
	auto it = vectorVertex.find(nameVertex);
	if (it == vectorVertex.end()) {
		return;
	}
	else{
		delete it->second;
		vectorVertex.erase(nameVertex);
		iAmountVertex--;
	}
}

void Graph::connectNodes(std::string nodeConnected, std::string nodeAttached, unsigned int weightEdges)
{
	auto NodeConnected = vectorVertex.find(nodeConnected);
	auto NodeAttached = vectorVertex.find(nodeAttached);
	if (NodeAttached == vectorVertex.end() || NodeConnected == vectorVertex.end())
		return;
	auto temp = NodeConnected->second->addEdges(NodeConnected->second, NodeAttached->second, weightEdges);
	heshMapEdges[temp->indexEdges] = temp;
}
