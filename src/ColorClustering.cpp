/********************************************************************************************
Project Name    : ColorClustering.cpp    -- getting number of patches of color in image
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 23-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept
********************************************************************************************/

/**************************************Library**********************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include "List2Dynamic.h"    	//developed by Lokesh
#include "List1Dynamic.h"		//developed by Lokesh
#include "ColorClustering.h"	//developed by Lokesh
/**************************************Main**********************************************/

/**
 * @brief      Creates a file.pr init for scan
 *
 * @param      tempBuffer  Input buffer for processing 2D array in 1D ;form of [y0:x0------y0:xM---y1:x0-------y1:xM.....] 
 * @param[in]  widthTemp   The width of array
 * @param[in]  heightTemp  The height of array
 */
void ColorClustering::create_file(int tempBuffer [], int heightTemp, int widthTemp) 
{
	resultList.init(5,5);
	resultColorList.init(5, 5);
	outputColorList.init(256);
	for (int i = 0; i < 256; ++i)
	{
		outputColorList.append(0);
	}
	this->widthMatrix = widthTemp;
	this->heightMatrix = heightTemp;
	//Dynamically creating 2D array
	this->inputArray = new int *[this->heightMatrix]; 
	this->assignArray = new int *[this->heightMatrix];  
    for (int i = 0; i < this->heightMatrix; i++) 
    {
        this->inputArray[i] = new int[this->widthMatrix];
        this->assignArray[i] = new int[this->widthMatrix];
    }

	int tempCounter = 0;
	for (int i = 0; i < this->heightMatrix; i++)
	{
		for (int z = 0; z < this->widthMatrix; z++)
		{
			this->inputArray[i][z] = tempBuffer[tempCounter]; 
			this->assignArray[i][z] = 0;
			tempCounter++;
		}
	}
}
/**
 * @brief      Scans for a cluster in the array.
 */
void ColorClustering::scan_cluster()
{
	for (this->yIndex = 0; this->yIndex < this->heightMatrix; this->yIndex++)
	{
		for (this->xIndex = 0; this->xIndex < this->widthMatrix; this->xIndex++)
		{	
			if(this->assignArray[this->yIndex][this->xIndex] == 0)
			{
				this->currentAssigned = 0;
				this->currentValue = this->inputArray[this->yIndex][this->xIndex];
				// cout << "not assigned- this->currentValue : " << this->xIndex << ' ' << this->yIndex << ' ' << this->currentValue << endl;

				 // scan of location previously assigned
				this->processed_location((this->xIndex - 1), (this->yIndex   ));
				this->processed_location((this->xIndex - 1), (this->yIndex - 1));
				this->processed_location((this->xIndex    ), (this->yIndex - 1));
				this->processed_location((this->xIndex + 1), (this->yIndex - 1));

				//  scan of location not assigned
				this->other_location((this->xIndex - 1), (this->yIndex + 1));
				this->other_location((this->xIndex    ), (this->yIndex + 1));
				this->other_location((this->xIndex + 1), (this->yIndex + 1));
				this->other_location((this->xIndex + 1), (this->yIndex    ));	
				
			}
			if(this->currentAssigned == 0)
			{
				this->assignCounter++;
				this->assignArray[this->yIndex][this->xIndex] = this->assignCounter;
				this->insert_new_match(this->assignCounter);
			}
			
		}
	}
	this->generate_output_array();		
}
/**
 * @brief      {Processing previous location which could have been already processesd}
 *
 * @param[in]  tempX  The x position 
 * @param[in]  tempY  The y position
 */
void ColorClustering::processed_location(int tempX, int tempY)
{
	if((tempX >= 0) && (tempX < this->widthMatrix) && (tempY >= 0) && (tempY < this->heightMatrix))
	{
		if(this->inputArray[tempY][tempX] == this->currentValue)
		{
			if(this->assignArray[tempY][tempX] != 0)
			{
				this->assignArray[this->yIndex][this->xIndex] = this->assignArray[tempY][tempX];
				this->currentAssigned = 1;
				// cout << " processed assigned : " << tempX << " " << tempY << endl;
			}
		}
	}
}
/**
 * @brief      { Processing of other location which are not been processesd}
 *
 * @param[in]  tempX  The temporary x
 * @param[in]  tempY  The temporary y
 *
 * @return     { 0 = value has been assigned, -1= out of boundary }
 */
int ColorClustering::other_location(int tempX, int tempY)
{
	if((tempX >= 0) && (tempX < this->widthMatrix) && (tempY >= 0) && (tempY < this->heightMatrix))
	{
		if(this->inputArray[tempY][tempX] == this->currentValue)
		{
			if(this->assignArray[this->yIndex][this->xIndex] == 0)
			{
				if(this->assignArray[tempY][tempX] == 0)
				{
					this->assignCounter++;
					this->assignArray[tempY][tempX] 	= this->assignCounter;
					this->assignArray[this->yIndex][this->xIndex] = this->assignCounter;
					this->currentAssigned = 1;
					this->insert_new_match(this->assignCounter);
					// cout << " other assigned 1 : " << tempX << " " << tempY << endl;
					return 0;	
				}
				else
				{
					this->assignArray[this->yIndex][this->xIndex] = this->assignArray[tempY][tempX];
					this->currentAssigned = 1;
					// cout << " other assigned 2 : " << tempX << " " << tempY << endl;
					return 0;
				}		
			}
			else if(this->assignArray[this->yIndex][this->xIndex] != this->assignArray[tempY][tempX])
			{
				if(this->assignArray[tempY][tempX] == 0)
				{
					this->assignArray[tempY][tempX] = this->assignArray[this->yIndex][this->xIndex];
					this->currentAssigned = 1;
					// cout << " other assigned 3 : " << tempX << " " << tempY << endl;
					return 0;	
				}
				else
				{
					// cout << " other assigned 4 : " << tempX << " " << tempY << endl;
					this->currentAssigned = 1;
					this->insert_match(this->assignArray[tempY][tempX], this->assignArray[this->yIndex][this->xIndex]);
					return 0;
				}
			}
		}
	}
	return -1;	
}

void ColorClustering::insert_match(int value1, int value2)
{
	int valueStored = 0;
	for (int x = 0; x < this->resultList.len() ; x++)
	{
		if(this->resultList.find_in_list(x, value1) == 0)
		{
			if(this->resultList.find_in_list(x, value2) == 0)
			{
				valueStored = 1;
			}
			else
			{
				this->resultList.append(x, value2);
				this->resultColorList.append(x, this->currentValue);					
				valueStored = 1;
			}
		}	
		else if(this->resultList.find_in_list(x, value2) == 0)
		{
			if(this->resultList.find_in_list(x, value1) == 0)
			{
				valueStored = 1;
			}			
			else
			{
				this->resultList.append(x, value1);
				this->resultColorList.append(x, this->currentValue);					
				valueStored = 1;
			}
		}
	}
	if (valueStored == 0)
	{
		this->resultList.append(value1);
		this->resultList.append_current(value2);
		this->resultColorList.append(this->currentValue);	
	}				
}

void ColorClustering::insert_new_match(int value1)
{
	int	valueStored = 0;
	for (int x = 0; x < this->resultList.len() ; x++)
	{
		if(this->resultList.find_in_list(x, value1) == 0)
		{
			valueStored = 1;
		}
	}
	if (valueStored == 0)
	{
		this->resultList.append(value1);
		this->resultColorList.append(this->currentValue);					
	}
}

void ColorClustering::generate_output_array()
{
	List1D tempList;
	tempList.init(256);
	for (int t = 0; t < this->resultList.len() ; t++)
	{		
		int checkRepeat = 0;
		for (int z = 0; z < this->resultList.len(t) ; z++)
		{
			if(tempList.find_in_list(this->resultList.get_value(t, z)) == 0)//{if this->resultList[t][z] in tempList:
			{
				checkRepeat = 1;
				break;
			}
		}
		for (int z = 0; z < this->resultList.len(t) ; z++)
		{
			tempList.append(this->resultList.get_value(t, z));// to change
		}

		if (checkRepeat == 0)
		{		
			int index = this->resultColorList.get_value(t, 0);
			int value = this->outputColorList.get_value(index);
			value++;
			this->outputColorList.set_value(index, value);
		}
	}
	tempList.free_memory();
}

void ColorClustering::print_input()
{
	cout << "[" << endl;
	for (int i = 0; i < this->widthMatrix; i++)
	{
		for (int z = 0; z < this->heightMatrix; z++)
		{
			cout << this->inputArray[i][z];
		}
		cout << endl;
	}
	cout << ']';
}

void ColorClustering::print_output()
{
 	this->outputColorList.print();
	
}
void ColorClustering::free_memory()
{

	for (int i = 0; i < this->widthMatrix; i++) 
    {
	    delete this->inputArray[i];
	    delete this->assignArray[i];
    }
    delete this->inputArray;
    delete this->assignArray;
	this->resultList.free_memory();
	this->resultColorList.free_memory();
	this->outputColorList.free_memory();
}