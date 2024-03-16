#include "AI.h"

int main()
{
	ai::AI graf("AI-PERCEPTRON.txt"/*, ai::PERCEPTRON*/);
	//graf.CreateNetwork(2,1);
	std::list<bool> v = { 1, 1 };
	auto res = graf.Computation(v);
	return 0;
}