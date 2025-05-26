#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _WIN32_WINNT 0x0601

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#define DEFAULT_PORT "9999"
#define DEFAULT_BUFF_LEN 512

int __cdecl main(void)
{
    // Fill in getaddrinfo struct

    WSADATA wsaData;
    int iResult;
    char recvbuf[DEFAULT_BUFF_LEN];
    int iSendResult;
    int recvbuflen = DEFAULT_BUFF_LEN;

    SOCKET ListeningSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    if (iResult != 0)
    {
        printf("Cannot set addrinfo\n");
        WSACleanup();
        return 1;
    }

    // Listening socket defined

    ListeningSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListeningSocket == INVALID_SOCKET)
    {
        printf("Invaild Socket %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();

        return 2;
    }

    // Bind the socket

    iResult = bind(ListeningSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR)
    {
        printf("Cannot Bind %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListeningSocket);
        WSACleanup();

        return 3;
    }

    freeaddrinfo(result);

    //

    if (listen(ListeningSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Cannot Listen %ld\n", WSAGetLastError());
        closesocket(ListeningSocket);
        WSACleanup();

        return 4;
    }

    // ACCEPT A CONNECTION

    ClientSocket = INVALID_SOCKET;
    ClientSocket = accept(ListeningSocket, NULL, NULL);

    if (ClientSocket == INVALID_SOCKET)
    {
        printf("Cannot Accept %ld\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();

        return 5;
    }

    closesocket(ListeningSocket);

    do
    {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);

        if (iResult > 0)
        {

            iSendResult = send(ClientSocket, recvbuf, iResult, 0);

            if (iSendResult == SOCKET_ERROR)
            {
                printf("Cannot send %ld\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();

                return 6;
            }
            else
            {
                printf("Bytes received: %d\n", iResult);
            }
        }
        else if (iResult == 0)
        {
            printf("Closing Connection..........\n");
        }
        else
        {
            printf("Cannot recv/send %ld\n\r\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();

            return 7;
        }

    } while (iResult > 0);

    iResult = shutdown(ClientSocket, SD_SEND);

    if (iResult == SOCKET_ERROR)
    {
        printf("Invalid socket %ld", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();

        return 8;
    }
    // CLEANUP

    WSACleanup();
    closesocket(ClientSocket);
    return 0;
}
