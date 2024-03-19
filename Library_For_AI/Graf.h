#pragma once
#include "Vertex.h"
#include "Edges.h"
#include <memory>//умные указатели
#include <unordered_map>//хеш-таблица для сохранения индексов узлов
#include <fstream>//для сохраниния и записи с файла данных о графе для оптимизации большых обьемов данных
#include <sstream>

#include <iostream>
namespace ai
{
	long double RandomValue(long double localMax = 1, long double localMin = -1);
	std::string GetLocalTime();

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
		std::string nameProjectLogFile;
		std::shared_ptr<Vertex> vertex;
		std::shared_ptr<Edges> edges;

		unsigned long long int amountGoodTry = 0;
		unsigned long long int counterForAddVertex = 0;
		unsigned long long int amountTraing = 0;
		unsigned long long int counterTraing = 0;

		bool(*activationFuncPtr)(long double) = nullptr;
		bool(*activationOutFuncPtr)(long double) = nullptr;

		//хеш-таблица для индексации ребер
		std::unordered_map<std::string, std::shared_ptr<Edges>> heshMapEdges;
		//хеш-таблица значений множителей ребер для каждего нейрона
		std::unordered_map<std::string, std::shared_ptr<StorageCellForComputation>> valueListEdges;

		virtual void CreateNetwork(size_t amountInVertex, size_t amountOutVertex,bool (*activationFuncPtr)(long double) = nullptr,bool(*activationOutFuncPtr)(long double) = nullptr)
		{}
		virtual void CreateNetwork(std::string nameFile,bool (*activationFuncPtr)(long double) = nullptr,bool(*activationOutFuncPtr)(long double) = nullptr)
		{}
		virtual std::list<bool> Computation(std::list<bool> vaules)
		{
			std::list<bool> res;
			return res;
		}
		void SelectionOfWeights(bool result)
		{
			counterTraing++;
			counterForAddVertex++;//счетчик для добовление нейрона 
			valueListEdges.clear();//очистить значение для нейронов 
			if (result)
			{
				amountGoodTry++;
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
				if (amountTraing >= 100)
				{
					amountTraing = 0;
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
			}
			amountTraing++;
			SaveNetwork();
		}
		virtual void PercentageTraining(unsigned int percentage)
		{}
		virtual void EditWeightEdges(std::string nameEdges, long double weightEdges)
		{}
		virtual void Logging(std::string nameProjectFile)
		{}
		virtual void SaveNetwork()
		{}
		Graf(std::string nameFile, std::string nameLogFile)
		{
			nameProjectFile = nameFile;
			nameProjectLogFile = nameLogFile;
		}
		Graf()
		{}
	};
}