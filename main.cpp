#include "Graph.h"

int main()
{
	Graph graph;
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();

	graph.vertexBinding("1");
	graph.vertexBinding("2");

	graph.vertexBinding("1.0");
	graph.vertexBinding("1");

	graph.vertexBinding("1.1");

	graph.connectNodes("1.1", "1");

	graph.showAllVertex();
}