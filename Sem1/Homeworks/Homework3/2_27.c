/* 2.27 */
#include <stdio.h>
#include <math.h>

int ibp(int a){
    return ((int) pow(2, a));
}

/* doubt */
int main(){
    int x, y, n, p;
    int xl, xr, y_elem;
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &n);
    scanf("%d", &p);
    xr = x % ibp(32-n-p+1);
    x /= ibp(32-n-p+1);
    xmid = x % ibp(n);
    xl = x /  ibp(n);

    y_elem = y / ibp(32-p+1);
    y_elem = !y_elem;

    x = xl * ibp(32-p+1);
    x += y_elem * ibp(32-n-p+1);
    x += xr; 

    printf("%d", x);
    return 0;
}