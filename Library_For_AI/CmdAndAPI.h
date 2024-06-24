#pragma once
#include "AI.h"
#include <cstring>
#include <winsock2.h>
#include <sstream>
#pragma comment(lib, "ws2_32.lib")
class CmdAndAPI
{
    bool createNetwork(WSADATA& wsaData, SOCKET& listeningSocket)
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Ошибка инициализации Winsock." << std::endl;
            return false;
        }
        listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (listeningSocket == INVALID_SOCKET) {
            std::cerr << "Ошибка создания сокета." << std::endl;
            WSACleanup();
            return false;
        }
        return true;
    }

    void splitString(const std::string& str, char delimiter, std::vector<std::string>& tokens)
    {
        std::stringstream ss(str);
        std::string item;
        while (std::getline(ss, item, delimiter)) {
            tokens.push_back(item);
        }
    }
public:
    void commandInput(int argc, char* argv[]);
};