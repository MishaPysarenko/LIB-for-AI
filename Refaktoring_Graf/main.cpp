#include "Graf.h"

int main()
{
	Graf graf;
	graf.CreateNetwork(3, 1);
	std::list<bool> vaule1 = {0,0,0};
	std::list<bool> vaule2 = {0,0,1};
	std::list<bool> vaule3 = {0,1,0};
	std::list<bool> vaule4 = {0,1,1};
	std::list<bool> vaule5 = {1,0,0};
	std::list<bool> vaule6 = {1,0,1};
	std::list<bool> vaule7 = {1,1,0};
	std::list<bool> vaule8 = {1,1,1};
	int chek = 0;
	unsigned long long int amountIter = 0;
	graf.Training3(0);
	while (chek < 8)
	{
		amountIter++;
		if (graf.Computation(vaule1) == 0)
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
		if (graf.Computation(vaule2) == 0)
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
		if (graf.Computation(vaule3) == 0)
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
		if (graf.Computation(vaule4) == 0)
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
		if (graf.Computation(vaule5) == 0)
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
		if (graf.Computation(vaule6) == 0)
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
		if (graf.Computation(vaule7) == 0)
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
		if (graf.Computation(vaule8) == 1)
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