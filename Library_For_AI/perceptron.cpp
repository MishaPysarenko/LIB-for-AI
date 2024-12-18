#include "perceptron.h"

void ai::perceptron::EditWeightEdges(std::string nameEdges, long double weightEdges)
{
	//����� �� ���-������� � �������� ���� � �����
	heshMapEdges.find(nameEdges)->second->weightEdges = weightEdges;
}

void ai::perceptron::AddLayerEdges(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected, std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerAttached)
{
	// ���������� ��� ������� � ������ ����
	for (auto itConnected = vertexLayerConnected->begin(); itConnected != vertexLayerConnected->end(); ++itConnected)
	{
		// ���������� ��� ������� �� ��������� �������
		for (auto itAttached = vertexLayerAttached->begin(); itAttached != vertexLayerAttached->end(); ++itAttached)
		{
			// ��������� ������� ������ �� connected ���� � ������� �������� �� attached ����
			AddEdges(itConnected, itAttached, RandomValue()); // ��������������, ��� weightEdges ��������� ���-�� � ����� ����
		}
	}
}

void ai::perceptron::AddVertex(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected, 
	ActivationFunction func = nullptr, unsigned long long int iter = 0)
{
	// ������� ����� �������
	auto newVertex = std::make_shared<Vertex>(func, iter);

	newVertex->indexVertex = std::to_string(std::distance(listVertex.begin(), 
		vertexLayerConnected)) + "." + std::to_string(vertexLayerConnected->size());//������ ��� 
	// ��������� ����� ������� � ������, �� ������� ��������� ��������
	vertexLayerConnected->push_back(newVertex);
}

void ai::perceptron::AddInVertex(ActivationFunction func, unsigned long long int iter)
{
	// �������� ������ ���� � ������
	auto& initialLayer = listVertex.front();
	// ������� ����� ����
	auto newVertex = std::make_shared<Vertex>(func, iter);
	newVertex->indexVertex = "I." + std::to_string(listVertex.front().size());
	// ��������� ����� ���� � ������ ������� ����
	initialLayer.emplace_front(std::move(newVertex));
}

void ai::perceptron::AddOutVertex(ActivationFunction func, unsigned long long int iter)
{
	// �������� ��������� ���� � ������
	auto& outputLayer = listVertex.back();
	// ������� ����� ����
	auto newVertex = std::make_shared<Vertex>(func, iter);
	newVertex->indexVertex = "O." + std::to_string(listVertex.back().size());
	// ��������� ����� ���� � ����� ���������� ����
	outputLayer.emplace_back(std::move(newVertex));
}

void ai::perceptron::AddEdges(std::list<std::shared_ptr<Vertex>>::iterator vertexConnected, std::list<std::shared_ptr<Vertex>>::iterator vertexAttached, long double weightEdges)
{
	//--------------------------------------------------------------
	//��������� ���������� ��� ������ ����� � ���-�������
	auto tempVertexConnected = vertexConnected;
	auto tempVertexAttached = vertexAttached;
	//--------------------------------------------------------------
	edges = std::make_shared<Edges>();//������� ����� ����� 
	edges->indexEdges = tempVertexConnected->get()->indexVertex + "-" + tempVertexAttached->get()->indexVertex;//���� ��� ���, �� ���� �����
	edges->nextVertex = *tempVertexAttached;//���������� ��������� ���������� �������/���� 
	edges->weightEdges = weightEdges;//���������� ��� �����
	heshMapEdges[edges->indexEdges] = edges;//��������� � ���-������� �����
	edges.get()->nextVertex.get()->counterPrt++;

	tempVertexConnected->get()->listEdges->push_back(edges);
}

void ai::perceptron::AddLayerVertex()
{
	// �������� �������� �� ��������� ����
	auto lastLayerIter = std::prev(listVertex.end()); 

	// ������� ����� ����
	std::list<std::shared_ptr<Vertex>> newLayer; 

	// ��������� ����� ���� ����� ��������� �����
	listVertex.insert(lastLayerIter, std::move(newLayer));

	//// �������� �������� �������� �� ��������� ����
	//auto lastLayerIter = listVertex.rbegin();
	//// ������� ����� ����
	//std::list<std::shared_ptr<Vertex>> newLayer;
	//// ��������� ����� ���� ����� ��������� �����
	//listVertex.insert(lastLayerIter.base(), std::move(newLayer));
}

void ai::perceptron::AddLayerInVertex()
{
	// ������� ����� ������� ����
	std::list<std::shared_ptr<Vertex>> inputLayer;

	// ��������� ������� ���� � ������ ������
	listVertex.emplace_front(std::move(inputLayer));
}

void ai::perceptron::AddLayerOutVertex()
{
	// ������� ����� ������� ����
	std::list<std::shared_ptr<Vertex>> inputLayer;

	// ��������� ������� ���� � ����� ������
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

	////���������� ���������� 3� ����� � 9� ��������� 
	//AddLayerVertex();
	//auto itConnected = std::prev(listVertex.end());
	//auto itAttached = std::prev(itConnected);
	//for (size_t i = 0; i < 5; i++)
	//{
	//	AddVertex(itAttached);
	//}
	//// ���������� ��� ���� �� ����������� ����������
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

	// ��������, �������� �� ���� �������
	if (!AIFile) {
		return;//����� �� �������
	}

	nameProjectFile = nameFile;
	//nameProjectLogFile = nameFile.substr(0, nameFile.find('.')) + " LOG " + GetLocalTime() + ".txt";

	std::string strAmountLayer;
	std::string temp;
	std::string value;
	std::getline(AIFile, temp);
	std::getline(AIFile, temp);
	std::getline(AIFile, strAmountLayer);
	if (std::stoi(strAmountLayer) < 2)//�������� �� ������������ �������� ����, ���� ������ 2 �� ���� ������������ 
	{
		return;
	}
	AddLayerInVertex();
	AddLayerOutVertex();
	std::getline(AIFile, value);
	std::string amountVertex = value.substr(0, value.find('-'));
	size_t length = value.find('-')+1;
	std::string actFuck = value.substr(length, value.find('.')-2);
	amountIn = std::stoi(amountVertex);
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
	amountOut = std::stoi(value);
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
		// ����� ������� ����
		for (; itLayer != listVertex.end(); ++itLayer) {
			for (auto itVertex = itLayer->begin(); itVertex != itLayer->end(); ++itVertex) {
				if ((*itVertex)->indexVertex == firstVertex) {
					firstNodeIterator = itVertex;
					break;
				}
			}
		}

		// ����� ������� ����
		for (itLayer = listVertex.begin(); itLayer != listVertex.end(); ++itLayer) {
			for (auto itVertex = itLayer->begin(); itVertex != itLayer->end(); ++itVertex) {
				if ((*itVertex)->indexVertex == secondVertex) {
					secondNodeIterator = itVertex;
					break;
				}
			}
		}

		// ���� ��� ���� �������, ��������� �����
		if (firstNodeIterator->get()->indexVertex != "" && secondNodeIterator->get()->indexVertex != "") {//��� ������
			AddEdges(firstNodeIterator, secondNodeIterator, value);
		}
	}
	//std::ofstream LogFile(nameProjectLogFile, std::ios::out);
	//LogFile.close();
	AIFile.close();
}

std::list<NWDT> ai::perceptron::Computation(std::list<NWDT> vaules)
{
	valueListEdges.clear();
	std::list<NWDT> result;
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

void ai::perceptron::SaveNetwork()
{
	if (nameProjectFile.size() == 0/* || nameProjectLogFile.size() == 0*/)
	{
		nameProjectFile = "AI-.txt";
		//nameProjectLogFile = "AI- LOG " + GetLocalTime() + ".txt";
	}

	std::ofstream outputFile(nameProjectFile, std::ios::out);

	outputFile << typeConvert << '\n';

	outputFile << "P\n";//��� �������� ����

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
	if (nameProjectFile.size() == 0)
	{
		nameProjectFile = "AI-.txt";
	}

	std::ofstream outputFile(nameFile, std::ios::out);

	outputFile << "P\n";//��� �������� ����

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
	return std::pow(activationFunctions.size(), amountComb);
}

void ai::perceptron::TryArchitecture(unsigned int amountVertex)
{
	//���������� ���������� 3� ����� � 9� ��������� 
	AddLayerVertex();
	auto itConnected = std::prev(listVertex.end());
	auto itAttached = std::prev(itConnected);
	
	for (size_t i = 0; i < amountVertex; i++)
	{
		AddVertex(itAttached);
	}
	// ���������� ��� ���� �� ����������� ����������
	heshMapEdges.clear();
	itConnected = listVertex.begin();
	itAttached = std::next(itConnected);
	while (itAttached != listVertex.end()) {
		AddLayerEdges(itConnected, itAttached);
		++itConnected;
		++itAttached;
	}
}

void ai::perceptron::EditAtckFunk(unsigned int numberCombination)
{
	unsigned int amountComb = 0;
	for (const auto& pair : listVertex)
	{
		amountComb = amountComb + pair.size();
	}

	auto combination = CreateCombination(numberCombination, amountComb, activationFunctions.size());

	unsigned int i = 0;
	for (const auto& pair : listVertex)
	{
		for (const auto& it : pair)
		{
			it->activationFunc = activationFunctions[combination[i]-1];
			i++;
		}
	}
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

	AddLayerVertex();
	auto itConnected = std::prev(listVertex.end());
	auto itAttached = std::prev(itConnected);
	for (size_t i = 0; i < 70; i++)
	{
		AddVertex(itAttached, activationFunctions[0]);
	}


	// ���������� ��� ���� �� ����������� ����������
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