#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <iterator> 

using namespace std;
string finalFileName = "";
int arrayWidth  = 0;
int arrayHeight = 0;

int strToInt(string temp)
{
    int result = 0;
    if(temp.length() == 4)
    {
        result += (int(temp[0])- 48) * 1000;
        result += (int(temp[1])- 48) * 100;
        result += (int(temp[2])- 48) * 10;
        result += (int(temp[3])- 48) * 1;
    }
    else if(temp.length() == 3)
    {
        result += (int(temp[0])- 48) * 100;
        result += (int(temp[1])- 48) * 10;
        result += (int(temp[2])- 48) * 1;
    }
    else if(temp.length() == 2)
    {
        result += (int(temp[0])- 48) * 10;
        result += (int(temp[1])- 48) * 1;
    }
    else if(temp.length() == 1)
    {
        result = (int(temp[0])- 48) * 1;
    }
    // cout << result << endl;
    return result;
}

int get_arg(int argcTemp, char *argvTemp[], string *fileName, int *imageW, int *imageH)
{
	int validation = 0;
    string dimension[4];
    int pointerDimension = 0;
    if(argcTemp == 4)
    {
        *fileName = argvTemp[1];
        validation++;
        string temp = argvTemp[3];
	    for (int i = 0; i < temp.length(); i++)
	    {
	        if(argvTemp[3][i] != ',')
	        {
	            dimension[pointerDimension] = dimension[pointerDimension] + argvTemp[3][i];
	        }
	        else
	        {
	            pointerDimension++;
	            validation++;
	        }
	    }
	    *imageH = strToInt(dimension[0]);
	    *imageW = strToInt(dimension[1]);
	    if(validation == 2)
	    { 
	    	return 0; 
	    }

	    else
	    { 
	    	return -2; 
	    }
    }
    else
    { 
    	return -1; 
    }

}

int main( int argc, char *argv[] )  
{
	int returnValue = get_arg(argc, argv, &finalFileName, &arrayWidth, &arrayHeight);
    cout << finalFileName << endl;
    cout << arrayWidth << endl;
    cout << arrayHeight << endl;
    cout << returnValue << endl;
}