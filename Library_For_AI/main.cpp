#include "AI.h"

int main()
{
	ai::AI graf("PERCEPTRON2x5x2"/*, ai::PERCEPTRON*/);
	//graf.CreateNetwork(2,2);
	std::list<bool> v = { 1, 1 };
	auto res = graf.Computation(v);
	return 0;
}