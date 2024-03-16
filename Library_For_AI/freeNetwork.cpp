#include "freeNetwork.h"

void ai::freeNetwork::EditWeightEdges(std::string nameEdges, long double weightEdges)
{
	//поиск по хеш-таблице и измененя веса у ребра
	heshMapEdges.find(nameEdges)->second->weightEdges = weightEdges;
}

void ai::freeNetwork::AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges)
{
	//--------------------------------------------------------------
	//временные переменные для записи узлов с хеш-таблицы
	auto tempVertexConnected = heshMapVertex.find(vertexConnected);
	auto tempVertexAttached = heshMapVertex.find(vertexAttached);
	//--------------------------------------------------------------
	edges = std::make_shared<Edges>();//создаем новое ребро 
	edges->indexEdges = tempVertexConnected->second->indexVertex + "-" + tempVertexAttached->second->indexVertex;//даем ему имя, от двух узлов
	edges->nextVertex = tempVertexAttached->second;//записываем указатель следующего нейрона/узла 
	edges->weightEdges = weightEdges;//записываем вес ребра
	heshMapEdges[edges->indexEdges] = edges;//добавляем в хеш-таблицу ребер
	edges.get()->nextVertex.get()->counterPrt++;

	tempVertexConnected->second->listEdges->push_back(edges);//
}

void ai::freeNetwork::DeleteEdges(std::string nameVertex, std::string nameEdges)
{
	auto temp = heshMapVertex.find(nameVertex)->second;//Находим узел из которого надо удалить связь
	auto listTemp = temp->listEdges;
	for (auto it = listTemp->begin(); it != listTemp->end(); ++it)
	{
		if ((*it)->indexEdges == nameEdges) {//если найдено
			it->get()->nextVertex.get()->counterPrt--;
			it = temp->listEdges->erase(it);//удаляем из списка итератор
			heshMapEdges.erase(nameEdges);
		}
		else {
			++it;
		}
	}
}

void ai::freeNetwork::AddVertex()
{
	vertex = std::make_shared<Vertex>(activationFuncPtr);//создаем в динам памяти новый нейрон
	vertex->indexVertex = "M." + std::to_string(heshMapInterVertex.size());//даем ему имя согласно тому что выходные будут с перфиском "M."
	heshMapVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу
	heshMapInterVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу для промежуточных нейронов
}

void ai::freeNetwork::AddInVertex()
{
	vertex = std::make_shared<Vertex>();//создаем в динам памяти новый нейрон
	vertex->indexVertex = "I." + std::to_string(heshMapInVertex.size());//даем ему имя согласно тому что входные будут с перфиском "I."
	heshMapVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу
	heshMapInVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу для входных нейронов
}

void ai::freeNetwork::AddOutVertex()
{
	vertex = std::make_shared<Vertex>(activationOutFuncPtr);//создаем в динам памяти новый нейрон
	vertex->indexVertex = "O." + std::to_string(heshMapOutVertex.size());//даем ему имя согласно тому что выходные будут с перфиском "O."
	heshMapVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу
	heshMapOutVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу для выходных нейронов
}

void ai::freeNetwork::AddVertex(std::string vertexConnected, std::string vertexAttached)
{
	vertex = std::make_shared<Vertex>(activationFuncPtr);//создаем в динам памяти новый нейрон
	vertex->indexVertex = "M." + std::to_string(heshMapInterVertex.size());//даем ему имя согласно тому что выходные будут с перфиском "M."
	heshMapVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу
	heshMapInterVertex[vertex->indexVertex] = vertex;//записываем в хеш-таблицу для промежуточных нейронов

	AddEdges(vertexConnected, vertex->indexVertex, RandomValue());
	AddEdges(vertex->indexVertex, vertexAttached, RandomValue());
}

void ai::freeNetwork::DeleteVertex(std::string nameVertex)
{
	auto iter = heshMapVertex.find(nameVertex);
	try
	{
		if (iter != heshMapVertex.end()) {
			if (iter->first[0] == 'M') {
				heshMapInterVertex.find(iter->first)->second.reset();
				heshMapInterVertex.erase(iter->first);
			}
			else if (iter->first[0] == 'I') {
				heshMapInVertex.find(iter->first)->second.reset();
				heshMapInVertex.erase(iter->first);
			}
			else if (iter->first[0] == 'O') {
				heshMapOutVertex.find(iter->first)->second.reset();
				heshMapOutVertex.erase(iter->first);
			}
			else {
				throw std::exception();
			}
			heshMapVertex.erase(iter);
		}
		else {
			throw std::exception();
		}
	}
	catch (const std::exception&)
	{
		heshMapVertex.erase(iter);
	}
}

void ai::freeNetwork::CreateNetwork(size_t amountInVertex, size_t amountOutVertex, bool(*activationFuncPtr)(long double), bool(*activationOutFuncPtr)(long double))
{
	std::cout << "CreateNetwork in freeNetwork\n";

	this->activationFuncPtr = activationFuncPtr;
	this->activationOutFuncPtr = activationOutFuncPtr;

	for (unsigned long long int i = 0; i < amountInVertex; i++)
	{
		AddInVertex();
	}
	for (unsigned long long int i = 0; i < amountOutVertex; i++)
	{
		AddOutVertex();
	}
	//Реализация соидинений входных и выходных нейронов
	for (const auto& pairInVertex : heshMapInVertex)
	{
		for (const auto& pairOutVertex : heshMapOutVertex)
		{
			AddEdges(pairInVertex.first, pairOutVertex.first, RandomValue());
		}
	}
	SaveNetwork();
	Training(0);//костыль 
}

void ai::freeNetwork::CreateNetwork(std::string nameFile, bool(*activationFuncPtr)(long double), bool(*activationOutFuncPtr)(long double))
{
	std::ifstream AIFile(nameFile);

	// Проверка, открылся ли файл успешно
	if (!AIFile) {
		return;//Выход из функции
	}

	this->activationFuncPtr = activationFuncPtr;
	this->activationOutFuncPtr = activationOutFuncPtr;

	nameProjectFile = nameFile;
	nameProjectLogFile = nameFile.substr(0, nameFile.find('.')) + " LOG " + GetLocalTime() + ".txt";
	std::string strAmountInVertex;
	std::string strAmountOutVertex;
	std::string strAmountInterVertex;
	std::string temp;
	std::getline(AIFile, temp);//для затирание символа типа нейронки 
	std::getline(AIFile, strAmountInVertex);
	std::getline(AIFile, strAmountOutVertex);
	std::getline(AIFile, strAmountInterVertex);
	size_t amountInVertex = std::stoi(strAmountInVertex);
	size_t amountOutVertex = std::stoi(strAmountOutVertex);
	size_t amountInterVertex = std::stoi(strAmountInterVertex);
	for (unsigned long long int i = 0; i < amountInVertex; i++)
	{
		AddInVertex();
	}
	for (unsigned long long int i = 0; i < amountOutVertex; i++)
	{
		AddOutVertex();
	}
	for (unsigned long long int i = 0; i < amountInterVertex; i++)
	{
		AddVertex();
	}
	std::string line;
	while (std::getline(AIFile, line)) {
		std::string firstVertex = line.substr(0, line.find('-'));
		size_t length = line.find('=') - line.find('-') - 1;
		std::string secondVertex = line.substr(line.find('-') + 1, length);
		long double value = std::stod(line.substr(line.find('=') + 1));

		AddEdges(firstVertex, secondVertex, value);
	}
	std::ofstream LogFile(nameProjectLogFile, std::ios::out);
	LogFile.close();
	AIFile.close();
	Training(0);//костыль 
}

void ai::freeNetwork::SaveNetwork()
{
	if (nameProjectFile.size() == 0 || nameProjectLogFile.size() == 0)
	{
		nameProjectFile = "AI-.txt";
		nameProjectLogFile = "AI- LOG " + GetLocalTime() + ".txt";
	}

	std::ofstream outputFile(nameProjectFile, std::ios::out);

	outputFile << "F\n";//тип нейроной сети

	outputFile << heshMapInVertex.size() << '\n' << heshMapOutVertex.size() << '\n' << heshMapInterVertex.size() << '\n';

	for (const auto& pair : heshMapEdges) {
		outputFile << pair.first << "=" << pair.second->weightEdges << '\n';
	}

	outputFile.close();
}

std::list<bool> ai::freeNetwork::Computation(std::list<bool> vaules)
{
	return std::list<bool>();
}

void ai::freeNetwork::Training(bool result)
{
	counterTraing++;
	counterForAddVertex++;//счетчик для добовление нейрона 
	valueListEdges.clear();//очистить значение для нейронов 
	if (result)
	{
		if (flag)//если под счет сумы показал хорошие результаты  
		{
			flag = 0;
		}
		amountGoodTry++;
		auto tempEdges = heshMapEdges.find(nameEdges);
		cell = std::make_shared<StorageCell>();
		if (heshMapTrainingEdges.find(nameEdges) != heshMapTrainingEdges.end())
		{
			auto goodEdges = heshMapTrainingEdges.find(nameEdges);
			cell->weight = tempEdges->second->weightEdges;
			cell->amoutnTry = amountGoodTry;
			goodEdges->second->push_back(*cell);
		}
		else
		{
			listStorageCell = std::make_shared<std::list<StorageCell>>();
			//auto goodEdges = heshMapTrainingEdges.find(nameEdges);//Вероятная ошибка тут
			cell->weight = tempEdges->second->weightEdges;
			cell->amoutnTry = amountGoodTry;
			listStorageCell->push_back(*cell);
			heshMapTrainingEdges[nameEdges] = listStorageCell;
		}
	}
	else
	{
		if (flag)//если под счет сумы показал плохие результаты то стереть их и начать занаво 
		{
			flag = 0;
			heshMapTrainingEdges.clear();
		}
		amountGoodTry = 0;
		auto randomIter = std::next(heshMapEdges.begin(), std::rand() % heshMapEdges.size());//взятие случайного ребра
		EditWeightEdges(randomIter->first, RandomValue());//смена веса у ребра на рандомное значение в диапазое от -1 до 1
		nameEdges = randomIter->first;//запись ребра которое поменяли
		if (amountTraing >= 100)
		{
			amountTraing = 0;
			std::unordered_map<std::string, std::shared_ptr<std::list<StorageCell>>> temp;
			if (counterForAddVertex >= 1000)
			{
				counterForAddVertex = 0;

			}
			else
			{
				flag = 1;
				for (const auto& pair : heshMapTrainingEdges)
				{
					cell = std::make_shared<StorageCell>();
					listStorageCell = std::make_shared<std::list<StorageCell>>();
					long double value = 0;
					unsigned int iter = 0;
					for (const auto& element : *pair.second)
					{
						value += element.weight;
						iter += element.amoutnTry;
					}
					value = value / iter;
					EditWeightEdges(pair.first, value);
					cell->weight = value;
					if (iter < 10)
						cell->amoutnTry = 1;
					else
						cell->amoutnTry = 10;
					listStorageCell->push_back(*cell);
					temp[pair.first] = listStorageCell;
				}
			}
			heshMapTrainingEdges.clear();
			heshMapTrainingEdges = temp;
			temp.clear();
		}
	}
	amountTraing++;
	SaveNetwork();
}

void ai::freeNetwork::Logging(std::string nameProjectFile)
{
	std::ofstream LogFile(nameProjectLogFile, std::ios::app);

	if (!LogFile) {
		return;//Выход из функции
	}

	LogFile << GetLocalTime() << '\n';
	LogFile << "Vertex\nAmount of all nodes ";
	LogFile << heshMapVertex.size();
	LogFile << '\n';
	LogFile << "-----------------------\n";
	LogFile << "InVertex: " << heshMapInVertex.size() << '\n';
	for (const auto& pair : heshMapInVertex)
	{
		LogFile << pair.first << " number of pointers to it: " << pair.second.get()->counterPrt << '\n';
	}
	LogFile << "-----------------------\n";
	LogFile << "InterVertex: " << heshMapInterVertex.size() << '\n';
	for (const auto& pair : heshMapInterVertex)
	{
		LogFile << pair.first << " number of pointers to it: " << pair.second.get()->counterPrt << '\n';
	}
	LogFile << "-----------------------\n";
	LogFile << "OutVertex: " << heshMapOutVertex.size() << '\n';
	for (const auto& pair : heshMapOutVertex)
	{
		LogFile << pair.first << " number of pointers to it: " << pair.second.get()->counterPrt << '\n';
	}
	LogFile << "-----------------------\n";
	LogFile << "Edges\n";
	for (const auto& pair : heshMapEdges)
	{
		LogFile << pair.first << ' ' << pair.second->weightEdges <<'\n';
	}
	LogFile << "-----------------------\n";
	LogFile << "TrainingEdges\ncounter Traing = " << counterTraing << '\n'
		<< "Size TrainingEdges = " << heshMapTrainingEdges.size() << '\n';
	for (const auto& pair : heshMapTrainingEdges)
	{
		LogFile << "-----------------------\n";
		LogFile << pair.first << '\n';
		LogFile << "-----------------------\n";

		long double vaule = 0;
		unsigned int iter = 0;

		auto& list = *pair.second;//получаем ссылку на список
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			LogFile << (*it).weight << " - " << (*it).amoutnTry << '\n';
			vaule += ((*it).weight * (*it).amoutnTry);
			iter += ((*it).amoutnTry);
		}
		LogFile << "-----------------------\n";
		LogFile << "vaule - " << vaule << " iter - " << iter << "\n";
		vaule = vaule / iter;
		LogFile << "average number - " << vaule << "\n";
	}
	LogFile << "-----------------------\n";
	LogFile << "\n\n\n\n";
	LogFile.close();
}
