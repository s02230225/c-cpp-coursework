#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h> 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <poll.h>

#define MAX_QUEUE 5
#define BUF_SIZE 256
#define MAX_CLIENTS 10

typedef struct {
    int fd;
    char name[BUF_SIZE];
    int message_count;
} Client;

Client clients[MAX_CLIENTS];
int client_count = 0;

void broadcast_message(const char *message, int sender_fd) {
    for (int i = 0; i < client_count; i++) {
        write(clients[i].fd, message, strlen(message));
    }
}

void handle_client_message(int client_index, const char *buf) {
    clients[client_index].message_count++;
    if (strcmp(buf, "\\quit\n") == 0) {
        char message[BUF_SIZE];
        snprintf(message, sizeof(message), "%s покинул чат.\n", clients[client_index].name);
        broadcast_message(message, clients[client_index].fd);
        close(clients[client_index].fd);
        for (int i = client_index; i < client_count - 1; i++) {
            clients[i] = clients[i + 1];
        }
        client_count--;
    }
    else if (strcmp(buf, "\\users\n") == 0) {
        char message[BUF_SIZE * MAX_CLIENTS] = "Список пользователей:\n"; 
        for (int i = 0; i < client_count; i++) {
            strcat(message, clients[i].name);
            strcat(message, "\n");
        }
        write(clients[client_index].fd, message, strlen(message));
    }
    else if (strcmp(buf, "\\info\n") == 0) {
        int max_messages = 0;
        char *top_user = NULL;
        for (int i = 0; i < client_count; i++) {
            if (clients[i].message_count > max_messages) {
                max_messages = clients[i].message_count;
                top_user = clients[i].name;
            }
        }
        char message[BUF_SIZE];
        if (top_user != NULL) {
            snprintf(message, sizeof(message), "Пользователь с макс сообщениями: %s (%d штук)\n", top_user, max_messages);
        } else {
            snprintf(message, sizeof(message), "Нет пользователей.\n");
        }
        write(clients[client_index].fd, message, strlen(message));
    }
    else {
        char message[BUF_SIZE];
        snprintf(message, sizeof(message), "%s: %s\n", clients[client_index].name, buf);
        broadcast_message(message, clients[client_index].fd);
    }
}

int main(int argc, char *argv[]) {
    int main_socket, port, temp_socket, events;
    ssize_t n_read;
    char buf[BUF_SIZE];
    struct sockaddr_in adr;
    struct pollfd fds[MAX_CLIENTS + 1];
    if (argc < 2) {
        fprintf(stderr, "Забыл номер порта\n");
        return 1;
    }
    port = atoi(argv[1]);
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = INADDR_ANY;
    main_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (main_socket == -1) {
        perror("Не создался сокет");
        exit(1);
    }
    if (bind(main_socket, (struct sockaddr *)&adr, sizeof(adr)) == -1) {
        perror("Не привязался сокет к адресу");
        exit(1);
    }
    if (listen(main_socket, MAX_QUEUE) == -1) {
        perror("Не включилось прослушивание");
        exit(1);
    }
    fds[0].fd = main_socket;
    fds[0].events = POLLIN;
    while (1) {
        events = poll(fds, client_count + 1, -1);
        if (events == -1) {
            perror("Проблемы с poll");
            exit(1);
        }
        if (fds[0].revents & POLLIN) {
            temp_socket = accept(main_socket, NULL, NULL); 
            if (temp_socket == -1) {
                perror("Ошибка присоединения нового клиента");
                continue;
            }
            if (client_count < MAX_CLIENTS) {
                clients[client_count].fd = temp_socket;
                snprintf(clients[client_count].name, sizeof(clients[client_count].name), "User%d", client_count);
                clients[client_count].message_count = 0;
                client_count++;
                fds[client_count].fd = temp_socket;
                fds[client_count].events = POLLIN;
                char welcome_message[BUF_SIZE];
                snprintf(welcome_message, sizeof(welcome_message), "%s вошел в чат.\n", clients[client_count-1].name);
                broadcast_message(welcome_message, temp_socket);
            }
            else {
                close(temp_socket);
                write(temp_socket, "Слишком много людей\n", 20);
            }
        }
        for (int i = 1; i <= client_count; i++) {
            if (fds[i].revents & POLLIN) {
                n_read = read(fds[i].fd, buf, BUF_SIZE);
                if (n_read <= 0) {
                    close(fds[i].fd);
                    handle_client_message(i - 1, "\\quit");
                    fds[i] = fds[client_count];
                    i--;
                }
                else {
                    buf[n_read] = '\0';
                    handle_client_message(i - 1, buf);
                }
            }
        }
    }
    return 0;
}
