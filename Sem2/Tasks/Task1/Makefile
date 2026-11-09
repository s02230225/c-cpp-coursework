# Определение компилятора и флагов
CC = gcc
CFLAGS = -Wall -pedantic

# Исходные файлы
SRC_FILES = server.c client.c
# Объектные файлы
OBJ_FILES = $(SRC_FILES:.c=.o)

# Исполняемые файлы
TARGETS = server client

# Правило для сборки всех программ
all: $(TARGETS)

# Правила для создания исполняемых файлов
server: server.o
	$(CC) $(CFLAGS) -o $@ $^

client: client.o
	$(CC) $(CFLAGS) -o $@ $^

# Правило для сборки объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Очистка скомпилированных файлов
clean:
	rm -f $(OBJ_FILES) $(TARGETS)

# Установка правила по умолчанию
.PHONY: all clean
