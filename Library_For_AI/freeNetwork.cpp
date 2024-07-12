#include "freeNetwork.h"

void ai::freeNetwork::EditWeightEdges(std::string nameEdges, long double weightEdges)
{
	//����� �� ���-������� � �������� ���� � �����
	heshMapEdges.find(nameEdges)->second->weightEdges = weightEdges;
}

void ai::freeNetwork::AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges)
{
	//--------------------------------------------------------------
	//��������� ���������� ��� ������ ����� � ���-�������
	auto tempVertexConnected = heshMapVertex.find(vertexConnected);
	auto tempVertexAttached = heshMapVertex.find(vertexAttached);
	//--------------------------------------------------------------
	edges = std::make_shared<Edges>();//������� ����� ����� 
	edges->indexEdges = tempVertexConnected->second->indexVertex + "-" + tempVertexAttached->second->indexVertex;//���� ��� ���, �� ���� �����
	edges->nextVertex = tempVertexAttached->second;//���������� ��������� ���������� �������/���� 
	edges->weightEdges = weightEdges;//���������� ��� �����
	heshMapEdges[edges->indexEdges] = edges;//��������� � ���-������� �����
	edges.get()->nextVertex.get()->counterPrt++;

	tempVertexConnected->second->listEdges->push_back(edges);//
}

void ai::freeNetwork::DeleteEdges(std::string nameVertex, std::string nameEdges)
{
	auto temp = heshMapVertex.find(nameVertex)->second;//������� ���� �� �������� ���� ������� �����
	auto listTemp = temp->listEdges;
	for (auto it = listTemp->begin(); it != listTemp->end(); ++it)
	{
		if ((*it)->indexEdges == nameEdges) {//���� �������
			it->get()->nextVertex.get()->counterPrt--;
			it = temp->listEdges->erase(it);//������� �� ������ ��������
			heshMapEdges.erase(nameEdges);
		}
		else {
			++it;
		}
	}
}

void ai::freeNetwork::AddVertex()
{
	vertex = std::make_shared<Vertex>();//������� � ����� ������ ����� ������
	vertex->indexVertex = "M." + std::to_string(heshMapInterVertex.size());//���� ��� ��� �������� ���� ��� �������� ����� � ��������� "M."
	heshMapVertex[vertex->indexVertex] = vertex;//���������� � ���-�������
	heshMapInterVertex[vertex->indexVertex] = vertex;//���������� � ���-������� ��� ������������� ��������
}

void ai::freeNetwork::AddInVertex()
{
	vertex = std::make_shared<Vertex>();//������� � ����� ������ ����� ������
	vertex->indexVertex = "I." + std::to_string(heshMapInVertex.size());//���� ��� ��� �������� ���� ��� ������� ����� � ��������� "I."
	heshMapVertex[vertex->indexVertex] = vertex;//���������� � ���-�������
	heshMapInVertex[vertex->indexVertex] = vertex;//���������� � ���-������� ��� ������� ��������
}

void ai::freeNetwork::AddOutVertex()
{
	vertex = std::make_shared<Vertex>();//������� � ����� ������ ����� ������
	vertex->indexVertex = "O." + std::to_string(heshMapOutVertex.size());//���� ��� ��� �������� ���� ��� �������� ����� � ��������� "O."
	heshMapVertex[vertex->indexVertex] = vertex;//���������� � ���-�������
	heshMapOutVertex[vertex->indexVertex] = vertex;//���������� � ���-������� ��� �������� ��������
}

void ai::freeNetwork::AddVertex(std::string vertexConnected, std::string vertexAttached)
{
	vertex = std::make_shared<Vertex>();//������� � ����� ������ ����� ������
	vertex->indexVertex = "M." + std::to_string(heshMapInterVertex.size());//���� ��� ��� �������� ���� ��� �������� ����� � ��������� "M."
	heshMapVertex[vertex->indexVertex] = vertex;//���������� � ���-�������
	heshMapInterVertex[vertex->indexVertex] = vertex;//���������� � ���-������� ��� ������������� ��������

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

void ai::freeNetwork::CreateNetwork(size_t amountInVertex, size_t amountOutVertex)
{

	for (unsigned long long int i = 0; i < amountInVertex; i++)
	{
		AddInVertex();
	}
	for (unsigned long long int i = 0; i < amountOutVertex; i++)
	{
		AddOutVertex();
	}
	//���������� ���������� ������� � �������� ��������
	for (const auto& pairInVertex : heshMapInVertex)
	{
		for (const auto& pairOutVertex : heshMapOutVertex)
		{
			AddEdges(pairInVertex.first, pairOutVertex.first, RandomValue());
		}
	}
	SaveNetwork();
}

void ai::freeNetwork::CreateNetwork(std::string nameFile)
{
	std::ifstream AIFile(nameFile);

	// ��������, �������� �� ���� �������
	if (!AIFile) {
		return;//����� �� �������
	}

	nameProjectFile = nameFile;
	//nameProjectLogFile = nameFile.substr(0, nameFile.find('.')) + " LOG " + GetLocalTime() + ".txt";
	std::string strAmountInVertex;
	std::string strAmountOutVertex;
	std::string strAmountInterVertex;
	std::string temp;
	std::getline(AIFile, temp);//��� ��������� ������� ���� �������� 
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
	//std::ofstream LogFile(nameProjectLogFile, std::ios::out);
	//LogFile.close();
	AIFile.close();
}

void ai::freeNetwork::SaveNetwork()
{
	if (nameProjectFile.size() == 0 /*|| nameProjectLogFile.size() == 0*/)
	{
		nameProjectFile = "AI-.txt";
		//nameProjectLogFile = "AI- LOG " + GetLocalTime() + ".txt";
	}

	std::ofstream outputFile(nameProjectFile, std::ios::out);

	outputFile << "F\n";//��� �������� ����

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

//void ai::freeNetwork::Logging(std::string nameProjectFile)
//{
//	std::ofstream LogFile(nameProjectLogFile, std::ios::app);
//
//	if (!LogFile) {
//		return;//����� �� �������
//	}
//
//	LogFile << GetLocalTime() << '\n';
//	LogFile << "Vertex\nAmount of all nodes ";
//	LogFile << heshMapVertex.size();
//	LogFile << '\n';
//	LogFile << "-----------------------\n";
//	LogFile << "InVertex: " << heshMapInVertex.size() << '\n';
//	for (const auto& pair : heshMapInVertex)
//	{
//		LogFile << pair.first << " number of pointers to it: " << pair.second.get()->counterPrt << '\n';
//	}
//	LogFile << "-----------------------\n";
//	LogFile << "InterVertex: " << heshMapInterVertex.size() << '\n';
//	for (const auto& pair : heshMapInterVertex)
//	{
//		LogFile << pair.first << " number of pointers to it: " << pair.second.get()->counterPrt << '\n';
//	}
//	LogFile << "-----------------------\n";
//	LogFile << "OutVertex: " << heshMapOutVertex.size() << '\n';
//	for (const auto& pair : heshMapOutVertex)
//	{
//		LogFile << pair.first << " number of pointers to it: " << pair.second.get()->counterPrt << '\n';
//	}
//	LogFile << "-----------------------\n";
//	LogFile << "Edges\n";
//	for (const auto& pair : heshMapEdges)
//	{
//		LogFile << pair.first << ' ' << pair.second->weightEdges <<'\n';
//	}
//	LogFile << "-----------------------\n";
//	LogFile << "TrainingEdges\ncounter Traing = " << counterTraing << '\n'
//		<< "Size TrainingEdges = " << heshMapTrainingEdges.size() << '\n';
//	for (const auto& pair : heshMapTrainingEdges)
//	{
//		LogFile << "-----------------------\n";
//		LogFile << pair.first << '\n';
//		LogFile << "-----------------------\n";
//
//		long double vaule = 0;
//		unsigned int iter = 0;
//
//		auto& list = *pair.second;//�������� ������ �� ������
//		for (auto it = list.begin(); it != list.end(); ++it)
//		{
//			LogFile << (*it).weight << " - " << (*it).amoutnTry << '\n';
//			vaule += ((*it).weight * (*it).amoutnTry);
//			iter += ((*it).amoutnTry);
//		}
//		LogFile << "-----------------------\n";
//		LogFile << "vaule - " << vaule << " iter - " << iter << "\n";
//		vaule = vaule / iter;
//		LogFile << "average number - " << vaule << "\n";
//	}
//	LogFile << "-----------------------\n";
//	LogFile << "\n\n\n\n";
//	LogFile.close();
//}
