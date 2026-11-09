# Определение компилятора и флагов
CC = gcc
CFLAGS = -Wall -pedantic

# Исходные файлы
SRC_FILES = cp.c ln.c grep.c cmp.c tail.c od.c
# Объектные файлы
OBJ_FILES = $(SRC_FILES:.c=.o)

# Исполняемые файлы
TARGETS = cp ln grep cmp tail od

# Правило для сборки всех программ
all: $(TARGETS)

# Правила для создания исполняемых файлов
cp: cp.o
	$(CC) $(CFLAGS) -o $@ $^

ln: ln.o
	$(CC) $(CFLAGS) -o $@ $^

grep: grep.o
	$(CC) $(CFLAGS) -o $@ $^

cmp: cmp.o
	$(CC) $(CFLAGS) -o $@ $^

tail: tail.o
	$(CC) $(CFLAGS) -o $@ $^

od: od.o
	$(CC) $(CFLAGS) -o $@ $^

# Правило для сборки объектных файлов
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

# Очистка скомпилированных файлов
clean:
	rm -f $(OBJ_FILES) $(TARGETS)

# Установка правила по умолчанию
.PHONY: all clean
