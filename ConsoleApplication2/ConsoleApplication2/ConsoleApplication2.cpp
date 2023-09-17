#include <iostream>
#include <winsock2.h>
#include <locale.h>
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 

#define SERVER "127.0.0.1"  
#define BUFLEN 2048 
#define PORT 10115


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    system("title Client");


    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        cout << "Ошибка. WinSock";
        return 1;
    }


    sockaddr_in server;
    int sock_cl;
    if ((sock_cl = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        cout << "Не удалось создать сокет.";
        return 2;
    }


    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);

    system("cls");
    while (true)
    {
        char message[BUFLEN];
        cout << "Введите Команду: ";
        cin.getline(message, BUFLEN);


        if (sendto(sock_cl, message, strlen(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            cout << "sendto() получил ошибку.";
            return 3;
        }


        char RecMes[BUFLEN] = {};

        int slen = sizeof(sockaddr_in);
        int RecMes_length;
        if (RecMes_length = recvfrom(sock_cl, RecMes, BUFLEN, 0, (sockaddr*)&server, &slen) == SOCKET_ERROR)
        {
            cout << "recvfrom() получил ошибку.";
            exit(0);
        }

        cout << endl << RecMes << endl << endl;
    }

    closesocket(sock_cl);
    WSACleanup();
}
