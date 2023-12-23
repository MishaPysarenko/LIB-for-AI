#include <list>//лист для сохранения индексов ребер 
#include <unordered_map>//масив для сохранения индексов узлов
#include <algorithm>//алгоритм поиска
#include <string>//для индексации узлов (замысел в том чтобы понимать чей насщядок узла и записывать число в кором будет сохранять от кого он
				 //и какой по счету, разделяя все поколения спец символом приблизительная запись "56,1,25" у узла 2 предка первый 54й второй 
				 //от первого 1й и трети то есть сам узел 25й)
#include <fstream>//для сохраниния и записи с файла данных о графе для оптимизации большых обьемов данных

#include <iostream>//удалить после отладки

class Graph
{
public:
	//--------------------
	// 
	// 
	//----------------------------------------
private:
	class Vertex//узел/вершина
	{
	public:
		//------------------------------------
		class Edges//ребро
		{
		public:
			Vertex* nextVertex;
			std::string indexEdges;//для индексации ребер
			int weightEdges;//вес ребра 
		};
		//------------------------------------
		Edges* edgesPoint;
		std::list<Edges*> ListVertex;//лист для сохранения индексов ребер 
		unsigned int getAmountEdges();
		//void addEdges(Vertex* newVerte1, Vertex* newVertex2, int weightEdges = 0);//добавления ребра
		Graph::Vertex::Edges* addEdges(Vertex* newVerte1, Vertex* newVertex2, int weightEdges);
		void deleteEdges(Edges* deletedEdges);//удаления ребра
		std::string nameVertex;//для индексации узла
		unsigned int precipitationAmount;//количество насщядков, или путей 
	};

	std::unordered_map<std::string,Vertex::Edges*> heshMapEdges;
	std::unordered_map<std::string,Vertex*> vectorVertex;

	Vertex* vertex;//корень самый первый узел
	unsigned int iAmountVertex = 0;//количество узлов
	void deleteVertex(Vertex* deletedVertex);//удаления вершины по указаелю
public:
//	Graph();//реализовать инцилизацию графа 
	~Graph();//реализовать удаления графа
	void addVertex();//добоврения вершины как корня
	void vertexBinding(std::string nameVertex);//добовления вершины к сушествующий 
	void deleteVertex(std::string nameVertex);//удаления вершины по имени
	void connectNodes(std::string nodeConnected, std::string nodeAttached, unsigned int weightEdges = 0);//связывание двух узлов графа
	unsigned int amountVertex();//определения сколько узлов в графе
	void takeTheEasiestPath();//идти по самому легкому пути
	void takeTheHardPath();//идти по самому сложному пути
	Vertex* getVertex(std::string nameVertex);//метод для возращения указателя на узел в графе 


	void drawAllVertex();
	void showAllVertex();//удалить после отладки
};