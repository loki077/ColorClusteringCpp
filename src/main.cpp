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
#include <list>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>

/*******MACROS#*******/ 
#define ERROR 		= -1;
#define SUCCESFULL	= 0


/***************************Variable Initialization***************************/
using namespace std;
string name = "";
int arrayWidth = 256;
int arrayHeight = 256;
int * inputData;

class ColorClustering
{
	public:
		int xIndex = 0;
		int yIndex = 0;
		int widthMatrix  = 0;
		int heightMatrix = 0;
		int currentValue = 0;
		int currentAssigned = 0;
		int assignCounter   = 0;
		int  **inputArray;
		int  **assignArray;

		list <int> resultStringList, resultColorList;
		list <int> outputColorList;

		void create_file(int tempBuffer [], int widthTemp, int heightTemp);
		void scan_cluster();
		// void print_output();
		// void generate_output_array();
		// void color_image_output();
		void processed_location(int tempX, int tempY);
		int other_location(int tempX, int tempY);
		// void insert_match(int value1, int value2);
		// void insert_new_match(int value1);
};

void ColorClustering::create_file(int tempBuffer [], int widthTemp, int heightTemp) 
{
	widthMatrix = widthTemp;
	heightMatrix = heightTemp;
	//Dynamically creating 2D array
	inputArray = new int *[widthMatrix]; 
	assignArray = new int *[widthMatrix];  
    for (int i = 0; i < widthMatrix; ++i) 
    {
        inputArray[i] = new int[heightMatrix];
        assignArray[i] = new int[heightMatrix];
    }

	int tempCounter = 0;
	for (int i = 0; i < widthMatrix; ++i)
	{
		for (int z = 0; z < heightMatrix; ++z)
		{
			inputArray[i][z] = 1; 
			inputArray[i][z] = tempBuffer[tempCounter]; 
			tempCounter++;
		}
	}
}
void ColorClustering::scan_cluster()
{
	for (int xIndex = 0; xIndex < widthMatrix; xIndex++)
	{
		for (int yIndex = 0; yIndex < heightMatrix; yIndex++)
		{	
			if(assignArray[xIndex][yIndex] == 0)
			{
				currentAssigned = 0;
				currentValue = inputArray[xIndex][yIndex];

				 // scan of location previously assigned
				processed_location((xIndex - 1), (yIndex   ));
				processed_location((xIndex - 1), (yIndex - 1));
				processed_location((xIndex    ), (yIndex - 1));
				processed_location((xIndex + 1), (yIndex - 1));

				//  scan of location not assigned
				other_location((xIndex - 1), (yIndex + 1));
				other_location((xIndex    ), (yIndex + 1));
				other_location((xIndex + 1), (yIndex + 1));
				other_location((xIndex + 1), (yIndex    ));		
			}
			if(currentAssigned == 0)
			{
				assignCounter ++;
				assignArray[xIndex][yIndex] = assignCounter;
				// insert_new_match(assignCounter);
			}
		}
	}
	// generate_output_array(resultStringList);		
}
void ColorClustering::processed_location(int tempX, int tempY)
{
	if((tempX >= 0) && (tempX < widthMatrix) && (tempY >= 0) && (tempY < heightMatrix))
	{
		if(inputArray[tempX][tempY] == currentValue)
		{
			if(assignArray[tempX][tempY] != 0)
			{
				assignArray[xIndex][yIndex] = assignArray[tempX][tempY];
				currentAssigned = 1;
			}
		}
	}
}

int ColorClustering::other_location(int tempX, int tempY)
{
	if((tempX >= 0) && (tempX < widthMatrix) && (tempY >= 0) && (tempY < heightMatrix))
	{
		if(inputArray[tempX][tempY] == currentValue)
		{
			if(assignArray[xIndex][yIndex] == 0)
			{
				if(assignArray[tempX][tempY] == 0)
				{
					assignCounter++;
					assignArray[tempX][tempY] 	= assignCounter;
					assignArray[xIndex][yIndex] = assignCounter;
					currentAssigned = 1;
					return 1;	
				}
				else
				{
					assignArray[xIndex][yIndex] = assignArray[tempX][tempY];
					currentAssigned = 1;
					return 1;
				}		
			}
			else if(assignArray[xIndex][yIndex] != assignArray[tempX][tempY])
			{
				if(assignArray[tempX][tempY] == 0)
				{
					assignArray[tempX][tempY] = assignArray[xIndex][yIndex];
					currentAssigned = 1;
					return 1;	
				}
				else
				{
					// insert_match(assignArray[tempX][tempY], assignArray[xIndex][yIndex]);
					currentAssigned = 1;
					return 1;
				}
			}
		}
	}
	return 0;	
}

int file_load(int imageW, int imageH)
{
    char buffer[imageW * imageH];
    inputData = (int *)malloc(imageW * imageH * sizeof(int)); 
    string fileLocation = "";
    cout << "count-areas ";
    cin >> fileLocation;
    fileLocation = "/home/lokesh/Desktop/Projects/ColorGrouping/data/sample.bin";
    ifstream myFile ("/home/lokesh/Desktop/Projects/ColorClusteringCpp/data/sample.bin", ios::binary);
    
    if (!myFile.read (buffer, imageW * imageH)) 
    {
        return -1;
    }
    for (int i = 0; i < sizeof(buffer); ++i)
    {
        inputData[i] = (int)buffer[i];
        cout << inputData[i];
    }
    return 0;
}

ColorClustering scan1;

int main()
{
	if(file_load(arrayWidth, arrayHeight) == -1)
	{
		cout << "********FILE READING FAIL*********" << endl;
		return 0;
	}
	scan1.create_file(inputData, arrayWidth, arrayHeight);
	return 0;
}