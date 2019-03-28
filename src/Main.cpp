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
#define SUCCESFULL	= 0


/***************************Variable Initialization***************************/
using namespace std;
int arrayWidth  = 0;
int arrayHeight = 0;
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
 * @brief      { file load and extract data }
 *
 * @param[in]  imageH  The image h
 * @param[in]  imageW  The image w
 *
 * @return     { 0 - SUCCESS , -1 = fail loading }
 */
int file_load( int imageH, int imageW)
{

    ifstream inFile;
    string rawInput = "";
    cin >> rawInput;
    cin >> rawInput;
    char fileLocation[rawInput.length() + 1];
    strcpy(fileLocation, rawInput.c_str()); 
    // cout << fileLocation << endl;
    cin >> rawInput;
    cin >> rawInput;
    string dimension[4];
    int pointerDimension = 0;
    for (int i = 0; i < rawInput.length(); i++)
    {
        if(rawInput[i] != ',')
        {
            dimension[pointerDimension] = dimension[pointerDimension] + rawInput[i];
        }
        else
        {
            pointerDimension++;
        }
    }
    imageH = strToInt(dimension[0]);
    imageW = strToInt(dimension[1]);
    arrayHeight = imageH;
    arrayWidth = imageW;
    char buffer[imageH * imageW];
    readArray = new int [imageH * imageW];  
    unsigned char buffer1;
    // open file

    inFile.open(fileLocation, ios::binary);
    inFile.read(buffer, imageH * imageW);
    
    for (int i = 0; i < sizeof(buffer); ++i)
    {
        buffer1 = (unsigned char)buffer[i];
        readArray[i] = (int)buffer1;
    }
    inFile.close();
    return 0;
}


/********************************************MAIN******************************************/
int main()
{
	if(file_load(arrayHeight, arrayWidth) == -1)
	{
		// cout << "********FILE READING FAIL*********" << endl;
		return 0;
	}
	detectPatch.create_file(readArray, arrayHeight, arrayWidth);
	detectPatch.scan_cluster();
	detectPatch.print_output();
	detectPatch.free_memory();
	return 0;
}