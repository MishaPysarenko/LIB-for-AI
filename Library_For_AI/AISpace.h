#pragma once
#include "Vertex.h"
#include "Edges.h"
#include "DataConvektorFuntion.h"

#include <memory>//умные указатели
#include <unordered_map>//хеш-таблица для сохранения индексов узлов
#include <fstream>//для сохраниния и записи с файла данных о графе для оптимизации большых обьемов данных
#include <sstream>
#include <cmath>
#include <filesystem>

#include <iostream>

namespace ai
{
	enum frame
	{
		PERCEPTRON,
		FREENETWORK
	};

	enum howOpen
	{
		DATA_DATA = 1,
		DATA_FILE = 2,
		FILE_DATA = 3,
		FILE_FILE = 4,
	};




	//для генерации рамдомных значений в диапазоне, по умолнанию 1, -1
	long double RandomValue(long double localMax = 1, long double localMin = -1);

	//возвращение нынешнего времени компьютера
	std::string GetLocalTime();

	//для создания комбинации на основе её номера комбинации, количестве нейронов, количества функций активации 
	std::vector<int> CreateCombination(int k, int n, int m);

	//функция на определение все ли в списке значения равны
	bool areAllValuesEqual(const std::list<float>& myList);
}
