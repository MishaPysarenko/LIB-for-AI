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
		long double (*activationFunc)(long double);
		
		Vertex(long double (*activationFuncPtr)(long double) = nullptr, unsigned long long int iterFunc = 0);
		
		long double ActivationFunc(long double value, long double(*activationFunc)(long double) = nullptr);

		//������ ������� ��� ���
		std::string indexVertex;

		//���� ��� ���������� �������� ����� 
		std::shared_ptr<std::list<std::shared_ptr<Edges>>> listEdges;

		unsigned long long int counterPrt;
		unsigned long long int iterFunc;
	};
}