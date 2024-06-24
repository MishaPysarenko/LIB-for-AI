#pragma once
#include <functional>
#include <vector>

namespace ai
{
	using ActivationFunction = bool(*)(long double);
	bool StepActivationFunctionBig05(long double value);
	bool StepActivationFunctionLess05(long double value);
	extern std::vector<ActivationFunction> activationFunctions;
}