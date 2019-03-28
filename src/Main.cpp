/********************************************************************************************
Project Name    : Color Clusturing with input from .bin file and dimesion
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 22-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept
********************************************************************************************/

/***************************Library Import***************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
/***************************Developedby Me for this Project****************/
#include "List2Dynamic.h"		//developed by Lokesh
#include "List1Dynamic.h"		//developed by Lokesh
#include "ColorClustering.h"	//developed by Lokesh

/*******MACROS#*******/ 
#define ERROR 		= -1;
#define SUCCESFULL	= 0


/***************************Variable Initialization***************************/
using namespace std;
string name 	= "";
int arrayWidth 	= 256;
int arrayHeight = 256;
int *readArray;
int *tempBuffer = new int [ arrayHeight * arrayWidth]; 

int file_load( int imageH, int imageW)
{
    char buffer[imageH * imageW];
    unsigned char buffer1;
    readArray = new int [imageH * imageW];  
    string fileLocation = "";
    ifstream inFile;
   
    // open file
    fileLocation = "/home/lokesh/Desktop/Projects/ColorGrouping/data/sample.bin";
    inFile.open("/home/lokesh/Desktop/Projects/ColorClusteringCpp/data/sample.bin", ios::binary);
    inFile.read(buffer, imageH * imageW);
    
    for (int i = 0; i < sizeof(buffer); ++i)
    {
	   	buffer1 = (unsigned char)buffer[i];
        readArray[i] = (int)buffer1;
    }
    inFile.close();
    return 0;
}

ColorClustering detectPatch;
int main()
{
	if(file_load(arrayHeight, arrayWidth) == -1)
	{
		cout << "********FILE READING FAIL*********" << endl;
		return 0;
	}
	detectPatch.create_file(readArray, arrayHeight, arrayWidth);
	detectPatch.scan_cluster();
	detectPatch.print_output();
	// detectPatch.free_memory();
	return 0;
}