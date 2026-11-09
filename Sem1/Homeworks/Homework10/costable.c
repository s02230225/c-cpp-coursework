/* costable */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define _USE_MATH_DEFINES
double calculate_element(int i, int j, double x0, double s, int P) {
    return cos((x0 + j * s) * (i + 1) / P * M_PI);
}

int main(int argc, char** argv) {
    if (argc != 6) {
        fprintf(stderr, "Usage: Filename P x0 s K\n");
        return 1;
    }
    const char* file_name = argv[1];
    int P = atoi(argv[2]);
    double x0 = atof(argv[3]);
    double s = atof(argv[4]);
    int K = atoi(argv[5]);
    if (P <= 0 || s <= 0 || K < 0) {
        fprintf(stderr, "Invalid arguments. Must be: P > 0, s > 0, K >= 0\n");
        return 1;
    }
    size_t max_row_size = (K + 1) * 30;
    size_t shared_size = P * max_row_size;
    char* shared_string = mmap(NULL, shared_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_string == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    pid_t pids[P];
    memset(shared_string, 0, shared_size);
    for (int i = 0; i < P; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            return 1;
        } else if (pids[i] == 0) {
            char* row = shared_string + i * max_row_size;
            char buf[30];
            for (int j = 0; j <= K; j++) {
                double val = calculate_element(i, j, x0, s, P);
                snprintf(buf, sizeof(buf), " %.10g", val);
                strcat(row, buf);
            }
            strcat(row, "\n");
            exit(0);
        }
    }
    for (int i = 0; i < P; i++) {
        waitpid(pids[i], NULL, 0);
    }
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }
    fwrite(shared_string, sizeof(char), shared_size, file);
    fclose(file);
    munmap(shared_string, shared_size);
    return 0;
}
