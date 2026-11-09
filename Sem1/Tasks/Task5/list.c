#include "list.h"

void error(char* status){
    printf("\nERROR!!!!! %s\n",status);
    while(getsym()!='\n');
    longjmp(begin,1);
}

void liststrreplace(char **str) {
    char *qur, *strnew, *s2, streuid[32], strshell[128];
    const char *strhome = getenv("HOME");
    const char *struser = getlogin();
    const char *struser2 = "UNKNOWN";
    realpath("shell", strshell);
    snprintf(streuid, sizeof(streuid), "%d", geteuid()); // Получает EUID текущего процесса и преобразует в строку

    char *new_str = realloc(*str, 1024);
    if (new_str == NULL) {
        free(*str);
        error("Memory allocation failed");
    }
    *str = new_str;

    while (1) {
        qur = strstr(*str, "$HOME");
        if (qur) {
            *qur = '\0'; // Разделяет строку на две части
            s2 = qur + 5; // Пропускает "$HOME"
            strnew = strdup(s2); // Копирует оставшуюся часть строки
            if (strnew == NULL) {
                error("Memory allocation failed");
            }
            strcat(*str, strhome); // Добавляет значение $HOME
            strcat(*str, strnew); // Добавляет оставшуюся часть
            free(strnew); // Освобождает временную строку
            continue;
        }
        qur = strstr(*str, "$USER");
        if (qur) {
            *qur = '\0'; // Разделяет строку
            s2 = qur + 6; // Пропускает "$USER"
            strnew = strdup(s2); // Копирует оставшуюся часть строки
            if (strnew == NULL) {
                error("Memory allocation failed");
            }
            strcat(*str, struser ? struser : struser2);
            strcat(*str, strnew); // Добавляет оставшуюся часть
            free(strnew); // Освобождает временную строку
            continue; // Возвращается к началу цикла
        }
        qur = strstr(*str, "$EUID");
        if (qur) {
            *qur = '\0'; // Разделяет строку
            s2 = qur + 6; // Пропускает "$EUID"
            strnew = strdup(s2); // Копирует оставшуюся часть строки
            if (strnew == NULL) {
                error("Memory allocation failed");
            }
            strcat(*str, streuid); // Добавляет значение $EUID
            strcat(*str, strnew); // Добавляет оставшуюся часть
            free(strnew); // Освобождает временную строку
            continue; // Возвращается к началу цикла
        }
        qur = strstr(*str, "$SHELL");
        if (qur) {
            *qur = '\0'; // Разделяет строку
            s2 = qur + 7; // Пропускает "$SHELL"
            strnew = strdup(s2); // Копирует оставшуюся часть строки
            if (strnew == NULL) {
                error("Memory allocation failed");
            }
            strcat(*str, strshell); // Добавляет значение $SHELL
            strcat(*str, strnew); // Добавляет оставшуюся часть
            free(strnew); // Освобождает временную строку
            continue; // Возвращается к началу цикла
        }
        break;
    }
}

void append(list *ls, char *s) {
    liststrreplace(&s); // Заменяет значения в строке
    if (*ls == NULL) {
        *ls = malloc(2 * sizeof(char *)); // Выделяет память для нового списка
        if (*ls == NULL) {
            error("Memory allocation failed");
        }
        (*ls)[0] = s; // Добавляет строку в список
        (*ls)[1] = NULL; // Завершает список NULL
    } else {
        int strlist_listlen = listlen(*ls); // Получает текущую длину списка
        char **new_ls = realloc(*ls, (strlist_listlen + 2) * sizeof(char *));
        if (new_ls == NULL) {
            error("Memory allocation failed");
        }
        *ls = new_ls; // Обновляет указатель на новый список
        (*ls)[strlist_listlen] = s; // Добавляет строку в список
        (*ls)[strlist_listlen + 1] = NULL; // Завершает список NULL
    }
}

void deletelist(list *ls) {
    if (ls == NULL || *ls == NULL) return;
    for (int i = 0; (*ls)[i] != NULL; i++) { // Освобождает каждую строку в списке
        free((*ls)[i]);
    }
    free(*ls);
    *ls = NULL;
}

int listlen( list ls){
    int len = 0;
    if (ls == NULL) return 0;
    while(*ls != NULL){
        len++;
        ls++;
    }
    return len;
}

void lssort(list *ls){
    int i, j, n = listlen(*ls);
    char *a;
    for (i = 0; i<n; i++){
        for(j = i + 1; j<n; j++){
            if(strcmp((*ls)[i],(*ls)[j])>0){
                a = (*ls)[i];
                (*ls)[i] = (*ls)[j];
                (*ls)[j] = a;		
            }
        }
    }
}

void printlist(list ls){
    int i, n = listlen(ls);
    for(i = 0; i<n; i++){
        printf("%s",ls[i]); // Печатает строку
        printf("%c",i != n-1 ? ' ' : '\n'); // Добавляет пробел или перевод строки
    }
}

int getsym(){
    return getchar();
}

int createlist(list *ls) {
    char *s;
    int cpred, k, c, i = 0, escign = 0, opsubshcount = 0;
    list wordls = NULL;
    c = getsym();
    while (c != EOF && c != '\n') {
        if (c == '\t' || c == ' ') {
            c = getsym();
            continue;
        }
        if (c == EOF || c == '\n') break;
        k = STRSIZE;
        s = (char *)malloc(k);
        if (c == '\\') {
            c = getsym();
            if (c == '\n' || c == EOF) break;
            s[0] = c;
            i = 1;
            c = ' ';
        } else if (c == '#') {
            while (c != '\n' && c != EOF) {
                c = getsym();
            }
            break;
        } else if (c == '"') {
            i = 0;
            c = getsym();
            while (c != '"' && c != EOF && c != '\n') {
                s[i] = c;
                i++;
                if (i == k - 1) {
                    k += STRSIZE;
                    s = (char *)realloc(s, k);
                }
                c = getsym();
            }
            s[i] = '\0';
            s = (char *)realloc(s, i + 1);
            append(&wordls, s);
            if (c == '"') c = getsym();
            continue;
        } else {
            s[0] = c;
            i = 1;
        }
        switch (c) {
            case '(':
                opsubshcount += 2;
            case ')':
                opsubshcount--;
                if (opsubshcount < 0) error("NO NEED )");
            case '<':
            case ';':  // служебные слова только из 1 символа
                s[1] = '\0';
                s = (char *)realloc(s, 2);
                append(&wordls, s);
                c = getsym();
                break;
            case '>':
            case '|':
            case '&':  // служебные слова из 1 или 2 символов
                cpred = c;
                c = getsym();
                if (c == cpred) {
                    s[0] = c;
                    s[1] = c;
                    s[2] = '\0';
                    s = (char *)realloc(s, 3);
                    c = getsym();
                } else {
                    s[1] = '\0';
                    s = (char *)realloc(s, 2);
                }
                append(&wordls, s);
                break;
            default:  // обычные слова без спецсимволов
                while (1) {
                    c = getsym();
                    switch (c) {
                        case EOF:
                        case '\n':
                            s[i] = '\0';
                            s = (char *)realloc(s, i + 1);
                            append(&wordls, s);
                            escign = 0;
                            break;
                        case '\\':
                            escign = 1;
                            c = getsym();
                            if (c == EOF || c == '\n') {
                                s[i] = '\0';
                                s = (char *)realloc(s, i + 1);
                                append(&wordls, s);
                                break;
                            }
                        case '<':
                        case '>':
                        case ' ':
                        case '|':
                        case '\t':
                        case '#':
                        case '"':
                        case '(':
                        case ')':
                        case '&':
                        case ';':
                            if (!escign) {
                                s[i] = '\0';
                                s = (char *)realloc(s, i + 1);
                                append(&wordls, s);
                                if (c == '#') {
                                    while (c != '\n' && c != EOF) {
                                        c = getsym();
                                    }
                                }
                                escign = 0;
                                break;
                            }

                        default: {
                            s[i] = c;
                            s[i + 1] = '\0';
                            i++;
                            if (i == k - 1) {
                                k += STRSIZE;
                                s = (char *)realloc(s, k);
                            }
                            continue;
                        }
                    }
                    break;
                }
        }
    }
    *ls = wordls;
    return -(c == EOF);
}