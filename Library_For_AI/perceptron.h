#pragma once
#include "Graf.h"
namespace ai
{
	//Как идея "динамический перцептрон"
	//	Всё нейроны хранить
	//	Список - слоев - нейронов
	//	Компиляция будет идти последовательно по слоям
	//  Главное правило что все нейроны идут по очередно по слоям и все слои связаны только с соседними
	class perceptron : public Graf
	{
		std::list<std::list<std::shared_ptr<Vertex>>> listVertex;// Список - слоев - нейронов
		std::list<std::list<std::shared_ptr<Edges>>> listEdges;
		std::unordered_map<std::string, std::shared_ptr<Edges>> heshMapEdges;
		std::unordered_map<std::string, long double> valueListEdges;

		void EditWeightEdges(std::string nameEdges, long double weightEdges);
		void AddLayerEdges(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected, std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerAttached);
		void AddEdges(std::list<std::shared_ptr<Vertex>>::iterator vertexConnected, std::list<std::shared_ptr<Vertex>>::iterator vertexAttached, long double weightEdges);

		void AddLayerVertex();
		void AddLayerInVertex();
		void AddLayerOutVertex();
		void AddVertex(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected);
		void AddInVertex();
		void AddOutVertex();
	public:
		void CreateNetwork(size_t amountInVertex, size_t amountOutVertex, bool (*activationFuncPtr)(long double) = nullptr, bool(*activationOutFuncPtr)(long double) = nullptr) override;
		void CreateNetwork(std::string nameFile, bool (*activationFuncPtr)(long double) = nullptr, bool(*activationOutFuncPtr)(long double) = nullptr)override;
		std::list<bool> Computation(std::list<bool> vaules) override;
		void Training(bool result) override;
		void Logging(std::string nameProjectFile) override;
		void SaveNetwork() override;
		~perceptron()
		{
			SaveNetwork();
		}
		perceptron(std::string nameFile, std::string nameLogFile)
		{
			nameProjectFile = nameFile;
			nameProjectLogFile = nameLogFile;
		}
	};
}