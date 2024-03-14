#include "AI.h"
#include <cstdlib>//дл€ генерации рандомных чисел
#include <ctime>
#include <chrono>//дл€ времени, название лог файла
namespace ai
{
	long double RandomValue(long double localMax, long double localMin)
	{
		double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; // √енераци€ случайной дробной части [0, 1)
		return localMin + (randomFraction * (localMax - localMin)); // √енераци€ числа в заданном диапазоне
	}

	std::string GetLocalTime()
	{
		//дл€ генерации рандомных весов
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// ѕолучаем текущее врем€
		auto now = std::chrono::system_clock::now();

		// ѕреобразуем врем€ в локальное врем€
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		// »спользуем localtime_s дл€ безопасного форматировани€ времени
		std::tm tm_time;
		localtime_s(&tm_time, &now_time);

		// ‘орматируем врем€ в строку
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H-%M-%S", &tm_time);
		std::string LocalTime = buffer;
		return LocalTime;
	}
}