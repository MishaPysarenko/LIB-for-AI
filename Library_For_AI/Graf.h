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

		std::shared_ptr<std::list<StorageCell>> listStorageCell;
		std::shared_ptr<Edges> beforeEdges;
		std::string nameEdges;
		std::shared_ptr<StorageCell> cell;

		//хеш-таблица для индексации ребер которые себя хорошо показали в предедущих итерация или на тренерованные
		std::unordered_map<std::string, std::shared_ptr<std::list<StorageCell>>> heshMapTrainingEdges;

		std::string nameProjectFile;
		std::shared_ptr<Vertex> vertex;
		std::shared_ptr<Edges> edges;

		unsigned long long int amountGoodTry = 0;

		//хеш-таблица для индексации ребер
		std::unordered_map<std::string, std::shared_ptr<Edges>> heshMapEdges;
		
		//хеш-таблица значений множителей ребер для каждего нейрона
		std::unordered_map<std::string, std::shared_ptr<StorageCellForComputation>> valueListEdges;

		//создания нейроной сети по параметрам
		virtual void CreateNetwork(size_t amountInVertex, size_t amountOutVertex)
		{}
		
		//создания нейроной сети по файлу
		virtual void CreateNetwork(std::string nameFile)
		{}
		
		//компиляция нейроной сети
		virtual std::list<bool> Computation(std::list<bool> vaules)
		{
			std::list<bool> res;
			return res;
		}
		
		//----------------------------------------------------------------------------------------
		//суммиравание всех результатов по стараму алгоритму тренировки
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
		
		//подбор и поиск удачных весов по результатам правильности ответов 
		void SelectionOfWeights(bool result)
		{
			valueListEdges.clear();//очистить значение для нейронов 
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
					//auto goodEdges = heshMapTrainingEdges.find(nameEdges);//Вероятная ошибка тут
					cell->weight = tempEdges->second->weightEdges;
					cell->amoutnTry = amountGoodTry;
					listStorageCell->push_back(*cell);
					heshMapTrainingEdges[nameEdges] = listStorageCell;
				}
			}
			else
			{
				amountGoodTry = 0;
				auto randomIter = std::next(heshMapEdges.begin(), std::rand() % heshMapEdges.size());//взятие случайного ребра
				EditWeightEdges(randomIter->first, RandomValue());//смена веса у ребра на рандомное значение в диапазое от -1 до 1
				nameEdges = randomIter->first;//запись ребра которое поменяли
			}
		}
		//----------------------------------------------------------------------------------------

		void ClearMapTraing() {
			heshMapTrainingEdges.clear();
		}

		//Количество комбинаций нейронов и их функций для этой нейронной сети
		virtual unsigned int CounterCombination()
		{
			return 0;
		}
		
		//Изменения архитектуры на основе количества добавляймых нейронов
		virtual void TryArchitecture(unsigned int amountVertex)
		{}

		virtual void EditAtckFunk(unsigned int numberCombination)
		{}
		
		//изменения веса ребра(нейроной связи)
		virtual void EditWeightEdges(std::string nameEdges, long double weightEdges)
		{}
		
		//сохраниния нейроной сети в файл
		virtual void SaveNetwork()
		{}
		
		//сохраниния нейроной сети в файл с указаным именем
		virtual void SaveNetwork(std::string nameFile)
		{}
		
		//нарисовать в консоль колицество и индекс функций в слое и слои в общем
		virtual void Show() {
		};
		
		//очистить все нейроны и связи 
		virtual void Clear()
		{}
		
		//функция теста для разных испытаний 
		virtual void Test(){
		}

		Graf(std::string nameFile)
		{
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