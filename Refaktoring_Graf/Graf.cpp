#include "Graf.h"

void Graf::CreateNetwork(unsigned long long int amountInVertex, unsigned long long int amountOutVertex)
{
	for (unsigned long long int  i = 0; i < amountInVertex; i++)
	{
		AddInVertex();
	}
	for (unsigned long long int i = 0; i < amountOutVertex; i++)
	{
		AddOutVertex();
	}
	//Реализация соидинений входных и выходных нейронов
	std::srand(static_cast<unsigned int>(std::time(nullptr)));//для генерации рандомных весов
	for (unsigned long long int i = 0; i < amountInVertex; i++)
	{
		for (unsigned long long int j = amountInVertex; j < amountOutVertex + amountInVertex;j++)
		{
			double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; // Генерация случайной дробной части [0, 1)
			auto vaule = 2.0 * randomFraction - 1.0; // Масштабирование и смещение для диапазона (-1, 1)
			AddEdges("1." + std::to_string(i), "-1." + std::to_string(j), vaule);
		}
	}

	// Создаем объект ofstream и открываем файл для записи (std::ios::out)
	std::ofstream outputFile("1.txt", std::ios::out);

	for (const auto& pair : heshMapVertex) {
		outputFile << pair.first << "\n";
		for (const auto& element : pair.second->listEdges) {
			outputFile << "\t" << element->indexEdges << " " << element->weightEdges << "\n";
		}
	}

}

void Graf::Training()
{

}
//скорее всего прейдеться переделать если будут очень много выходных нейронов ибо тут все равно по списку идет, 
//надо будет как-то сделать так чтобы переходило как-то по ребрам
void Graf::Computation() 
{
	
	//Входные нейроны перебираем и даем значение для следующих нейронов
	for (const auto& pair : heshMapInVertex) {
		long double vaule = 0;
		for (const auto& element : pair.second->listEdges) {//перебираем связи
			//Сумматор и множитель одновремено 
			vaule = (pair.second->value * element->weightEdges);
			valueListEdges[element->nextVertex->indexVertex] += vaule;
		}
	
	}

	//МБ просмотреть этот цыкл, и что там у него
	//Промежуточные нейроны и их значения
	if (heshMapVertex.size() > heshMapInVertex.size() + heshMapOutVertex.size())
	{
		for (const auto& pair : heshMapVertex) {
			//перебираем из всех нейронов за исключением тех которые помеченны как входные и выходные
			if (heshMapInVertex.find(pair.first) == heshMapInVertex.end() || heshMapOutVertex.find(pair.first) == heshMapOutVertex.end()) {
				for (const auto& element : pair.second->listEdges) {//перебираем связи
					//Активируем нейрон
					pair.second->ActivationFunc(valueListEdges.find(pair.first)->second);
					//Сумматор и множитель одновремено 
					valueListEdges[pair.first] += (pair.second->value * element->weightEdges);
				}
			}
		}
	}

	//Выходные нейроны
	for (const auto& pair : heshMapOutVertex) {
		//Активируем нейрон
		std::cout << pair.second->ActivationFunc(valueListEdges.find(pair.first)->second) << '\t' << valueListEdges.find(pair.first)->second << '\n';
	}
}

Graf::~Graf()
{
	for (const auto& pair : heshMapVertex) {
		for (const auto& element : pair.second->listEdges) {//перебираем связи
			delete element;
		}
		delete pair.second;
	}
}

void Graf::DeleteEdges(std::string nameVertex, std::string nameEdges)
{
	auto temp = heshMapVertex.find(nameVertex)->second;//Находим узел из которого надо удалить связь
	
	for (const auto& element : temp->listEdges) {//перебираем и ищем связь
		if (element->indexEdges == nameEdges)//если найдено
		{
			temp->listEdges.remove(element);//удаляем из спика 
			delete element;//удаляем
		}
	}
}

void Graf::AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges)
{
	//--------------------------------------------------------------
	//временные переменные для записи узлов с хеш-таблицы
	auto tempVertexConnected = heshMapVertex.find(vertexConnected);
	auto tempVertexAttached = heshMapVertex.find(vertexAttached);
	//--------------------------------------------------------------

	edges = new Edges;//создаем новое ребро 
	edges->indexEdges = tempVertexConnected->second->indexVertex + "-" + tempVertexAttached->second->indexVertex;//даем ему имя, от двух узлов
	edges->nextVertex = tempVertexAttached->second;//записываем указатель следующего нейрона/узла 
	edges->weightEdges = weightEdges;//записываем вес ребра
	heshMapEdges[edges->indexEdges] = edges;//добавляем в хеш-таблицу ребер
	amountEdges++;//добавляем к счетчику +1

	tempVertexConnected->second->listEdges.push_back(edges);//в нейроне от которого связь, добавляем ребро
}

void Graf::EditWeightEdges(std::string nameEdges, long double weightEdges)
{
	//поиск по хеш-таблице и измененя веса у ребра
	heshMapEdges.find(nameEdges)->second->weightEdges = weightEdges;
}

void Graf::AddInVertex()
{
	vertex = new Vertex;//создаем в динам памяти новый нейрон
	vertex->indexVertex = "1." + std::to_string(amountVertex);//даем ему имя согласно тому что входные будут с перфиском "1."
	heshMapVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу
	heshMapInVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу для входных нейронов
	amountVertex++;//добавляем к счетчику +1
}

void Graf::AddOutVertex()
{
	vertex = new Vertex;//создаем в динам памяти новый нейрон
	vertex->indexVertex = "-1." + std::to_string(amountVertex);//даем ему имя согласно тому что выходные будут с перфиском "-1."
	heshMapVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу
	heshMapOutVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу для выходных нейронов
	amountVertex++;//добавляем к счетчику +1
}

void Graf::AddVertex()
{
	vertex = new Vertex;//создаем в динам памяти новый нейрон
	vertex->indexVertex = "0." + std::to_string(amountVertex);//даем ему имя согласно тому что выходные будут с перфиском "-1."
	heshMapVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу
	amountVertex++;//добавляем к счетчику +1
}

void Graf::DeleteVertex(std::string nameVertex)
{
	delete heshMapVertex.find(nameVertex)->second;//Находим узел который надо удалить
	auto iter = heshMapVertex.find(nameVertex);
	if (iter != heshMapVertex.end()) {
		heshMapVertex.erase(iter);//Удаляем елемент из хеш-таблицы
	}
}

Graf::Graf()
{

}
