#pragma once
#include "freeNetwork.h"
#include "perceptron.h"

namespace ai
{

	enum frame
	{
		PERCEPTRON,
		FREENETWORK
	};

	class AI
	{
		std::string nameProjectFile;
		std::string nameProjectLogFile;
		
		std::shared_ptr<Graf> ai;

		void Initialization(frame type);

		bool doCreate = 0, doNamePrj = 0;

		void CreateNetwork(std::string nameFile, 
			bool (*activationFuncPtr)(long double) = nullptr,
			bool(*activationOutFuncPtr)(long double) = nullptr);
	public:

		void CreateNetwork(size_t amountInVertex, size_t amountOutVertex, 
			bool (*activationFuncPtr)(long double) = nullptr,
			bool(*activationOutFuncPtr)(long double) = nullptr);

		std::list<bool> Computation(std::list<bool> vaules);

		void DatasetTraining(std::string nameFile, float percent);

		AI(std::string nameProject, frame type);

		AI(std::string AIFile,bool (*activationFuncPtr)(long double) = nullptr,bool(*activationOutFuncPtr)(long double) = nullptr);

		void SaveNetwork();
	};
}