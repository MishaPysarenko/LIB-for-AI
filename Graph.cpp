#include "Graph.h"

unsigned int Graph::amountVertex()
{
	return iAmountVertex;
}

Graph::Vertex* Graph::getVertex(std::string nameVertex)
{
	for (int count = 0; count < vectorVertex.size(); count++)
	{
		if (vectorVertex[count]->nameVertex == nameVertex)
		{
			return vectorVertex[count];
		}
	}
	return nullptr;
}

void Graph::showAllVertex()
{
	std::cout << vectorVertex.size() << '\n';
	for (int count = 0;count < vectorVertex.size();count++)
	{
		std::cout << vectorVertex[count]->nameVertex <<'\n';
	}

}

Graph::Graph()
{
}

Graph::~Graph()
{
	for (int count = 0; count < vectorVertex.size(); count++)
	{
		if (vectorVertex[count] == nullptr)
		{
			std::cout << "nullptr" << count << '\n';
		}
		else
		{
			std::cout << vectorVertex[count]->nameVertex << "~Graph()\n";
			delete vectorVertex[count];
		}
	}
}

void Graph::addVertex()
{
	vertex = new Vertex;
	vectorVertex.push_back(vertex);
	vertex->nameVertex = std::to_string(iAmountVertex);
	iAmountVertex++;
}

void Graph::vertexBinding(std::string nameVertex)
{
	vertex = new Vertex;
	for (int count = 0; count < vectorVertex.size(); count++)
	{
		if (vectorVertex[count]->nameVertex == nameVertex)
		{
			vectorVertex[count]->addEdges(vectorVertex[count], vertex);
			vertex->nameVertex = vectorVertex[count]->nameVertex + "." + std::to_string(vectorVertex[count]->precipitationAmount);
			vectorVertex[count]->precipitationAmount++;
			iAmountVertex++;
			vectorVertex.push_back(vertex);
			return;
		}

	}
	delete vertex;
	return;
}

void Graph::deleteVertex(std::string nameVertex)
{
	for (int count = 0; count < vectorVertex.size(); count++)
	{
		if (vectorVertex[count]->nameVertex == nameVertex)
		{
			delete vectorVertex[count];
			vectorVertex.erase(vectorVertex.begin() + count);
			iAmountVertex--;
			break;
		}
	}
}

void Graph::connectNodes(std::string nodeConnected, std::string nodeAttached, unsigned int weightEdges)
{
	int indexNodeConnected = NULL, indexNodeAttached = NULL;
	for (int count = 0; count < vectorVertex.size(); count++)
	{
		if (vectorVertex[count]->nameVertex == nodeConnected)
		{
			indexNodeConnected = count;
		}
		if (vectorVertex[count]->nameVertex == nodeAttached)
		{
			indexNodeAttached = count;
		}
		if (!(indexNodeAttached = NULL || indexNodeConnected == NULL))
		{
			break;
		}
	}
	vectorVertex[indexNodeConnected]->addEdges(vectorVertex[indexNodeConnected], vectorVertex[indexNodeAttached], weightEdges);
}
