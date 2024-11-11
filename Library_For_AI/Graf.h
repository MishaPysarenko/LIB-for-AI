#pragma once

#include "AISpace.h"

namespace ai
{
	class Graf
	{
	public:
		struct StorageCell
		{
			long double weight;
			unsigned int amoutnTry;
		};

		struct StorageCellForComputation
		{
			long double value;
			unsigned long long int amountOfCalculations;
		};

		struct StorageMinMax
		{
			long double min;
			long double max;
		};

		std::shared_ptr<std::list<StorageCell>> listStorageCell;
		std::shared_ptr<Edges> beforeEdges;
		std::string nameEdges;
		std::shared_ptr<StorageCell> cell;

		//���-������� ��� ���������� ����� ������� ���� ������ �������� � ���������� �������� ��� �� �������������
		std::unordered_map<std::string, std::shared_ptr<std::list<StorageCell>>> heshMapTrainingEdges;

		std::string nameProjectFile;
		std::shared_ptr<Vertex> vertex;
		std::shared_ptr<Edges> edges;

		unsigned int amountIn;
		unsigned int amountOut;

		unsigned long long int amountGoodTry = 0;

		howOpen typeConvert;

		//���-������� ��� ���������� �����
		std::unordered_map<std::string, std::shared_ptr<Edges>> heshMapEdges;
		
		//���-������� �������� ���������� ����� ��� ������� �������
		std::unordered_map<std::string, std::shared_ptr<StorageCellForComputation>> valueListEdges;

		//�������� �������� ���� �� ����������
		virtual void CreateNetwork(size_t amountInVertex, size_t amountOutVertex)
		{}
		
		//�������� �������� ���� �� �����
		virtual void CreateNetwork(std::string nameFile)
		{}
		
		//���������� �������� ����
		virtual std::list<NWDT> Computation(std::list<NWDT> vaules)
		{
			std::list<NWDT> res;
			return res;
		}
		
		//----------------------------------------------------------------------------------------
		//������������ ���� ����������� �� ������� ��������� ����������
		void SummarizeWeightSelection()
		{
			std::unordered_map<std::string, std::shared_ptr<std::list<StorageCell>>> temp;
			for (const auto& pair : heshMapTrainingEdges)
			{
				cell = std::make_shared<StorageCell>();
				listStorageCell = std::make_shared<std::list<StorageCell>>();
				long double value = 0;
				unsigned int iter = 0;
				for (const auto& element : *pair.second)
				{
					value += element.weight;
					iter += element.amoutnTry;
				}
				value = value / iter;
				EditWeightEdges(pair.first, value);
				cell->weight = value;
				if (iter < 10)
					cell->amoutnTry = 1;
				else
					cell->amoutnTry = 10;
				listStorageCell->push_back(*cell);
				temp[pair.first] = listStorageCell;
			}
			heshMapTrainingEdges.clear();
			heshMapTrainingEdges = temp;
			temp.clear();
		}
		
		//������ � ����� ������� ����� �� ����������� ������������ ������� 
		void SelectionOfWeights(bool result)
		{
			valueListEdges.clear();//�������� �������� ��� �������� 
			if (result)
			{
				amountGoodTry++;
				if (nameEdges == "")
				{
					return;
				}
				auto tempEdges = heshMapEdges.find(nameEdges);
				cell = std::make_shared<StorageCell>();
				if (heshMapTrainingEdges.find(nameEdges) != heshMapTrainingEdges.end())
				{
					auto goodEdges = heshMapTrainingEdges.find(nameEdges);
					cell->weight = tempEdges->second->weightEdges;
					cell->amoutnTry = amountGoodTry;
					goodEdges->second->push_back(*cell);
				}
				else
				{
					listStorageCell = std::make_shared<std::list<StorageCell>>();
					//auto goodEdges = heshMapTrainingEdges.find(nameEdges);//��������� ������ ���
					cell->weight = tempEdges->second->weightEdges;
					cell->amoutnTry = amountGoodTry;
					listStorageCell->push_back(*cell);
					heshMapTrainingEdges[nameEdges] = listStorageCell;
				}
			}
			else
			{
				amountGoodTry = 0;
				auto randomIter = std::next(heshMapEdges.begin(), std::rand() % heshMapEdges.size());//������ ���������� �����
				EditWeightEdges(randomIter->first, RandomValue());//����� ���� � ����� �� ��������� �������� � �������� �� -1 �� 1
				nameEdges = randomIter->first;//������ ����� ������� ��������
			}
		}

		//float CollisionOfWeights(std::list<std::list<NWDT>> DataSetList, std::list<std::list<NWDT>> Answer)
		//{
		//	float percentResult = 0;
		//	float counter = 0;
		//	bool isNotEnd = true;
		//	for (std::list<std::list<NWDT>>::iterator data = DataSetList.begin(), 
		//		answer = Answer.begin(); isNotEnd ;data++, answer++)
		//	{
		//		auto temp = Computation(*data);
		//		if (temp == *answer)
		//		{
		//			counter++;
		//		}
		//		else
		//		{
		//			counter = 0;
		//			answer = Answer.begin();
		//			data = DataSetList.begin();
		//		}
		//		//����� �� ��������� ���� ��� ���������
		//		if (counter == DataSetList.size())
		//		{
		//			isNotEnd = false;
		//		}
		//	}
		//}
		
		//----------------------------------------------------------------------------------------

		void ClearMapTraing() {
			heshMapTrainingEdges.clear();
		}

		//���������� ���������� �������� � �� ������� ��� ���� ��������� ����
		virtual unsigned int CounterCombination()
		{
			return 0;
		}
		
		//��������� ����������� �� ������ ���������� ����������� ��������
		virtual void TryArchitecture(unsigned int amountVertex)
		{}

		virtual void EditAtckFunk(unsigned int numberCombination)
		{}
		
		//��������� ���� �����(�������� �����)
		virtual void EditWeightEdges(std::string nameEdges, long double weightEdges)
		{}
		
		//���������� �������� ���� � ����
		virtual void SaveNetwork()
		{}
		
		//���������� �������� ���� � ���� � �������� ������
		virtual void SaveNetwork(std::string nameFile)
		{}
		
		//���������� � ������� ���������� � ������ ������� � ���� � ���� � �����
		virtual void Show() {
		};
		
		//�������� ��� ������� � ����� 
		virtual void Clear()
		{}
		
		//������� ����� ��� ������ ��������� 
		virtual void Test(){
		}

		Graf(std::string nameFile, howOpen typeConvert)
		{
			this->typeConvert = typeConvert;
			nameProjectFile = nameFile;
		}
		Graf()
		{}
		~Graf()
		{
			SaveNetwork();
		}
	};
}