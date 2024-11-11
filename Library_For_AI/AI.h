#pragma once
#include "freeNetwork.h"
#include "perceptron.h"
#include "LogManager.h"
namespace ai
{
	class AI
	{
		std::string nameProjectFile;

		frame typeArchitecture;
		howOpen openingType;

		std::shared_ptr<Graf> ai;
		std::shared_ptr<Graf> tryAi;
		std::shared_ptr<LogManager> log;

		unsigned int amountIn;
		unsigned int amountOut;
		bool doCreate = 0, doNamePrj = 0;

		void Initialization(frame typetype, howOpen Convert);
		std::shared_ptr<Graf> Initialization();

		void CreateNetwork(std::string nameFile);

		float testCycle(std::list<std::list<NWDT>> DataSetList, std::list<std::list<NWDT>> Answer);
		float testCycle(std::shared_ptr<Graf>, std::list<std::list<NWDT>> DataSetList, std::list<std::list<NWDT>> Answer);

		void DataSetFolder(std::string nameFolder, std::list<std::list<NWDT>> & Data);
		void DataSetFile(std::string nameFile, std::list<std::list<NWDT>>& Data);

		std::list<NWDT> DataFileConverter(std::string nameFile, int maxBlocks = 0);
		std::list<NWDT> DataBlockConverter(std::vector<char> data, int maxBlocks = 0);
	public:
		void CreateNetwork(size_t amountInVertex, size_t amountOutVertex);

		std::list<NWDT> Computation(std::list<NWDT> vaules);

		void DatasetTraining( std::string dataIn, std::string dataOut, float percent, howOpen type = ai::howOpen::DATA_DATA);

		void Logging();

		void Test();

		void SaveNetwork();

		std::string getNameProject()
		{
			return nameProjectFile;
		}

		void SelectionOfWeights(bool result)
		{
			ai->SelectionOfWeights(result);
		}

		AI(std::string nameProject, frame type, howOpen typeConvert);
		AI(std::string AIFile);
	};
}