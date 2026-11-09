/* prime */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int count = 1;
unsigned int cur_num = 0;

void hndlr_int(int s) {
    if (count++ < 4) {
        printf("\n%d\n", cur_num);
        fflush(stdout);
    } else
        _exit(0);
}

void hndlr_term(int s){
    _exit(0);
}

int is_prime(int n) {
    for (int i = 2; i <= n / 2; ++i)
        if (n % i == 0) return 0;
    return 1;
}

int get_prime_num(int low, int high) {
    for (int i = low + 1; i < high; ++i) {
        if (is_prime(i)) return i;
    }
    return cur_num;
}

int main() {
    unsigned int low, high, old_num;
    scanf("%u%u", &low, &high);
    printf("%d\n", getpid());
    fflush(stdout);
    signal(SIGINT, hndlr_int);
    signal(SIGTERM, hndlr_term);
    while (1) {
        sleep(1);
        old_num = cur_num;
        cur_num = get_prime_num(low, high);
        if (old_num == cur_num) {
            printf("%d\n", -1);
            fflush(stdout);
            _exit(0);
        }
        low = cur_num;
    }
}
