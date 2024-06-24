#pragma once
#include "freeNetwork.h"
#include "perceptron.h"
#include "LogManager.h"
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

		frame type;

		std::shared_ptr<Graf> ai;
		std::shared_ptr<Graf> tryAi;
		std::shared_ptr<LogManager> log;

		unsigned int amountIn;
		unsigned int amountOut;
		bool doCreate = 0, doNamePrj = 0;

		void Initialization(frame type);
		std::shared_ptr<Graf> Initialization();

		void CreateNetwork(std::string nameFile);

		float testCycle(std::string nameFile);
		float testCycle(std::shared_ptr<Graf>, std::string nameFile);

		std::vector<std::shared_ptr<Graf>> ArchitectureGenerator(std::shared_ptr<Graf> sampler, std::string nameFile);

		std::vector<std::shared_ptr<Graf>> GenerationCF(std::shared_ptr<Graf> sampler);
	public:

		std::string getNameProject();

		void SelectionOfWeights(bool res);

		void CreateNetwork(size_t amountInVertex, size_t amountOutVertex);

		std::list<bool> Computation(std::list<bool> vaules);

		void DatasetTraining(std::string nameFile, float percent);

		AI(std::string nameProject, frame type);
		AI(std::string AIFile);

		void Logging();

		void Test();

		void SaveNetwork();
	};
}