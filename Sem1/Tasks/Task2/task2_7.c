/*  task2_7 */
#include <stdio.h>
#include <setjmp.h>
#include <math.h>

jmp_buf begin;
char curlex;

void error();
void getlex();
int expr(); 
int term(); 
int power();

int main() {
    int result;
    setjmp(begin);
    printf("==> ");
    getlex();
    result = expr();
    if (curlex != '\n') error();
    printf("\n%d\n", result);
    return 0;
}

void error() {
    printf("\nERROR!\n");
    while (getchar() != '\n');
    longjmp(begin, 1);
}

void getlex() {
    while ((curlex = getchar()) == ' ')
        {}
}

int expr() {
    int e = term();
    while (curlex == '+' || curlex == '-') {
        char op = curlex;
        getlex();
        if (op == '+') {
            e += term();
        } else {
            e -= term();
        }
    }
    return e;
}

int term() {
    int t = power();
    while (curlex == '*' || curlex == '/') {
        char op = curlex;
        getlex();
        if (op == '*') {
            t *= power();
        } else {
            int divisor = power();
            if (divisor == 0) error();
            t /= divisor;
        }
    }
    return t;
}

int power() {
    int base = 0;
    switch(curlex) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            base = curlex - '0';
            break;
        case '(':
            getlex();
            base = expr();
            if (curlex != ')') error();
            break;
        default: error();
    }
    getlex();
    if (curlex == '^') {
        getlex();
        int exponent = power();
        base = (int)pow(base, exponent);
    }
    return base;
}