/* sum with overflow */
#include <stdio.h>

enum{ MY_INT_MAX = ~0u >> (~0u / ~0u),
	MY_INT_MIN = ~MY_INT_MAX
};

int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	int s = a+b;
	if (s<0 && a>0 && b>0) 
		printf("%d\n", MY_INT_MAX);
	else if (s>0 && a<0 && b<0)
		printf("%d\n", MY_INT_MIN);
	else
		printf("%d\n", s);
    return 0;
}
