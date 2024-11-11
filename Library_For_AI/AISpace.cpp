#include "AI.h"
#include "AISpace.h"

#include <cstdlib>//��� ��������� ��������� �����
#include <ctime>
#include <chrono>//��� �������, �������� ��� �����
namespace ai
{
    std::vector<ActivationFunction> activationFunctions =
    { StepActivationFunctionBig05, StepActivationFunctionLess05, TransferWithoutChangeActivationFunction };

    std::vector<DataConvertFunc> ConvertFunctions =
    { DataFileConverter,  DataBlockConverter };

    std::list<NWDT> DataFileConverter(std::any data, int maxBlocks)
    {
        std::string nameFile = std::any_cast<std::string>(data);
        std::ifstream file(nameFile, std::ios::binary);
        std::list<NWDT> doubles;

        if (!file)
            return doubles;

        const std::size_t blockSize = sizeof(NWDT);
        std::vector<char> buffer(blockSize);
        unsigned int blocksRead = 0;
        std::streamsize bytesRead;
        double value;
        while (file.read(buffer.data(), blockSize) && blocksRead < maxBlocks) {
            bytesRead = file.gcount();
            if (bytesRead == blockSize) {
                std::memcpy(&value, buffer.data(), blockSize);
                doubles.push_back(value);
            }
            else {
                std::vector<char> incompleteBlock(blockSize, 0);
                std::memcpy(incompleteBlock.data(), buffer.data(), bytesRead);

                std::memcpy(&value, incompleteBlock.data(), blockSize);
                doubles.push_back(value);
                break;
            }
            ++blocksRead;
        }
        return doubles;
    }

    std::list<NWDT> DataBlockConverter(std::any data, int maxBlocks)
    {
        std::vector<char> blockData = std::any_cast<std::vector<char>>(data);
        std::list<NWDT> doubles;

        const std::size_t blockSize = sizeof(NWDT);
        unsigned int blocksRead = 0;
        std::streamsize bytesRead;
        double value;
        std::size_t totalSize = blockData.size();
        std::size_t currentPos = 0;

        while (currentPos + blockSize <= totalSize && blocksRead < maxBlocks) {
            std::vector<char> buffer(blockData.begin() + currentPos, blockData.begin() + currentPos + blockSize);
            std::memcpy(&value, buffer.data(), blockSize);
            doubles.push_back(value);

            currentPos += blockSize;
            ++blocksRead;
        }

        if (currentPos < totalSize && blocksRead < maxBlocks) {
            std::size_t remainingBytes = totalSize - currentPos;
            std::vector<char> incompleteBlock(blockSize, 0);
            std::memcpy(incompleteBlock.data(), blockData.data() + currentPos, remainingBytes);

            std::memcpy(&value, incompleteBlock.data(), blockSize);
            doubles.push_back(value);
        }

        return doubles;
    }

    NWDT StepActivationFunctionBig05(NWDT value)
    {
        if (value <= 0.5)
            return 0;
        return 1;
    }

    NWDT StepActivationFunctionLess05(NWDT value)
    {
        if (value >= 0.5)
            return 0;
        return 1;
    }

    NWDT TransferWithoutChangeActivationFunction(NWDT value)
    {
        return value;
    }

    NWDT ActivationFunctionShortTermMemory(NWDT value)//��� ���� ����������
    {
        // ������������� �������, ������� ���������� ���������� ��������
        static long double previousValue = 0.0;  // ����������� ���������� ��� �������� �������� ��������
        long double alpha = 0.1;  // ����������� �����������

        // ���������� ������� ��������, ��������� ����������
        long double result = alpha * value + (1 - alpha) * previousValue;

        // ��������� ������� ��������
        previousValue = result;

        return result;
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