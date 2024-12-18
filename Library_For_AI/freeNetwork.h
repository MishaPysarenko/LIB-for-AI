#pragma once
#include "Graf.h"
#include <algorithm> // ��� std::find
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
		void Test()override;
		void CreateNetwork(size_t amountInVertex, size_t amountOutVertex) override;
		void CreateNetwork(std::string nameFile)override;
		std::list<NWDT> Computation(std::list<NWDT> vaules) override;
		void SaveNetwork() override;
		~freeNetwork()
		{
			SaveNetwork();
		}
		freeNetwork(std::string nameFile, howOpen typeConvert)
		{
			this->typeConvert = typeConvert;
			nameProjectFile = nameFile;
		}
	};
}