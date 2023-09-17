#include <iostream>
#include <winsock2.h>
#include <clocale>
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

#define BUFLEN 2048
#define PORT 10115

bool ValidCommand = false;
int IsText = 0;

int IntParametrs[9];
std::string textp[1];

struct Command {
    std::string ocnova;
    std::vector<std::string> parametr;
};

Command ParseCommand(const std::string& String_Commanda) {
    Command command;

    int IntData;

    std::istringstream get_wo(String_Commanda);
    std::string MyWord;
    get_wo >> command.ocnova;

    int i = 0;
    while (get_wo >> MyWord) {
        if (MyWord == "-")
        {
            break;
        }
        command.ocnova += " " + MyWord;
    }

    if (command.ocnova == "clear display") {
        ValidCommand = false;
    }
    else if (command.ocnova == "draw pixel") {
        ValidCommand = false;
    }
    else if (command.ocnova == "draw line") {
        ValidCommand = false;
    }
    else if (command.ocnova == "draw rectangle")
    {
        ValidCommand = false;
    }
    else if (command.ocnova == "fill rectangle") {
        ValidCommand = false;
    }
    else if (command.ocnova == "draw ellipse") {
        ValidCommand = false;
    }
    else if (command.ocnova == "fill ellipse")
    {
        ValidCommand = false;
    }
    else if (command.ocnova == "draw circle")
    {
        ValidCommand = false;
    }
    else if (command.ocnova == "fill circle")
    {
        ValidCommand = false;
    }
    else if (command.ocnova == "draw rounded rectangle")
    {
        ValidCommand = false;
    }
    else if (command.ocnova == "fill rounded rectangle")
    {
        ValidCommand = false;
    }
    else if (command.ocnova == "draw text")
    {
        IsText = 1;
        ValidCommand = false;
    }
    else {
        ValidCommand = true;
    }


    if (!ValidCommand)
    {
        while (get_wo >> MyWord) {

            command.parametr.push_back(MyWord);
            try {
                IntData = std::stoi(MyWord);
            }
            catch (const std::invalid_argument& e) {
                if (IsText != 1)
                {
                    ValidCommand = true;
                    return command;
                }
                else {
                    textp[0] = MyWord;
                }
            }
            IntParametrs[i] = IntData;
            i++;
        }
        ValidCommand = false;
        IsText = 0;
        return command;
    }
    else {
        return command;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    system("title Serv");


    sockaddr_in serv, client;


    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cout << "Ошибка Winsock.";
        exit(0);
    }


    SOCKET sock_1;
    if ((sock_1 = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        std::cout << "Не удалось создать сокет.";
    }


    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);


    if (bind(sock_1, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR)
    {
        std::cout << "Bind не удался.";
        exit(EXIT_FAILURE);
    }
    while (true)
    {
        fflush(stdout);
        char message[BUFLEN] = {};


        int leng;
        int slen = sizeof(sockaddr_in);
        if (leng = recvfrom(sock_1, message, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
            std::cout << "recvfrom() получил ошибку.";
            exit(0);
        }

        std::istringstream givecom(message);
        std::string linecom;

        while (std::getline(givecom, linecom, '\n')) {
            Command command = ParseCommand(linecom);

            std::string firstWord, secondWord;
            std::istringstream nameStream(command.ocnova);
            nameStream >> firstWord >> secondWord;


            if (!ValidCommand) {
                std::cout << "Получена командa\n";
                std::cout << "Основная команда: " << command.ocnova << std::endl;
                std::cout << "Параметры:";
                for (const std::string& parametrs : command.parametr) {
                    std::cout << " " << parametrs;
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "Ошибка при получении команды!";
            }
            std::cout << std::endl;
        }
    }

    closesocket(sock_1);
    WSACleanup();
}
