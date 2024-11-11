#include "AI.h"
#include "AISpace.h"

#include <cstdlib>//для генерации рандомных чисел
#include <ctime>
#include <chrono>//для времени, название лог файла
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

    NWDT ActivationFunctionShortTermMemory(NWDT value)//ещё надо доработать
    {
        // Активационная функция, которая запоминает предыдущее значение
        static long double previousValue = 0.0;  // Статическая переменная для хранения прошлого значения
        long double alpha = 0.1;  // Коэффициент сглаживания

        // Сглаживаем текущее значение, используя предыдущее
        long double result = alpha * value + (1 - alpha) * previousValue;

        // Обновляем прошлое значение
        previousValue = result;

        return result;
    }

	long double RandomValue(long double localMax, long double localMin)
	{
		double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; // Генерация случайной дробной части [0, 1)
		return localMin + (randomFraction * (localMax - localMin)); // Генерация числа в заданном диапазоне
	}

	std::string GetLocalTime()
	{
		//для генерации рандомных весов
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// Получаем текущее время
		auto now = std::chrono::system_clock::now();

		// Преобразуем время в локальное время
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		// Используем localtime_s для безопасного форматирования времени
		std::tm tm_time;
		localtime_s(&tm_time, &now_time);

		// Форматируем время в строку
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H-%M-%S", &tm_time);
		std::string LocalTime = buffer;
		return LocalTime;
	}
    // Функция для создания комбинации по номеру, количеству переменных и количеству комбинаций
    std::vector<int> CreateCombination(int k, int n, int m) {
        std::vector<int> combination;

        // Вычисляем максимальное значение номера комбинации
        int maxK = std::pow(m , n) - 1;

        // Если номер комбинации больше максимального значения, устанавливаем его в максимальное значение
        if (k > maxK) {
            k = maxK;
        }

        // Пока номер комбинации не станет равным нулю
        while (k > 0) {
            // Получаем значение очередного разряда
            int digit = k % m;

            // Добавляем значение разряда в комбинацию
            combination.push_back(digit);

            // Делим номер комбинации на основание системы счисления
            k /= m;
        }

        // Дополняем комбинацию нулями, если необходимо
        while (combination.size() < n) {
            combination.push_back(0);
        }

        // Возвращаем полученную комбинацию
        return combination;
    }

    bool areAllValuesEqual(const std::list<float>& myList) {
        if (myList.empty()) {
            return false; // Пустой список считается как содержащий равные элементы
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