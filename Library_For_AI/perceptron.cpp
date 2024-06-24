#include "perceptron.h"

void ai::perceptron::EditWeightEdges(std::string nameEdges, long double weightEdges)
{
	//поиск по хеш-таблице и измененя веса у ребра
	heshMapEdges.find(nameEdges)->second->weightEdges = weightEdges;
}

void ai::perceptron::AddLayerEdges(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected, std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerAttached)
{
	// Перебираем все нейроны в каждом слое
	for (auto itConnected = vertexLayerConnected->begin(); itConnected != vertexLayerConnected->end(); ++itConnected)
	{
		// Перебираем все нейроны во вложенных списках
		for (auto itAttached = vertexLayerAttached->begin(); itAttached != vertexLayerAttached->end(); ++itAttached)
		{
			// Связываем текущий нейрон из connected слоя с текущим нейроном из attached слоя
			AddEdges(itConnected, itAttached, RandomValue()); // Предполагается, что weightEdges определен где-то в вашем коде
		}
	}
}

void ai::perceptron::AddVertex(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected, 
	ActivationFunction func = nullptr, unsigned long long int iter = 0)
{
	// Создаем новую вершину
	auto newVertex = std::make_shared<Vertex>(func, iter);

	newVertex->indexVertex = std::to_string(std::distance(listVertex.begin(), 
		vertexLayerConnected)) + "." + std::to_string(vertexLayerConnected->size());//ошибка тут 
	// Вставляем новую вершину в список, на который указывает итератор
	vertexLayerConnected->push_back(newVertex);
}

void ai::perceptron::AddInVertex(ActivationFunction func, unsigned long long int iter)
{
	// Получаем первый слой в списке
	auto& initialLayer = listVertex.front();
	// Создаем новый узел
	auto newVertex = std::make_shared<Vertex>(func, iter);
	newVertex->indexVertex = "I." + std::to_string(listVertex.front().size());
	// Добавляем новый узел в начало первого слоя
	initialLayer.emplace_front(std::move(newVertex));
}

void ai::perceptron::AddOutVertex(ActivationFunction func, unsigned long long int iter)
{
	// Получаем последний слой в списке
	auto& outputLayer = listVertex.back();
	// Создаем новый узел
	auto newVertex = std::make_shared<Vertex>(func, iter);
	newVertex->indexVertex = "O." + std::to_string(listVertex.back().size());
	// Добавляем новый узел в конец последнего слоя
	outputLayer.emplace_back(std::move(newVertex));
}

void ai::perceptron::AddEdges(std::list<std::shared_ptr<Vertex>>::iterator vertexConnected, std::list<std::shared_ptr<Vertex>>::iterator vertexAttached, long double weightEdges)
{
	//--------------------------------------------------------------
	//временные переменные для записи узлов с хеш-таблицы
	auto tempVertexConnected = vertexConnected;
	auto tempVertexAttached = vertexAttached;
	//--------------------------------------------------------------
	edges = std::make_shared<Edges>();//создаем новое ребро 
	edges->indexEdges = tempVertexConnected->get()->indexVertex + "-" + tempVertexAttached->get()->indexVertex;//даем ему имя, от двух узлов
	edges->nextVertex = *tempVertexAttached;//записываем указатель следующего нейрона/узла 
	edges->weightEdges = weightEdges;//записываем вес ребра
	heshMapEdges[edges->indexEdges] = edges;//добавляем в хеш-таблицу ребер
	edges.get()->nextVertex.get()->counterPrt++;

	tempVertexConnected->get()->listEdges->push_back(edges);
}

void ai::perceptron::AddLayerVertex()
{
	// Получаем итератор на последний слой
	auto lastLayerIter = std::prev(listVertex.end()); 

	// Создаем новый слой
	std::list<std::shared_ptr<Vertex>> newLayer; 

	// Вставляем новый слой перед последним слоем
	listVertex.insert(lastLayerIter, std::move(newLayer));

	//// Получаем обратный итератор на последний слой
	//auto lastLayerIter = listVertex.rbegin();
	//// Создаем новый слой
	//std::list<std::shared_ptr<Vertex>> newLayer;
	//// Вставляем новый слой перед последним слоем
	//listVertex.insert(lastLayerIter.base(), std::move(newLayer));
}

void ai::perceptron::AddLayerInVertex()
{
	// Создаем новый входной слой
	std::list<std::shared_ptr<Vertex>> inputLayer;

	// Добавляем входной слой в начало списка
	listVertex.emplace_front(std::move(inputLayer));
}

void ai::perceptron::AddLayerOutVertex()
{
	// Создаем новый входной слой
	std::list<std::shared_ptr<Vertex>> inputLayer;

	// Добавляем входной слой в конец списка
	listVertex.emplace_back(std::move(inputLayer));
}

void ai::perceptron::CreateNetwork(size_t amountInVertex, size_t amountOutVertex)
{
	AddLayerInVertex();
	AddLayerOutVertex();
	for (size_t i = 0; i < amountInVertex; i++)
	{
		AddInVertex(activationFunctions[0], 0);
	}
	for (size_t i = 0; i < amountOutVertex; i++)
	{
		AddOutVertex(activationFunctions[0], 0);
	}

	////Реализация добавления 3х слоев с 9ю нейронами 
	//AddLayerVertex();
	//auto itConnected = std::prev(listVertex.end());
	//auto itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 5; i++)
	//{
	//	AddVertex(itAttached);
	//}
	//// Перебираем все слои за исключением последнего
	//itConnected = listVertex.begin();
	//itAttached = std::next(itConnected);
	//while (itAttached != listVertex.end()) {
	//	AddLayerEdges(itConnected, itAttached);
	//	++itConnected;
	//	++itAttached;
	//}

	AddLayerEdges(listVertex.begin(), std::prev(listVertex.end()));
	SaveNetwork();
}

void ai::perceptron::CreateNetwork(std::string nameFile)
{
	std::ifstream AIFile(nameFile);

	// Проверка, открылся ли файл успешно
	if (!AIFile) {
		return;//Выход из функции
	}

	nameProjectFile = nameFile;
	//nameProjectLogFile = nameFile.substr(0, nameFile.find('.')) + " LOG " + GetLocalTime() + ".txt";

	std::string strAmountLayer;
	std::string temp;
	std::string value;
	std::getline(AIFile, temp);//для затирание символа типа нейронки 
	std::getline(AIFile, strAmountLayer);
	if (std::stoi(strAmountLayer) < 2)//тут ошибка
		//проверка на правильность нейроной сети, если меньше 2 то сеть неправильная 
	{
		return;
	}
	AddLayerInVertex();
	AddLayerOutVertex();
	std::getline(AIFile, value);
	std::string amountVertex = value.substr(0, value.find('-'));
	size_t length = value.find('-')+1;
	std::string actFuck = value.substr(length, value.find('.')-2);
	for (size_t i = 0; i < std::stoi(amountVertex); i++)
	{
		AddInVertex(activationFunctions[std::stoi(actFuck)], std::stoi(actFuck));
		length = length + 2;
		actFuck = value.substr(length, value.find('.') - 2);
	}
	for (size_t i = 0; i < (std::stoi(strAmountLayer) - 2); i++)
	{
		AddLayerVertex();
		std::getline(AIFile, value);
		amountVertex = value.substr(0, value.find('-'));
		length = value.find('-') + 1;
		actFuck = value.substr(length, value.find('.') - 2);
		for (size_t i = 0; i < std::stoi(value); i++)
		{
			AddVertex(std::prev(std::prev(listVertex.end())), activationFunctions[std::stoi(actFuck)], std::stoi(actFuck));
			length = length + 2;
			actFuck = value.substr(length, value.find('.') - 2);
		}
	}
	std::getline(AIFile, value);
	amountVertex = value.substr(0, value.find('-'));
	length = value.find('-') + 1;
	actFuck = value.substr(length, value.find('.') - 2);
	for (size_t i = 0; i < std::stoi(value); i++)
	{
		AddOutVertex(activationFunctions[std::stoi(actFuck)], std::stoi(actFuck));
		length = length + 2;
		actFuck = value.substr(length, value.find('.') - 2);
	}

	std::string line;
	while (std::getline(AIFile, line)) {
		std::string firstVertex = line.substr(0, line.find('-'));
		size_t length = line.find('=') - line.find('-') - 1;
		std::string secondVertex = line.substr(line.find('-') + 1, length);
		long double value = std::stod(line.substr(line.find('=') + 1));
		
		std::list<std::shared_ptr<Vertex>>::iterator firstNodeIterator;
		std::list<std::shared_ptr<Vertex>>::iterator secondNodeIterator;

		auto itLayer = listVertex.begin();
		// Поиск первого узла
		for (; itLayer != listVertex.end(); ++itLayer) {
			for (auto itVertex = itLayer->begin(); itVertex != itLayer->end(); ++itVertex) {
				if ((*itVertex)->indexVertex == firstVertex) {
					firstNodeIterator = itVertex;
					break;
				}
			}
		}

		// Поиск второго узла
		for (itLayer = listVertex.begin(); itLayer != listVertex.end(); ++itLayer) {
			for (auto itVertex = itLayer->begin(); itVertex != itLayer->end(); ++itVertex) {
				if ((*itVertex)->indexVertex == secondVertex) {
					secondNodeIterator = itVertex;
					break;
				}
			}
		}

		// Если оба узла найдены, добавляем ребро
		if (firstNodeIterator->get()->indexVertex != "" && secondNodeIterator->get()->indexVertex != "") {//тут ошибка
			AddEdges(firstNodeIterator, secondNodeIterator, value);
		}
	}
	//std::ofstream LogFile(nameProjectLogFile, std::ios::out);
	//LogFile.close();
	AIFile.close();
}

std::list<bool> ai::perceptron::Computation(std::list<bool> vaules)
{
	valueListEdges.clear();
	std::list<bool> result;
	if (vaules.size() != listVertex.front().size())
		return result;

	for(const auto& Node : listVertex.front())
	{
		valueListEdges[Node->indexVertex] = vaules.front();
		vaules.pop_front();
	}

	for(const auto &Layer : listVertex)
	{
		for (const auto& Node : Layer)
		{
			auto tempValue = Node->ActivationFunc(valueListEdges.find(Node->indexVertex)->second);
			auto list = Node->listEdges;
			for (auto& tempList : *list)
			{
				if (valueListEdges.find(tempList->nextVertex->indexVertex) == valueListEdges.end())
				{
					valueListEdges[tempList->nextVertex->indexVertex] = tempValue * tempList->weightEdges;
				} 
				else
				{
					valueListEdges.find(tempList->nextVertex->indexVertex)->second += tempValue * tempList->weightEdges;
				}
			}
		}
	}

	for (const auto& Res : listVertex.back())
	{
		result.push_front(Res->ActivationFunc(valueListEdges.find(Res->indexVertex)->second));
	}

	return result;
}

void ai::perceptron::Logging(std::string nameProjectFile)
{

}

void ai::perceptron::SaveNetwork()
{
	if (nameProjectFile.size() == 0/* || nameProjectLogFile.size() == 0*/)
	{
		nameProjectFile = "AI-.txt";
		//nameProjectLogFile = "AI- LOG " + GetLocalTime() + ".txt";
	}

	std::ofstream outputFile(nameProjectFile, std::ios::out);

	outputFile << "P\n";//тип нейроной сети

	outputFile << listVertex.size() << '\n';

	for (const auto& pair : listVertex)
	{
		outputFile << pair.size() << '-';
		for (const auto& element : pair)
		{
			outputFile << element->iterFunc << '.';
		}
		outputFile << '\n';
	}

	for (const auto& pair : heshMapEdges) {
		outputFile << pair.first << "=" << pair.second->weightEdges << '\n';
	}

	outputFile.close();
}

void ai::perceptron::SaveNetwork(std::string nameFile)
{
	if (nameProjectFile.size() == 0/* || nameProjectLogFile.size() == 0*/)
	{
		nameProjectFile = "AI-.txt";
		//nameProjectLogFile = "AI- LOG " + GetLocalTime() + ".txt";
	}

	std::ofstream outputFile(nameFile, std::ios::out);

	outputFile << "P\n";//тип нейроной сети

	outputFile << listVertex.size() << '\n';

	for (const auto& pair : listVertex)
	{
		outputFile << pair.size() << '-';
		for (const auto& element : pair)
		{
			outputFile << element->iterFunc << '.';
		}
		outputFile << '\n';
	}

	for (const auto& pair : heshMapEdges) {
		outputFile << pair.first << "=" << pair.second->weightEdges << '\n';
	}

	outputFile.close();
}

unsigned int ai::perceptron::CounterCombination()
{
	unsigned int amountComb = 0;
	for (const auto& pair : listVertex)
	{
		amountComb = amountComb + pair.size();
	}
	return amountComb;
}

void ai::perceptron::TryArchitecture(unsigned int amountVertex, unsigned int combinationNumber)
{
	//Реализация добавления 3х слоев с 9ю нейронами 
	AddLayerVertex();
	auto itConnected = std::prev(listVertex.end());
	auto itAttached = std::prev(itConnected);
	//костыль
	if (amountVertex < 1)
	{
		amountVertex = 1;
	}
	auto combination = CreateCombination(combinationNumber, amountVertex, activationFunctions.size());
	for (size_t i = 0; i < amountVertex; i++)
	{
		AddVertex(itAttached, activationFunctions[combination[i]], combination[i]);
	}
	// Перебираем все слои за исключением последнего
	heshMapEdges.clear();
	itConnected = listVertex.begin();
	itAttached = std::next(itConnected);
	while (itAttached != listVertex.end()) {
		AddLayerEdges(itConnected, itAttached);
		++itConnected;
		++itAttached;
	}
}

std::vector<std::shared_ptr<ai::Graf>> ai::perceptron::GenerateCombinationFunctions()
{
	std::vector<std::shared_ptr<Graf>> res;
	std::shared_ptr<perceptron> tempObj;
	auto itList = listVertex.begin();
	auto itVertex = itList->begin();
	unsigned int it = 0;
	auto temp = itVertex;
	auto temp1 = itList;
	while (true)
	{
		temp1 = itList;
		temp = itVertex;
		if (itVertex->get()->iterFunc < (activationFunctions.size() - 1))
		{
			itVertex->get()->iterFunc = it;
			itVertex->get()->activationFunc = activationFunctions[it];//
			it++;
		}
		else
		{
			temp++;
			if (temp != itList->end() && temp->get()->iterFunc != (activationFunctions.size() - 1))//ошибка возникает тут после инкримации itList
			{
				itVertex->get()->iterFunc = 0;
				itVertex->get()->activationFunc = activationFunctions[0];
				itVertex++;
				it = 1;
				itVertex->get()->iterFunc = it;
				itVertex->get()->activationFunc = activationFunctions[it];
			}
			else
			{
				temp1++;
				temp = itList->begin();
				if (itList != listVertex.end() && temp->get()->iterFunc == (activationFunctions.size() - 1))
				{
					if (temp1 == listVertex.end() || temp1->begin()->get()->iterFunc == (activationFunctions.size() - 1))
					{
						break;
					}
					else
					{
						while (itVertex != itList->end())
						{
							itVertex->get()->iterFunc = 0;
							itVertex->get()->activationFunc = activationFunctions[0];
							itVertex++;
						}
						itList++;
					}
				}
				itVertex = itList->begin();
				it = 1;
			}
		}

		// Создание новой копии текущего состояния perceptron и добавление её в res
		//Try = new ai::perceptron(this);
		std::shared_ptr<perceptron> tempObj = std::make_shared<perceptron>(*this);
		res.push_back(tempObj);
	}
	return res;
}

void ai::perceptron::Clear()
{
	listVertex.clear();
	listEdges.clear();
}

void ai::perceptron::Show()
{
	for (auto pair : listVertex)
	{
		for (auto it : pair)
		{
			std::cout << it->iterFunc << ' ';
		}
		std::cout << '\n';
	}
}

void ai::perceptron::Test()
{
	AddLayerInVertex();
	AddLayerOutVertex();
	for (size_t i = 0; i < 100; i++)
	{
		AddInVertex(activationFunctions[0], 0);
	}
	for (size_t i = 0; i < 10; i++)
	{
		AddOutVertex(activationFunctions[0], 0);
	}

	//AddLayerVertex();
	//auto itConnected = std::prev(listVertex.end());
	//auto itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 90; i++)
	//{
	//	AddVertex(itAttached, activationFunctions[0]);
	//}

	//AddLayerVertex();
	//auto itConnected = std::prev(listVertex.end());
	//auto itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 80; i++)
	//{
	//	AddVertex(itAttached, activationFunctions[0]);
	//}

	AddLayerVertex();
	auto itConnected = std::prev(listVertex.end());
	auto itAttached = std::prev(itConnected);
	for (size_t i = 0; i < 70; i++)
	{
		AddVertex(itAttached, activationFunctions[0]);
	}

	//AddLayerVertex();
	// itConnected = std::prev(listVertex.end());
	// itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 60; i++)
	//{
	//	AddVertex(itAttached, activationFunctions[0]);
	//}

	//AddLayerVertex();
	// itConnected = std::prev(listVertex.end());
	// itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 50; i++)
	//{
	//	AddVertex(itAttached, activationFunctions[0]);
	//}

	AddLayerVertex();
	 itConnected = std::prev(listVertex.end());
	 itAttached = std::prev(itConnected);
	for (size_t i = 0; i < 40; i++)
	{
		AddVertex(itAttached, activationFunctions[0]);
	}

	//AddLayerVertex();
	// itConnected = std::prev(listVertex.end());
	// itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 30; i++)
	//{
	//	AddVertex(itAttached, activationFunctions[0]);
	//}

	//AddLayerVertex();
	// itConnected = std::prev(listVertex.end());
	// itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 20; i++)
	//{
	//	AddVertex(itAttached, activationFunctions[0]);
	//}

	//AddLayerVertex();
	// itConnected = std::prev(listVertex.end());
	// itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 10; i++)
	//{
	//	AddVertex(itAttached, activationFunctions[0]);
	//}

	// Перебираем все слои за исключением последнего
	heshMapEdges.clear();
	itConnected = listVertex.begin();
	itAttached = std::next(itConnected);
	while (itAttached != listVertex.end()) {
		AddLayerEdges(itConnected, itAttached);
		++itConnected;
		++itAttached;
	}

	SaveNetwork();
}

//void ai::perceptron::GenerateCombinationFunctions(unsigned int combinationNumber, unsigned int combinationNumberTwo)
//{
//	auto combinationForOne = CreateCombination(combinationNumber, listVertex.begin()->size(), activationFunctions.size());
//	auto combinationForTwo = CreateCombination(combinationNumberTwo, std::prev(listVertex.end())->size(), activationFunctions.size());
//	size_t i = 0;
//	for (auto pair : *listVertex.begin())
//	{
//		pair->activationFunc = activationFunctions[combinationForOne[i]];
//		i++;
//	}
//	i = 0;
//	for (auto pair : *std::prev(listVertex.end()))
//	{
//		pair->activationFunc = activationFunctions[combinationForOne[i]];
//		i++;
//	}
//}