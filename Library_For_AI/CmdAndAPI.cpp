#include "CmdAndAPI.h"

void CmdAndAPI::commandInput(int argc, char* argv[])
{
    ai::AI* network = nullptr;
    if (argc == 1)
    {
        std::cout << "Enter the command - help\n";
        return;
    }
    if (std::strcmp(argv[1], "help") == 0)
    {
        std::cout << "\nAll command and API\n";
        std::cout << "\tCOMMAND\n";
        std::cout << "OpenSession - this command is for opening TCP/IP ports and working directly with the neural network\n";
        std::cout << "Has the following arguments -\n";
        std::cout << "<Number port>\n\n";
        std::cout << "CreateProject - this command to create a new neural network:\n";
        std::cout << "Has the following arguments -\n";
        std::cout << "<Project name> <Neural network type> <Number of input neurons> <Number of output neurons>\n\n";
        std::cout << "DatasetTraining - this command is for opening an AI file and training on a pre-prepared data set\n";
        std::cout << "Has the following arguments -\n";
        std::cout << "<AI File> <Data Set File> <Expected percentage of correct answers>\n";
        std::cout << "\tAPI\n";//----------------------------------------------------------------
        std::cout << "When sending requests, the symbol <_> must be placed between the lines.\n";
        std::cout << "CloseSession - this command is for close TCP/IP connection\n";
        std::cout << "This command is not have arguments\n\n";
        std::cout << "OpenProject - open and create a project based on the AI file\n";
        std::cout << "Has the following arguments -\n";
        std::cout << "<Project Name File>\n\n";
        std::cout << "CreateProject - this command to create a new neural network:\n";
        std::cout << "Has the following arguments -\n";
        std::cout << "<Project name>_<Neural network type>_<Number of input neurons>_<Number of output neurons>\n\n";
        std::cout << "DatasetTraining - this command is for opening an AI file and training on a pre-prepared data set\n";
        std::cout << "Before use you need to create a project!\nHas the following arguments -\n";
        std::cout << "<Data Set File>_<Expected percentage of correct answers>\n\n";
        std::cout << "Compilation - compiles the AI response\n";
        std::cout << "Before use you need to create a project!\nHas the following arguments -\n";
        std::cout << "<bit sequence of data>\n\n";
        std::cout << "SelectionOfWeights - selects weights for edges in the AI ??based on previous actions. \n1 - AI answer is correct \n0 - AI answer is NOT correct\n";
        std::cout << "Before use, you must create a project and use it once!\nHas the following arguments -\n";
        std::cout << "<1 or 0>\n\n";
        return;
    }
    else if (std::strcmp(argv[1], "CreateProject") == 0)
    {
        std::string value[4];
        if (argc < 6)
        {
            std::cout << "Not all arguments\n";
            return;
        }
        for (size_t i = 2; i < 6; i++)
        {
            value[i - 2] = argv[i];
        }
        if (value[1] != "PERCEPTRON")
        {
            std::cout << "Argument <Neural network type> is not corect\n";
            std::cout << "variety of types available now:\n";
            std::cout << "1.PERCEPTRON\n";
            return;
        }
        if (std::stoi(value[3]) < 1 && std::stoi(value[2]) < 1)
        {
            std::cout << "Arguments <Number of input neurons> <Number of output neurons> is not corect\n";
            std::cout << "Arguments cannot be less than 1\n";
            return;
        }
        if (value[1] == "PERCEPTRON")
        {
            network = new ai::AI(value[0], ai::PERCEPTRON);
            network->CreateNetwork(std::stoi(value[2]), std::stoi(value[3]));
            delete network;
        }
        std::cout << "Successfully Created\n";
        return;
    }
    else if (std::strcmp(argv[1], "OpenSession") == 0)
    {
        // Инициализация Winsock
        WSADATA wsaData;
        // Создание сокета
        SOCKET listeningSocket;
        if (!createNetwork(wsaData, listeningSocket))
        {
            return;
        }
        int temp = std::stoi(argv[2]);
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(temp);
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        if (bind(listeningSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cout << "Socket binding error" << std::endl;
            closesocket(listeningSocket);
            WSACleanup();
            return;
        }
        // Прослушивание входящих соединений
        if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Error listening to socket" << std::endl;
            closesocket(listeningSocket);
            WSACleanup();
            return;
        }
        std::cout << "Waiting for connection..." << std::endl;
        // Принятие входящего соединения
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(listeningSocket, (sockaddr*)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection" << std::endl;
            closesocket(listeningSocket);
            WSACleanup();
            return;
        }
        std::cout << "Connection established!" << std::endl;
        char buffer[4096];
        int bytesReceived;
        // Получение данных от клиента и отправка обратно (эхо)
        while ((bytesReceived = recv(clientSocket, buffer, 4096, 0)) > 0) {
            buffer[bytesReceived] = '\0';
            std::string temp = buffer;
            std::cout << buffer << '\n';
            if (std::strcmp(buffer, "CloseSession") == 0)
            {
                send(clientSocket, "CloseSession Successfully", 26, 0);
                break;
            }
            else if (temp.substr(0, temp.find("_")) == "CreateProject")
            {
                std::vector<std::string> values;
                splitString(temp, '_', values);
                if (values.size() < 5)
                {
                    send(clientSocket, "Not all arguments", 18, 0);
                    continue;
                }
                if (values[2] != "PERCEPTRON")
                {
                    send(clientSocket, "Argument <Neural network type> is not corect", 45, 0);
                    continue;
                }
                if (std::stoi(values[4]) < 1 && std::stoi(values[3]) < 1)
                {
                    send(clientSocket, "Arguments <Number of input neurons> <Number of output neurons> is not corect", 77, 0);
                    continue;
                }
                if (values[2] == "PERCEPTRON")
                {
                    if (network != nullptr)
                    {
                        std::string tempMessege = "Project - \"" + network->getNameProject() + "\" has been deleted";
                        send(clientSocket, tempMessege.c_str(), tempMessege.size(), 0);
                        delete network;
                    }
                    network = new ai::AI(values[1], ai::PERCEPTRON);
                    network->CreateNetwork(std::stoi(values[4]), std::stoi(values[3]));
                }
                else
                {
                    send(clientSocket, "Failure to Create", 18, 0);
                    continue;
                }
                send(clientSocket, "Successfully Created", 21, 0);
            }
            else if (temp.substr(0, temp.find("_")) == "OpenProject")
            {
                std::vector<std::string> values;
                splitString(temp, '_', values);
                if (values.size() < 2)
                {
                    send(clientSocket, "Not all arguments", 18, 0);
                    continue;
                }
                if (network != nullptr)
                {
                    std::string tempMessege = "Project - \"" + network->getNameProject() + "\" has been deleted";
                    send(clientSocket, tempMessege.c_str(), tempMessege.size(), 0);
                    delete network;
                }
                network = new ai::AI(values[1]);
                send(clientSocket, "OK", 2, 0);
            }
            else if (temp.substr(0, temp.find("_")) == "DatasetTraining")
            {
                std::vector<std::string> values;
                splitString(temp, '_', values);
                if (values.size() < 3)
                {
                    send(clientSocket, "Not all arguments", 18, 0);
                    continue;
                }
                if (network == nullptr)
                {
                    send(clientSocket, "Project is not create", 22, 0);
                    continue;
                }
                send(clientSocket, "Start DatasetTraining", 22, 0);
                //network->DatasetTraining(values[1], std::stoi(values[2]));
                send(clientSocket, "Finish DatasetTraining", 23, 0);
            }
            else if (temp.substr(0, temp.find("_")) == "Compilation")
            {
                std::vector<std::string> values;
                splitString(temp, '_', values);
                if (values.size() < 2)
                {
                    send(clientSocket, "Not all arguments", 18, 0);
                    continue;
                }
                if (network == nullptr)
                {
                    send(clientSocket, "Project is not create", 22, 0);
                    continue;
                }
                std::list<bool> tempList;
                for (char c : values[1])
                {
                    std::cout << c << '\n';
                    if (c == '1')
                        tempList.push_back(1);
                    else if (c == '0')
                        tempList.push_back(0);
                    else
                    {
                        send(clientSocket, "Value is not correct", 21, 0);
                        continue;
                    }
                }
                std::cout << "-----------\n";
                for (auto pair : tempList)
                {
                    std::cout << pair << '\n';
                    //res.push_back(pair);
                }
                std::cout << "-----------\n";
                auto tempListt = network->Computation(tempList);//проблемма в комбиляции, то что там нету результата 
                std::string res;
                std::cout << tempListt.size() << ' ' << network->getNameProject() << '\n';
                for (auto pair : tempListt)
                {
                    std::cout << pair << '\n';
                    res.push_back(pair);
                }
                std::cout << "res: " << res << '\n';
                send(clientSocket, res.c_str(), res.size(), 0);
            }
            else if (temp.substr(0, temp.find("_")) == "SelectionOfWeights")
            {
                std::vector<std::string> values;
                splitString(temp, '_', values);
                if (values.size() < 2)
                {
                    send(clientSocket, "Not all arguments", 18, 0);
                    continue;
                }
                if (network == nullptr)
                {
                    send(clientSocket, "Project is not create", 22, 0);
                    continue;
                }
                if (values[1] == "0")
                {
                    network->SelectionOfWeights(0);
                }
                else if (values[1] == "1")
                {
                    network->SelectionOfWeights(1);
                }
                else
                {
                    send(clientSocket, "Value is not correct", 22, 0);
                }
                send(clientSocket, "OK", 2, 0);
            }
            else
            {
                send(clientSocket, "Not Corect command", 19, 0);
            }
        }
        // Закрытие сокетов
        closesocket(clientSocket);
        closesocket(listeningSocket);
        WSACleanup();
        if (network != nullptr)
        {
            delete network;
        }
    }
    else if (std::strcmp(argv[1], "DatasetTraining") == 0)
    {
        network = new ai::AI(argv[2]);
        //network->DatasetTraining(argv[3], std::stoi(argv[4]));
        delete network;
        return;
    }
    else
    {
        std::cout << "Not Corect command - ";
        for (size_t i = 0; i < argc; i++)
        {
            std::cout << argv[i] << ' ';
        }
        std::cout << '\n';
        return;
    }
}
