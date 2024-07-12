#include "AI.h"
#include "AISpace.h"

#include <cstdlib>//для генерации рандомных чисел
#include <ctime>
#include <chrono>//для времени, название лог файла
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