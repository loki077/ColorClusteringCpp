#include <stdio.h> 
#include <stdlib.h> 

int **arr;

int **a;

int main() 
{ 
    a = new int*[10];
    for(int i = 0; i < 10; ++i)
    {
        a[i] = new int[10];
    }
    for (int i = 0; i <  10; i++) 
        for (int j = 0; j < 10; j++) 
            a[i][j] = 1;
             
    for (int i = 0; i <  10; i++) 
        for (int j = 0; j < 10; j++) 
            printf("%d ", a[i][j]); 

    int r = 3, c = 4, i, j, count; 
  
    arr = (int **)malloc(r * sizeof(int *)); 

    for (i=0; i<r; i++) 
        arr[i] = (int *)malloc(c * sizeof(int)); 
  
    // Note that arr[i][j] is same as *(*(arr+i)+j) 
    count = 0; 
    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         arr[i][j] = ++count;  // OR *(*(arr+i)+j) = ++count 
  
    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         printf("%d ", arr[i][j]); 
  
   /* Code for further processing and free the  
      dynamically allocated memory */
  
   return 0; 
} 
