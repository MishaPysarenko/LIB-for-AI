#pragma once
#include "Edges.h"

#include <string>
#include <list>//���� ��� ���������� �������� ����� 
#include <memory>//����� ���������

namespace ai
{
	struct Edges;

	class Vertex
	{
	public:
		bool (*activationFunc)(long double);
		Vertex(bool (*activationFuncPtr)(long double) = nullptr, unsigned long long int iterFunc = 0);
		//������ ������� ��� ���
		std::string indexVertex;
		//���� ��� ���������� �������� ����� 
		std::shared_ptr<std::list<std::shared_ptr<Edges>>> listEdges;
		bool ActivationFunc(long double value, bool(*activationFunc)(long double) = nullptr);
		//
		unsigned long long int counterPrt;

		bool value;

		unsigned long long int iterFunc;
	};
}