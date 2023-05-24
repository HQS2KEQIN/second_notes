#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.13.60"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    // 创建客户端套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址和端口
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        // 从标准输入获取消息
        printf("客户端: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // 发送消息给服务器
        ssize_t bytesSent = write(clientSocket, buffer, strlen(buffer));
        if (bytesSent <= 0) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // 从服务器接收消息
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytesRead = read(clientSocket, buffer, BUFFER_SIZE - 1);
        if (bytesRead <= 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("服务器: %s", buffer);
    }

    // 关闭套接字
    close(clientSocket);

    return 0;
}
