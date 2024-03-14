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
		std::string nameProjectFile;
		std::string nameProjectLogFile;
		std::shared_ptr<Vertex> vertex;
		std::shared_ptr<Edges> edges;

		bool(*activationFuncPtr)(long double) = nullptr;
		bool(*activationOutFuncPtr)(long double) = nullptr;

		virtual void CreateNetwork(size_t amountInVertex, size_t amountOutVertex,bool (*activationFuncPtr)(long double) = nullptr,bool(*activationOutFuncPtr)(long double) = nullptr)
		{}

		virtual void CreateNetwork(std::string nameFile,bool (*activationFuncPtr)(long double) = nullptr,bool(*activationOutFuncPtr)(long double) = nullptr)
		{}

		virtual std::list<bool> Computation(std::list<bool> vaules)
		{
			std::list<bool> res;
			return res;
		}

		virtual void Training(bool result)
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
		{

		}
	};
}