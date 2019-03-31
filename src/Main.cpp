/********************************************************************************************
Project Name    : Color Clusturing with input from .bin file and dimension
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 22-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept

FileTerminal Input : count-areas <input-filename> --shape <height>,<width>"
eg: count-areas /home/lokesh/Desktop/Projects/ColorClusteringCpp/data/sample.bin --shape 256,256
********************************************************************************************/

/***************************Library Import***************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <bits/stdc++.h> 

/***************************Developedby Me for this Project****************/
#include "List2Dynamic.h"		//developed by Lokesh
#include "List1Dynamic.h"		//developed by Lokesh
#include "ColorClustering.h"	//developed by Lokesh

/*******MACROS#*******/ 
#define ERROR 		= -1;
#define SUCCESFULL	= 0;


/***************************Variable Initialization***************************/
using namespace std;
int arrayWidth  = 0;
int arrayHeight = 0;
string finalFileName = "";
int *readArray;
int *tempBuffer = new int [ arrayHeight * arrayWidth]; 
ColorClustering detectPatch;

/***************************************Functions*********************************/
/**
 * @brief      { strin to int conversion }
 *
 * @param[in]  temp  The temporary
 *
 * @return     { final int value }
 */
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
/**
 * @brief      { function_description }
 *
 * @param[in]  name  The name
 *
 * @return     { description_of_the_return_value }
 */
inline bool file_exist(const string& name) 
{
    return ( access( name.c_str(), F_OK ) != -1 );
}

/**
 * @brief      { file load and extract data }
 *
 * @param[in]  imageH  The image h
 * @param[in]  imageW  The image w
 *
 * @return     { 0 - SUCCESS , -1 = fail loading }
 */
int file_load( string fileLocationTemp, int imageHTemp, int imageWTemp)
{

    ifstream inFile;
    cout << imageHTemp << " " << imageWTemp << " " << fileLocationTemp << endl;

    char buffer[imageHTemp * imageWTemp];
    readArray = new int [imageHTemp * imageWTemp];  
    unsigned char buffer1;
    char fileLocation[fileLocationTemp.length() + 1];
    strcpy(fileLocation, fileLocationTemp.c_str());

    inFile.open(fileLocation, ios::binary);
    inFile.read(buffer, imageHTemp * imageWTemp);
    
    for (int i = 0; i < sizeof(buffer); ++i)
    {
        buffer1 = (unsigned char)buffer[i];
        readArray[i] = (int)buffer1;
    }
    inFile.close();
    return 0;
}

/**
 * @brief      Gets the argument.
 *
 * @param[in]  argcTemp  The argc temporary
 * @param      argvTemp  The argv temporary
 * @param      fileName  The file name
 * @param      imageW    The image w
 * @param      imageH    The image h
 *
 * @return     The argument.
 */
int get_arg(int argcTemp, char *argvTemp[], string *fileName, int *imageW, int *imageH)
{
    string dimension[4];
    int pointerDimension = 0;
    if(argcTemp == 4)
    {
        *fileName = argvTemp[1];
        if(file_exist(*fileName) == 0)
        {
            return -3;            
        }
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
            }
        }
        *imageH = strToInt(dimension[0]);
        *imageW = strToInt(dimension[1]);
        if(pointerDimension == 1)
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



/*----------------------------------Main---------------------------------------*//**
 * MAIN
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 *
 * @return     { description_of_the_return_value }
 */
int main(int argc, char *argv[])
{
    if(get_arg(argc, argv, &finalFileName, &arrayWidth, &arrayHeight) !=0)
    {
        cout << "********FILE READING FAIL 1*********" << endl;
        return 0;
    }
    if(file_load(finalFileName, arrayHeight, arrayWidth) != 0)
	{
		cout << "********FILE READING FAIL 2*********" << endl; 
		return 0;
	}
    cout << finalFileName << endl;
    cout << arrayHeight << endl;
    cout << arrayWidth << endl;

	detectPatch.create_file(readArray, arrayHeight, arrayWidth);
	detectPatch.scan_cluster();
	detectPatch.print_output();
	detectPatch.free_memory();
	return 0;
}