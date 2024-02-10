#include "Graf.h"

int main()
{
	std::ofstream outputFile("log.txt", std::ios::out);
	outputFile.close();
	Graf graf;
	graf.CreateNetwork(4, 1);
	std::list<bool> vaule1 = {0,0,0,0};
	std::list<bool> vaule2 = { 0,0,0,1 };
	std::list<bool> vaule3 = { 0,0,1,0 };
	std::list<bool> vaule4 = { 0,0,1,1 };
	std::list<bool> vaule5 = { 0,1,0,0 };
	std::list<bool> vaule6 = { 0,1,0,1 };
	std::list<bool> vaule7 = { 0,1,1,0 };
	std::list<bool> vaule8 = { 0,1,1,1 };
	std::list<bool> vaule9 = { 1,0,0,0 };
	std::list<bool> vaule10 = { 1,0,0,1 };
	std::list<bool> vaule11 = { 1,0,1,0 };
	std::list<bool> vaule12 = { 1,0,1,1 };
	std::list<bool> vaule13 = { 1,1,0,0 };
	std::list<bool> vaule14 = { 1,1,0,1 };
	std::list<bool> vaule15 = { 1,1,1,0 };
	std::list<bool> vaule16 = { 1,1,1,1 };
	int chek = 0;
	unsigned long long int amountIter = 0;
	graf.Training3(0);
	while (chek < 16)
	{
		amountIter++;
		if (graf.Computation(vaule1) == 0)/* { 0, 0, 0, 0 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule2) == 1) /*{ 0,0,0,1 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule3) == 1) /*{ 0,0,1,0 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule4) == 1) /*{ 0,0,1,1 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule5) == 1) /*{ 0,1,0,0 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule6) == 1) /*{ 0,1,0,1 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule7) == 1) /*{ 0,1,1,0 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule8) == 1) /*{ 0,1,1,1 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule9) == 1) /*{ 1,0,0,0 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule10) == 1) /*{ 1,0,0,1 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule11) == 1) /*{ 1,0,1,0 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule12) == 1) /*{ 1,0,1,1 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule13) == 1) /*{ 1,1,0,0 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule14) == 1) /*{ 1,1,0,1 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule15) == 1) /*{ 1,1,1,0 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
		amountIter++;
		if (graf.Computation(vaule16) == 1) /*{ 1,1,1,1 };*/
		{
			graf.Training3(1);
			chek++;
		}
		else
		{
			graf.Training3(0);
			chek = 0;
		}
	}
	std::cout << '\n' << amountIter << '\n';
	return 0;
}