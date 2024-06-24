#pragma once
#include "Graf.h"
namespace ai
{
	class freeNetwork : public Graf
	{
		std::shared_ptr<StorageCellForComputation> cellForCompulation;
		//----------------------------------------------------------------------------------------------
		//���-������� ��� ���������� ������������� ��������
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapInterVertex;
		//���-������� ��� ���������� ������� ��������
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapInVertex;
		//���-������ ��� ���������� �������� ��������
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapOutVertex;
		//���-������� ��� ���������� ���� ��������
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapVertex;
		//���-������� �������� ���������� ����� ��� ������� �������
		std::unordered_map<std::string, std::shared_ptr<StorageCellForComputation>> valueListEdges;
		//----------------------------------------------------------------------------------------------
		//������� �����
		void DeleteEdges(std::string nameVertex, std::string nameEdges);
		//���������� �����
		void AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges);
		//��������� ���� ����� � ���� ��������
		void EditWeightEdges(std::string nameEdges, long double weightEdges);
		//----------------------------------------------------------------------------------------------
		//��������� ����� ������� ������
		void AddInVertex();
		//��������� ����� �������� ������
		void AddOutVertex();
		//��������� ����� ������������� ������ ����� ����� �������
		void AddVertex(std::string vertexConnected, std::string vertexAttached);
		//��������� ����� ������������� ������
		void AddVertex();
		//������� ������������� ������
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