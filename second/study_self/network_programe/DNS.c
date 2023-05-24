#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char buffer[BUFFER_SIZE];

    // 创建服务器套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址和端口
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // 绑定服务器套接字到指定地址和端口
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(serverSocket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("等待客户端连接...\n");

    // 接受客户端连接
    socklen_t clientAddressLength = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientSocket < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("客户端已连接\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        // 从客户端接收消息
        ssize_t bytesRead = read(clientSocket, buffer, BUFFER_SIZE - 1);
        if (bytesRead <= 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("客户端: %s", buffer);

        // 从标准输入获取消息
        printf("服务器: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // 发送消息给客户端
        ssize_t bytesSent = write(clientSocket, buffer, strlen(buffer));
        if (bytesSent <= 0) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    // 关闭套接字
    close(clientSocket);
    close(serverSocket);

    return 0;
}
