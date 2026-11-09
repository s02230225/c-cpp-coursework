#include "tree.h"

static list q = NULL; 

// Макрос для освобождения памяти в списке
#define FREE_LIST(ls) do { \
    q = *ls; \
    (*ls)++; \
    free(*q); \
    q = NULL; \
} while(0)

// Функция для создания отступа в выводе
void make_shift(int n){
    while(n--){
        if (n%5==0) putc('|', stderr); // Каждые 5 отступов выводим '|'
        else putc(' ', stderr);
    }
}

// Функция для печати аргументов командной строки
void print_argv(char **p, int shift){
    char **q=p;
    if(p!=NULL){
        while(*p!=NULL){
            make_shift(shift);
            fprintf(stderr, "argv[%d]=%s\n",(int) (p-q), *p);
            p++;
        }
    }
}

// Функция для рекурсивного печати дерева команд
int print_tree(tree t, int shift){
    char **p;
    int ans1, ans2, ans3;
    ans1=ans2=ans3=0;
    if(t==NULL)
        return 0; // Если узел пуст, возвращаем 0
    p=t->argv; // Получаем аргументы команды
    if(p!=NULL)
        print_argv(p, shift);
    else{
        make_shift(shift);
        fprintf(stderr, "psubshell\n"); // Если аргументов нет, выводим psubshell
    }
    make_shift(shift);
    // Печать входного файла
    if(t->infile==NULL)
        fprintf(stderr, "infile=NULL\n");
    else
        fprintf(stderr, "infile=%s\n", t->infile);
    
    // Печать выходного файла
    make_shift(shift);
    if(t->outfile==NULL)
        fprintf(stderr, "outfile=NULL\n");
    else
        fprintf(stderr, "outfile=%s\n", t->outfile);
    
    // Печать остальных параметров команды
    make_shift(shift);
    fprintf(stderr, "append=%d\n", t->append);
    make_shift(shift);
    fprintf(stderr, "background=%d\n", t->backgrnd);
    make_shift(shift);
    fprintf(stderr, "type=%s\n", t->type==NXT ? "NXT" : t->type==OR ? "OR" : "AND" );

    // Рекурсивный вызов для подкоманд
    make_shift(shift);
    if(t->psubcmd==NULL)
        fprintf(stderr, "psubcmd=NULL \n");
    else{
        fprintf(stderr, "psubcmd---> \n");
        ans1=print_tree(t->psubcmd, shift+5);
    }

    // Рекурсивный вызов для пайпов
    make_shift(shift);
    if(t->pipe==NULL)
        fprintf(stderr, "pipe=NULL \n");
    else{
        fprintf(stderr, "pipe---> \n");
        ans2=print_tree(t->pipe, shift+5);
        ans2+=1;
    }

    // Рекурсивный вызов для следующей команды
    make_shift(shift);
    if(t->next==NULL)
        fprintf(stderr, "next=NULL \n");
    else{
        fprintf(stderr, "next---> \n");
        ans3=print_tree(t->next, shift+5);
    }

    // Возвращаем максимальную глубину дерева
    if (ans2>ans1) ans1=ans2;
    if (ans3>ans1) ans1=ans3;
    return ans1;
}

// Функция для создания нового узла дерева
tree maketree(){
    tree t;
    t = (tree)malloc(sizeof(node)); // Выделяем память под узел
    // Инициализация полей узла
    t->argv = NULL;
    t->infile = NULL;
    t->outfile = NULL;
    t->append = 0;
    t->backgrnd = 0;
    t->psubcmd = NULL;
    t->pipe = NULL;
    t->next = NULL;
    t->type = NXT;
    return t;
}

// Функция для обработки простых команд
tree simplecommand(list *ls){
    if (isspecialword(**ls) && !isopshell(**ls)) error("WAITED COMMAND!!!");
    tree t;
    if (isopshell(**ls)){
        t = maketree();
        FREE_LIST(ls);
        t->psubcmd = buildsubshell(t,ls); // Строим подкоманду
        return t;
    }
    t = maketree();
    char *s = **ls;
    list argv = NULL; // Список аргументов
    while (!isspecialword(s)){
        append(&argv, s); // Добавляем аргумент в список
        (*ls)++;
        s = **ls;
    }
    t->argv = argv; // Присваиваем список аргументов
    modifinout(t,ls); // Модифицируем входные и выходные файлы
    return t;   
}

// Функция для обработки конвейеров команд
tree conveyer(list *ls){
    if (**ls == NULL ) return NULL;
    tree t1 = simplecommand(ls);
    while (isconv(**ls)){ // Пока встречаем конвейеры
        FREE_LIST(ls);
        t1->pipe = conveyer(ls); // Рекурсивно обрабатываем следующий конвейер
    }
    if (isback(**ls)){ // Если команда в фоне
        t1->backgrnd = 1;
    }
    return t1; // Возвращаем узел
}

// Функция для обработки логических операторов
tree andor(list *ls){
    if (**ls == NULL ) return NULL;
    tree t1 = conveyer(ls); // Обрабатываем конвейер
    while (isor(**ls) || isand(**ls)){ // Пока встречаем логические операторы
        if(isor(**ls)){
            FREE_LIST(ls);
            t1->next = andor(ls); // Рекурсивное построение дерева
            t1->type = OR; // Устанавливаем тип OR
        }
        if(isand(**ls)){
            FREE_LIST(ls);
            t1->next = andor(ls); // Рекурсивное построение дерева
            t1->type = AND; // Устанавливаем тип AND
        }
    }
    return t1; // Возвращаем узел
}

// Функция для построения дерева следующей команды
tree nexttree(list *ls){
    if (**ls == NULL ) return NULL;
    tree t1 = andor(ls); // Обрабатываем логические операторы
    while (isfollow(**ls) || isback(**ls)){ // Пока встречаем операторы следующей команды или фоновые
        if(isfollow(**ls)){
            FREE_LIST(ls);
            t1->next = buildtree(ls); // Строим следующее дерево
        }
        if(isback(**ls)){ // Если фон
            FREE_LIST(ls);
            if (**ls == NULL){
                // Пустой список, ничего не делаем
            }
            else if (!isspecialword(**ls)){ // Если не специальное слово
                t1->next = nexttree(ls); // Рекурсивное построение дерева
            }
            else if(isconv(**ls)){ // Если это конвейер
                FREE_LIST(ls);
                t1->pipe = buildtree(ls); // Строим дерево для пайпа
            }
            else if(isor(**ls) || isand(**ls)){ // Если это логический оператор
                error("WAITED STATUS OF BACKGRND PROCCES"); // Ошибка
            }
            else if(isfollow(**ls)){ // Если следующий оператор
                FREE_LIST(ls);
                t1->next = buildtree(ls); // Строим следующее дерево
            }
            else if(isback(**ls)){ // Если фон
                FREE_LIST(ls);
                t1->next = buildtree(ls); // Строим следующее дерево
                t1->backgrnd = 1; // Устанавливаем флаг фона
            }
            else if(isopshell(**ls)){ // Если это подкоманда
                FREE_LIST(ls);
                t1->psubcmd = buildsubshell(t1,ls); // Строим подкоманду
            }
            else error("WAITED COMMAND|"); // Ошибка
            t1->backgrnd = 1; // Устанавливаем флаг фона
        }
    }
    return t1; // Возвращаем узел
}

// Функция для модификации входных и выходных файлов
void modifinout(tree t, list *ls){
    char *s = **ls;
    if (isfrom(s)){ // Если это входной файл
        FREE_LIST(ls);
        s = **ls; // Получаем следующий элемент
        if (isspecialword(s)) error("WAITED FILE NAME"); // Ошибка, если не имя файла
        t->infile = s; // Устанавливаем имя входного файла
        (*ls)++;
        s = **ls; // Получаем следующий элемент
    }   
    if (isto(s)){ // Если это выходной файл
        FREE_LIST(ls);
        s = **ls; // Получаем следующий элемент
        if (isspecialword(s)) error("WAITED FILE NAME"); // Ошибка, если не имя файла
        t->outfile = s; // Устанавливаем имя выходного файла
        (*ls)++;
        s = **ls; // Получаем следующий элемент
    }   
    if (isappend(s)){ // Если это оператор добавления
        FREE_LIST(ls);
        s = **ls; // Получаем следующий элемент
        if (isspecialword(s)) error("WAITED FILE NAME"); // Ошибка, если не имя файла
        t->outfile = s; // Устанавливаем имя выходного файла
        t->append = 1; // Устанавливаем флаг добавления
        (*ls)++;
        s = **ls; // Получаем следующий элемент
    }
}

// Функция для построения дерева
tree buildtree(list *ls){
    tree t1;
    if (*ls == NULL) return NULL;
    t1 = nexttree(ls);
    if (**ls == NULL) return t1;
    if(isopshell(**ls)){ // Если это подкоманда
        FREE_LIST(ls);
        t1->psubcmd = buildsubshell(t1,ls); // Строим подкоманду
        if(**ls != NULL){
            modifinout(t1,ls); // Модифицируем входные и выходные файлы
            if(isconv(**ls)){ // Если это конвейер
                FREE_LIST(ls);
                t1->pipe = nexttree(ls); // Строим дерево для пайпа
            }
            if(isor(**ls)){ // Если это оператор OR
                FREE_LIST(ls);
                t1->next = nexttree(ls); // Строим следующее дерево
                t1->type = OR; // Устанавливаем тип OR
            }
            if(isand(**ls)){ // Если это оператор AND
                FREE_LIST(ls);
                t1->next = nexttree(ls); // Строим следующее дерево
                t1->type = AND; // Устанавливаем тип AND
            }
            if(isfollow(**ls)){ // Если это следующий оператор
                FREE_LIST(ls);
                t1->next = nexttree(ls); // Строим следующее дерево
            }
            if(isback(**ls)){ // Если это фон
                FREE_LIST(ls);
                t1->next = nexttree(ls); // Строим следующее дерево
                t1->backgrnd = 1; // Устанавливаем флаг фона
            }
        }
    }
    return t1; // Возвращаем узел
}

// Функция для построения подкоманды
tree buildsubshell(tree t1,list *ls){
    tree t;
    if(iscloseshell(**ls)){ // Если встретили закрывающую скобку
        FREE_LIST(ls);
        modifinout(t1,ls); // Модифицируем входные и выходные файлы
        return maketree(); // Возвращаем новый узел
    }
    t = buildtree(ls); // Строим дерево
    if(iscloseshell(**ls)){ // Если встретили закрывающую скобку
        FREE_LIST(ls);
        modifinout(t1,ls); // Модифицируем входные и выходные файлы
        return t; // Возвращаем построенное дерево
    }
    else error("WAITED )"); // Ошибка, если не закрывающая скобка
    return NULL; // Возвращаем NULL в случае ошибки
}

// Функция для удаления дерева
void delete_tree(tree *t){
    if(*t==NULL) return;
    if((*t)->argv != NULL) deletelist(&((*t)->argv)); // Освобождаем список аргументов
    if((*t)->outfile != NULL) free((*t)->outfile); 
    if((*t)->infile != NULL) free((*t)->infile);
    delete_tree(&(*t)->psubcmd);
    delete_tree(&(*t)->next);
    delete_tree(&(*t)->pipe);
    free(*t);
    *t = NULL;
}
