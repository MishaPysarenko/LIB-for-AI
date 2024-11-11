#pragma once
#include "Vertex.h"
#include "Edges.h"
#include "DataConvektorFuntion.h"

#include <memory>//����� ���������
#include <unordered_map>//���-������� ��� ���������� �������� �����
#include <fstream>//��� ���������� � ������ � ����� ������ � ����� ��� ����������� ������� ������� ������
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




	//��� ��������� ��������� �������� � ���������, �� ��������� 1, -1
	long double RandomValue(long double localMax = 1, long double localMin = -1);

	//����������� ��������� ������� ����������
	std::string GetLocalTime();

	//��� �������� ���������� �� ������ � ������ ����������, ���������� ��������, ���������� ������� ��������� 
	std::vector<int> CreateCombination(int k, int n, int m);

	//������� �� ����������� ��� �� � ������ �������� �����
	bool areAllValuesEqual(const std::list<float>& myList);
}
