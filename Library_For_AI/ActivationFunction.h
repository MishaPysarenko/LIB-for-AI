#pragma once
#include <functional>
#include <vector>
#include <cstring> // Для std::memcpy
#define NWDT long double //neuron work data type или тип данных работы нейронов

namespace ai
{
	using ActivationFunction = NWDT(*)(NWDT);
	NWDT StepActivationFunctionBig05(NWDT value);
	NWDT StepActivationFunctionLess05(NWDT value);
	NWDT TransferWithoutChangeActivationFunction(NWDT value);
	NWDT ActivationFunctionShortTermMemory(NWDT value);
	extern std::vector<ActivationFunction> activationFunctions;
}