/* ln */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int myln(int argc, char* argv[]){
    if (argc > 4 || argc < 3) {
        fprintf(stderr, "Wrong number of args! Usage: [-s] <original_link> <new_link>\n");
        return 1;
    }
    errno = 0;
    int flag = 0;
    
    if (argv[1][0] == '-' && argv[1][1] == 's' && argv[1][2] == '\0') {
        flag = 1;
    }
    else if (argc == 4) {
        flag = 0;
    }
    else {
        fprintf(stderr, "Wrong number of args! Usage: [-s] <original_link> <new_link>\n");
        return 1;
    }

    if (flag) {
        if (symlink(argv[2], argv[3]) < 0) {
            fprintf(stderr, "Error in symlink: %s", strerror(errno));
            return 1;
        }
    }
    else {
        if (link(argv[1], argv[2]) < 0) {
            fprintf(stderr, "Error in link: %s", strerror(errno));
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    myln(argc, argv);
}
