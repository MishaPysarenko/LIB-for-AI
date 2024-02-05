#pragma once
#include "Edges.h"
#include "Vertex.h"

//#include <list>//лист для сохранения индексов ребер 
#include <unordered_map>//хеш-таблица для сохранения индексов узлов
#include <algorithm>//алгоритм поиска
#include <vector>
#include <string>//для индексации узлов. Входние будут позначаться как - "1.порядковый номер". Выходные как - "-1.порядковый номер". Промежуточные как - "0.порядковый номер"
				 //для индексации ребер. Будут позначаться как - "Индекс узла с которого идет - Индекс узла в который идет"
#include <fstream>//для сохраниния и записи с файла данных о графе для оптимизации большых обьемов данных

#include <cstdlib>//для генерации рандомных чисел
#include <ctime>

#include <iostream>//удалить после отладки

struct StorageCell
{
	long double weight;
	unsigned int amoutnTry;
};

class Graf
{
private:
	Vertex *vertex;
	Edges *edges;
	
	unsigned long long int amountVertex = 0;//количество узлов, для статистики
	unsigned long long int amountOutVertex = 0;
	unsigned long long int amountEdges = 0;//количество ребер, для статистики

	std::unordered_map<std::string, Vertex*> heshMapVertex;//хеш-таблица для индексации всех нейронов
	std::unordered_map<std::string, Vertex*> heshMapInVertex;//хеш-таблица для индексации входных нейронов
	std::unordered_map<std::string, Vertex*> heshMapOutVertex;//хеш-таблца для индексации выходный нейронов

	std::unordered_map<std::string, long double> valueListEdges;//хеш-таблица значений множителей ребер для каждего нейрона
	//------------------------------------------------------------
	//Все что связаное в ребрами
	//------------------------------------------------------------
	std::unordered_map<std::string, Edges*> heshMapEdges;//хеш-таблица для индексации ребер

	void DeleteEdges(std::string nameVertex, std::string nameEdges);//Удаления ребра
	void AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges);//Добавления ребра
	void EditWeightEdges(std::string nameEdges, long double weightEdges);//Изменения веса ребра у сязи нейронов
	//------------------------------------------------------------
	//Все что связаное в нейронами/узлами
	//------------------------------------------------------------
	void AddInVertex();//добоврения узла как корня, или входного нейрона
	void AddOutVertex();//добовления узла как выходного нейрона
	void AddVertex();//добовления узла как промежуточного нейрона
	void DeleteVertex(std::string nameVertex);//удаления вершины по имени
	//------------------------------------------------------------
	//Все что связаное с вычислением и обучением 
	//------------------------------------------------------------
	
	//хеш-таблица для индексации ребер которые себя хорошо показали в предедущих итерация или на тренерованные
	std::unordered_map<std::string, std::list<StorageCell*>*> heshMapTrainingEdges;

	std::list<StorageCell*> *listStorageCell;
	Edges *beforeEdges;
	std::string nameEdges;
	StorageCell *cell;

	unsigned long long int amountTraing = 0;
	unsigned int amountGoodTry = 0;

	
public:
	~Graf();
	Graf();
	void CreateNetwork(unsigned long long int amountInVertex, unsigned long long int amountOutVertex);
	void Training1();
	void Training2(bool result);
	void Training3(bool result);
	bool Computation(std::list<bool> vaules);
};

