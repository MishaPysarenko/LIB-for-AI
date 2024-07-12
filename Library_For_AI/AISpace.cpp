#include "AI.h"
#include "AISpace.h"

#include <cstdlib>//��� ��������� ��������� �����
#include <ctime>
#include <chrono>//��� �������, �������� ��� �����
namespace ai
{
    std::vector<ActivationFunction> activationFunctions =
    { StepActivationFunctionBig05, StepActivationFunctionLess05 };

    bool StepActivationFunctionBig05(long double value)
    {
        if (value <= 0.5)
            return false;
        return true;
    }

    bool StepActivationFunctionLess05(long double value)
    {
        if (value >= 0.5)
            return false;
        return true;
    }

	long double RandomValue(long double localMax, long double localMin)
	{
		double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; // ��������� ��������� ������� ����� [0, 1)
		return localMin + (randomFraction * (localMax - localMin)); // ��������� ����� � �������� ���������
	}

	std::string GetLocalTime()
	{
		//��� ��������� ��������� �����
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// �������� ������� �����
		auto now = std::chrono::system_clock::now();

		// ����������� ����� � ��������� �����
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		// ���������� localtime_s ��� ����������� �������������� �������
		std::tm tm_time;
		localtime_s(&tm_time, &now_time);

		// ����������� ����� � ������
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H-%M-%S", &tm_time);
		std::string LocalTime = buffer;
		return LocalTime;
	}
    // ������� ��� �������� ���������� �� ������, ���������� ���������� � ���������� ����������
    std::vector<int> CreateCombination(int k, int n, int m) {
        std::vector<int> combination;

        // ��������� ������������ �������� ������ ����������
        int maxK = std::pow(m , n) - 1;

        // ���� ����� ���������� ������ ������������� ��������, ������������� ��� � ������������ ��������
        if (k > maxK) {
            k = maxK;
        }

        // ���� ����� ���������� �� ������ ������ ����
        while (k > 0) {
            // �������� �������� ���������� �������
            int digit = k % m;

            // ��������� �������� ������� � ����������
            combination.push_back(digit);

            // ����� ����� ���������� �� ��������� ������� ���������
            k /= m;
        }

        // ��������� ���������� ������, ���� ����������
        while (combination.size() < n) {
            combination.push_back(0);
        }

        // ���������� ���������� ����������
        return combination;
    }

    bool areAllValuesEqual(const std::list<float>& myList) {
        if (myList.empty()) {
            return false; // ������ ������ ��������� ��� ���������� ������ ��������
        }

        float firstValue = myList.front();
        for (const float& value : myList) {
            if (value != firstValue) {
                return false;
            }
        }
        return true;
    }
}