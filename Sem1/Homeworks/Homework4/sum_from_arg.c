/* sum (+) and (-) arg */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int ap=0, am=0, a;
    for (int i=1;i<argc;i++){
        a=(int)(strtol(argv[i], NULL, 10));
        if (a>=0) ap+=a;
        else am+=a;
    }
    printf("%d   %d\n", ap, am);
    return 0;
} 