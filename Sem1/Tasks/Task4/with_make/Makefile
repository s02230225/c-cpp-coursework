# Определение компилятора и флагов
CC = gcc
CFLAGS = -Wall -pedantic

# Исходные файлы
SRC_FILES = ls.c cat.c wc.c mv.c pwd.c echo.c
# Объектные файлы
OBJ_FILES = $(SRC_FILES:.c=.o)

# Исполняемые файлы
TARGETS = ls cat wc mv pwd echo

# Правило для сборки всех программ
all: $(TARGETS)

# Правила для создания исполняемых файлов
ls: ls.o
	$(CC) $(CFLAGS) -o $@ $^

cat: cat.o
	$(CC) $(CFLAGS) -o $@ $^

wc: wc.o
	$(CC) $(CFLAGS) -o $@ $^

mv: mv.o
	$(CC) $(CFLAGS) -o $@ $^

pwd: pwd.o
	$(CC) $(CFLAGS) -o $@ $^

echo: echo.o
	$(CC) $(CFLAGS) -o $@ $^

# Правило для сборки объектных файлов
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

# Очистка скомпилированных файлов
clean:
	rm -f $(OBJ_FILES) $(TARGETS)

# Установка правила по умолчанию
.PHONY: all clean
