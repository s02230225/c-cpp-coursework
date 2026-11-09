/* sort */
#include <stdio.h>

void bubble_sort(int m[], int n){
    register int i, j, k;
    for (i=n-1; i>=0; i--)
        for (j=0; j<i; j++)
            if (m[j]>m[j+1]){
                k=m[j+1];
                m[j+1]=m[j];
                m[j]=k;
            }
}
 
void insert_sort(int m[], int n){
    register int i, j, k;
    for (i=0; i<n; i++){
        k=i;
        for (j=i+1; j<n; j++)
            if (m[j]<m[k]) k=j;
    j=m[i];
    m[i]=m[k];
    m[k]=j;
    }
}
 
void selection_sort(int m[], int n){
    register int i, j, k, t;
    for (int i=0; i<n; i++){
        k=i;
        for (int j=i+1; j<n; j++)
            if (m[k]>m[j])
                k=j;
        t=m[k];
        m[k]=m[i];
        m[i]=t;
    }
}
 
int main(){
    int arr[] = {64, 25, 12, 22, 11};
    int N = sizeof(arr) / sizeof(arr[0]);
 
    printf("Unsorted array: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);}
    printf("\n");
  
    bubble_sort(arr, N); /*change*/
 
    printf("Sorted array: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);}
    printf("\n");
 
    return 0;
}