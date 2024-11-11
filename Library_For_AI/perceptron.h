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
		std::unordered_map<std::string, long double> valueListEdges;

		ai::perceptron *Try = nullptr;

		void EditWeightEdges(std::string nameEdges, long double weightEdges);
		void AddLayerEdges(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected, std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerAttached);
		void AddEdges(std::list<std::shared_ptr<Vertex>>::iterator vertexConnected, std::list<std::shared_ptr<Vertex>>::iterator vertexAttached, long double weightEdges);

		void AddLayerVertex();
		void AddLayerInVertex();
		void AddLayerOutVertex();
		void AddVertex(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected, ActivationFunction func, unsigned long long int iter);
		void AddInVertex(ActivationFunction func, unsigned long long int iter);
		void AddOutVertex(ActivationFunction func, unsigned long long int iter);
	public:
		void CreateNetwork(size_t amountInVertex, size_t amountOutVertex) override;
		void CreateNetwork(std::string nameFile)override;
		std::list<NWDT> Computation(std::list<NWDT> vaules) override;
		void SaveNetwork() override;
		void SaveNetwork(std::string nameFile) override;
		unsigned int CounterCombination() override;
		void TryArchitecture(unsigned int amountVertex) override;
		void EditAtckFunk(unsigned int numberCombination) override;
		void Clear() override;
		void Show()override;
		void Test()override;
		~perceptron()
		{

		}
		perceptron(){}
		perceptron(std::string nameFile, howOpen typeConvert)
		{
			this->typeConvert = typeConvert;
			nameProjectFile = nameFile;
		}
		perceptron(const ai::perceptron& sample)
		{
			// Глубокое копирование listVertex
			for (const auto& layer : sample.listVertex) {
				std::list<std::shared_ptr<Vertex>> newLayer;
				for (const auto& vertex : layer) {
					newLayer.push_back(std::make_shared<Vertex>(*vertex));
				}
				listVertex.push_back(newLayer);
			}

			// Глубокое копирование listEdges
			for (const auto& layer : sample.listEdges) {
				std::list<std::shared_ptr<Edges>> newLayer;
				for (const auto& edge : layer) {
					newLayer.push_back(std::make_shared<Edges>(*edge));
				}
				listEdges.push_back(newLayer);
			}

			// Простое копирование остальных полей
			this->valueListEdges = sample.valueListEdges;
			this->nameEdges = sample.nameEdges;
			this->nameProjectFile = sample.nameProjectFile;
			this->heshMapEdges = sample.heshMapEdges; // Если они не содержат указателей
			this->heshMapTrainingEdges = sample.heshMapTrainingEdges; // Если они не содержат указателей
		}

	};
}