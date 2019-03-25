#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>

using namespace std;
int **array;
int arrayCounter = 1;
int *arraySubCounter = 0;

void init();
void re_init();
void append();
void append_sub();


void append_sub(int location, int value)
{
    arraySubCounter[location]++;
    re_init();
    array[location][arraySubCounter[location] - 1] = value;
}
void append()
{
    arrayCounter++;
    re_init();
}
void print()
{
    for (int i = 0; i < arrayCounter; i++)
    {
        for (int z = 0; z < arraySubCounter[i]; z++)
        {
            cout << array[i][z] <<" ";
        }
        cout << endl;
    }
}
void init()
{
    array = (int **)malloc(arrayCounter * sizeof(int*)); 
    arraySubCounter = (int *)malloc(arrayCounter * sizeof(int*)); 
    for (int i = 0; i < arrayCounter; ++i) 
    {
        int tempSize = arraySubCounter[i];
        array[i] = new int[tempSize];
    }
}
void re_init()
{
    array = (int **)realloc(array, arrayCounter * sizeof(int*)); 
    arraySubCounter = (int *)realloc(arraySubCounter, arrayCounter * sizeof(int*)); 

    for (int i = 0; i < arrayCounter; ++i) 
    {
        int tempSize = arraySubCounter[i];
        array[i] = new int[tempSize];
    }
}
int main() 
{ 
    init();
    append();
    append_sub(arrayCounter, 1);
    append_sub(arrayCounter, 2);
    append_sub(arrayCounter, 3);
    print();
    free(array);
    free(arraySubCounter);
   return 0; 
} 
