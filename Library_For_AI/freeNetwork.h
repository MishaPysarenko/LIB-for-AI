#pragma once
#include "Graf.h"
namespace ai
{
	class freeNetwork : public Graf
	{
		std::shared_ptr<StorageCellForComputation> cellForCompulation;
		//----------------------------------------------------------------------------------------------
		//хеш-таблица для индексации промежуточных нейронов
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapInterVertex;
		//хеш-таблица для индексации входных нейронов
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapInVertex;
		//хеш-таблца для индексации выходный нейронов
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapOutVertex;
		//хеш-таблица для индексации всех нейронов
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapVertex;
		//хеш-таблица значений множителей ребер для каждего нейрона
		std::unordered_map<std::string, std::shared_ptr<StorageCellForComputation>> valueListEdges;
		//----------------------------------------------------------------------------------------------
		//Удаляет ребро
		void DeleteEdges(std::string nameVertex, std::string nameEdges);
		//Добавления ребра
		void AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges);
		//Изменения веса ребра у сязи нейронов
		void EditWeightEdges(std::string nameEdges, long double weightEdges);
		//----------------------------------------------------------------------------------------------
		//Добавляет новый входной нейрон
		void AddInVertex();
		//Добавляет новый выходной нейрон
		void AddOutVertex();
		//Добавляет новый промежуточный нейрон между двумя другими
		void AddVertex(std::string vertexConnected, std::string vertexAttached);
		//Добавляет новый промежуточный нейрон
		void AddVertex();
		//Удаляет промежуточный нейрон
		void DeleteVertex(std::string nameVertex);

	public:
		void CreateNetwork(size_t amountInVertex, size_t amountOutVertex) override;
		void CreateNetwork(std::string nameFile)override;
		std::list<bool> Computation(std::list<bool> vaules) override;
		//void SelectionOfWeights(bool result) override;
		void Logging(std::string nameProjectFile) override;
		void SaveNetwork() override;
		~freeNetwork()
		{

		}
		freeNetwork(std::string nameFile, std::string nameLogFile)
		{
			nameProjectFile = nameFile;
			nameProjectLogFile = nameLogFile;
		}
	};
}