/*  ejudge 4 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    char *elem;
} Node;

typedef struct List {
    Node *first;
    Node *last;
} List;




///////////////////////////////////////////////////////////////
// Функция для создания нового узла
Node *createNode(const char *elem) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        perror("Failed to allocate memory for new node");
        return NULL;
    }
    newNode->elem = strdup(elem); // Создает копию строки
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в конец списка
void appendNode(List *list, Node *newNode) {
    if (list->last) {
        list->last->next = newNode;
        newNode->prev = list->last;
    } else {
        list->first = newNode; // Если список пуст, новый узел также является первым
    }
    list->last = newNode; // Указываем новый узел как последний
}

// Функция для инициализации списка
void initList(List *list) {
    list->first = NULL;
    list->last = NULL;
}

// Функция для вывода списка
void printList(const List *list) {
    if (list->first==NULL){
        printf("pust\n");
        return;
    }
    Node *current = list->first;
    while (current) {
        printf("%s ", current->elem);
        current = current->next;
    }
}

// Функция для освобождения памяти
void freeList(List *list) {
    if (list->first==NULL){
        printf("pust\n");
        return;
    }
    Node *current = list->first;
    Node *next;
    while (current) {
        next = current->next;
        free(current->elem); // Освобождаем память для строки
        free(current);       // Освобождаем память для узла
        current = next;
    }
}




/* void process(struct List *pl, const char *str){
    if (pl->first==NULL || pl->last==NULL) return;
    struct Node *th=pl->first, *nthis=pl->first, *nlast=pl->last;
    int ans, rez=1;
    while (rez){
        if (th==NULL || th==pl->last) rez=0;
        nthis=th;
        ans=strcmp(th->elem, str);
                printf("\n!!! %s   ", nthis->elem);
                printList(pl);
        if (ans>0 && th!=pl->last) {
            if (th==pl->first) {
                pl->first=pl->first->next;
                //th->prev->next
                th->prev=nlast;
                th->prev->next=th;
                th->next->prev=NULL;
                th->next=NULL;
                //th->next->prev
                th=nthis->next;
            }
            else {
                //pl->first
                th->prev->next=th->next;
                th->prev=nlast;
                th->prev->next=th;
                th->next->prev=nthis->prev;
                th->next=NULL;
                //th->next->prev
                th=nthis->next;
            }
        }
        else if (ans==0) {
            if (th==pl->first) {
                pl->first=pl->first->next;
                //th->prev->next
                //th->prev
                //th->prev->next
                th->next->prev=NULL;
                //th->next
                //th->next->prev
                th=nthis->next;
                free(nthis->elem);
                free(nthis);
            }
            else {
                //pl->first=pl->first->next;
                th->prev->next=th->next;
                //th->prev
                //th->prev->next
                th->next->prev=nthis->prev;
                //th->next
                //th->next->prev
                th=nthis->next;
                free(nthis->elem);
                free(nthis);
            }
        }
        else th=nthis->next;
    }
    pl->last=nlast;
}
*/

void process(struct List *pl, const char *str) {
    int rez = 1;
    struct Node *th0, *thsave;
    struct Node *fst = pl->first;
    struct Node *lst = pl->last;
    th0 = fst;
    fst = (struct Node*)calloc(1, sizeof(struct Node));
    thsave = fst;
    fst->next = th0;
    if (th0 != NULL && th0->next != NULL) {
        while (th0 != NULL) {
            rez=strcmp(th0->elem, str);
            if (rez == 0) {
                fst->next = th0->next;
                if (th0->next != NULL) {
                    th0->next->prev = fst;
                    if (th0 == pl->first)
                        pl->first = pl->first->next;
                    if (th0 == lst) {
                        free(th0->elem);
                        free(th0);
                        th0 = NULL;
                    }
                    else {
                        free(th0->elem);
                        free(th0);
                        th0 = fst->next;
                    }
                }
                else {
                    if (pl->last != thsave)
                        pl->last = fst;
                    else
                        pl->last = NULL;
                    if (th0 == pl->first)
                        pl->first = th0->next;
                    fst->next = th0->next;
                    free(th0->elem);
                    free(th0);
                    th0 = fst->next;
                }
                rez = -1;
            }
            else if (rez > 0) {
                if (th0->next != NULL) {
                    fst->next = th0->next;
                    if (th0 == pl->first)
                        pl->first = th0->next;
                    pl->last->prev = th0->prev;
                    th0->prev = pl->last;
                    th0->next = NULL;
                    pl->last->next = th0;
                    pl->last = th0;
                    if (th0 == lst)
                        th0 = NULL;
                    else
                        th0 = fst->next;
                }
                else {
                    fst = th0;
                    if (th0 == lst)
                        th0 = NULL;
                    else 
                        th0=th0->next;
                }
                rez = -1;
            }
            else if (rez < 0) { 
                fst = th0;
                if (th0 == lst)
                        th0 = NULL;
                    else 
                        th0=th0->next;
            }
        }
    }
    else if (th0 != NULL && th0->next == NULL) {
        rez=strcmp(th0->elem, str);
        if (rez == 0) { 
            free(th0->elem);
            free(th0);
            pl->first = pl->last = NULL;
        }
    }
    free(thsave);
}






// Главная функция
int main() {
    List list;
    initList(&list);

    char buffer[256];
    printf("Введите строки (введите 'exit' для завершения):\n");

    while (1) {
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Удаляем символ новой строки

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        Node *newNode = createNode(buffer);
        if (newNode) {
            appendNode(&list, newNode);
        }
    }
    char* mystr="5";
    process(&list, mystr);
    printf("\nВведенные строки:\n");
    printList(&list);

    freeList(&list); // Освобождаем память перед выходом
    return 0;
}