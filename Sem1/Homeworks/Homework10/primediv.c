/* primediv */
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

int get_cnt_primediv(int num) {
    int res = 0, t;
    for (int i = 2; i <= num; i++) {
        if (is_prime(i)) {
            t = num;
            while (t % i == 0) {
                ++res;
                t = t / i;
            }
        }
    }
    return res;
}

int main() {
    unsigned int low, high, old_num;
    scanf("%d%d", &low, &high);
    int l;
    printf("%d\n", getpid());
    fflush(stdout);
    signal(SIGINT, hndlr_int);
    for (int i = high - 1; i >= low; i--) {
        sleep(1);
        l = get_cnt_primediv(i);
        cur_num = i;
    }
    printf("%d\n", 1);
    fflush(stdout);
    _exit(0);
}
