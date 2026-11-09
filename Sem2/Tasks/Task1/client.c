#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 256

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr;
    char buf[BUF_SIZE];
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <IP> <Порт>\n", argv[0]);
        return 1;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Не удалось создать сокет");
        return 1;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Не удалось подключиться к серверу");
        close(sock);
        return 1;
    }
    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        FD_SET(STDIN_FILENO, &readfds); 
        if (select(sock + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("Ошибка select");
            break;
        }
        if (FD_ISSET(sock, &readfds)) {
            ssize_t n_read = read(sock, buf, BUF_SIZE);
            if (n_read <= 0) {
                printf("Соединение с сервером потеряно.\n");
                break;
            }
            buf[n_read] = '\0';
            printf("%s", buf);
        }
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            fgets(buf, BUF_SIZE, stdin);
            write(sock, buf, strlen(buf));
            if (strncmp(buf, "\\quit", 5) == 0) {
                break;
            }
        }
    }
    close(sock);
    return 0;
}
