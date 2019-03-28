/********************************************************************************************
Project Name    : List2Dynamic.cpp     --- 2 Dimensional dynamical Array
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
#include "List2Dynamic.h"
	
/**
 * @brief      Gets the value.
 *
 * @param[in]  pointer   1D pointer
 * @param[in]  pointer1  2D pointer
 *
 * @return     The value you want -1 wrong memory access
 */
int List2D::get_value(int pointer, int pointer1)
{
	if(pointer < this->usedSizeOfMainArray)
	{
		if(pointer1 < this->subArrayUsedSize[pointer])
		{
			return this->inputArray[pointer][pointer1];
		}
	}
	return -1;
}

/**
 * @brief      Sets the value in List.
 *
 * @param[in]  pointer   1D pointer
 * @param[in]  pointer1  2D pointer
 * @param[in]  value     The value to set in position
 *
 * @return     { 0 = Succesfull , -1 = wrong memory access }
 */
int List2D::set_value(int pointer, int pointer1, int value)
{
	if(pointer < this->usedSizeOfMainArray)
	{
		if(pointer1 < this->subArrayUsedSize[pointer])
		{
			this->inputArray[pointer][pointer1] = value;
			return 0;
		}
	}
	return -1;
}

/**
 * @brief      { Initiallizing the List }
 *
 * @param[in]  mainArraySize  The main array size
 * @param[in]  subArraySize   The sub array size
 */
void List2D::init(int mainArraySize, int subArraySize)
{	
	this->maxSizeOfMainArray = mainArraySize;
	this->maxSizeOfSubArray  = subArraySize;
	this->subArrayUsedSize 	 = new int [this->maxSizeOfMainArray];  
	this->inputArray = new int *[this->maxSizeOfMainArray];
	for (int i = 0; i < this->maxSizeOfMainArray; i++) 
    {
        this->inputArray[i] = new int[this->maxSizeOfSubArray];
    }
    this->init_zero();
}
void List2D::init_zero()
{
	for (int i = 0; i < this->maxSizeOfMainArray; i++)
	{
		for (int z = 0; z < this->maxSizeOfSubArray; z++)
		{
			this->inputArray[i][z] = 0;
		}
		this->subArrayUsedSize[i] = 0;
	}
}
/**
 * @brief      { To find value in list }
 *
 * @param[in]  pointer  The pointer position 
 * @param[in]  value    The value to search
 *
 * @return     { 0 = Succesfull , -1 = Not present }
 */
int List2D::find_in_list(int pointer, int value)
{
	if (pointer < this->usedSizeOfMainArray)
	{
		for (int i = 0; i < this->subArrayUsedSize[pointer]; i++)
		{
			if(this->inputArray[pointer][i] == value)
			{
				return 0;
			}
		}
		return -1;
	}
	return -2;
}

/**
 * @brief      { To Print List}
 */
void List2D::print()
{
	cout << this->maxSizeOfMainArray;
	cout << '['<< endl;
	for (int i = 0; i < this->maxSizeOfMainArray; i++)
	{
		cout << this->maxSizeOfSubArray << ": ";
		for (int z = 0; z < this->maxSizeOfSubArray; z++)
		{
			cout << this->inputArray[i][z] << " ";
		}
		cout << endl;
	}
	cout << ']' << endl;
}

/**
 * @brief      Appends into 1stD of array.
 *
 * @param[in]  value   The value to append in list
 */
int List2D::append(int value)
{
	this->inputArray[this->usedSizeOfMainArray][this->subArrayUsedSize[this->usedSizeOfMainArray]] = value;
	this->subArrayUsedSize[this->usedSizeOfMainArray]++;
	this->usedSizeOfMainArray++;	
	this->check_size();
	return 0;
}

/**
 * @brief      Appends into 2ndD of array with position access.
 *
 * @param[in]  pointer  The pointer of first dimension
 * @param[in]  value    The value
 *
 * @return     { 0 = Succesfull, -1 = wrong position access  }
 */
int List2D::append(int pointer, int value)
{
	if(pointer > this->usedSizeOfMainArray)
	{
		return -1;
	}
	this->inputArray[pointer][this->subArrayUsedSize[pointer]] = value;
	this->subArrayUsedSize[pointer] += 1;
	this->check_size();
	return 0;
}
/**
 * @brief      Appends a current sub main.
 *
 * @param[in]  value  The value
 */
void List2D::append_current(int value)
{
	this->inputArray[this->usedSizeOfMainArray - 1][this->subArrayUsedSize[this->usedSizeOfMainArray - 1]] = value;
	this->subArrayUsedSize[this->usedSizeOfMainArray - 1] += 1;
	this->check_size();
}
/**
 * @brief      { Free Memory }
 */
void List2D::free_memory()
{
	for (int i = 0; i < this->maxSizeOfMainArray; i++) 
    {
        delete this->inputArray[i];
    }
    delete this->inputArray;
    delete this->subArrayUsedSize;
}
/**
 * @brief      { Check size of memory and than resize it }
 */
void List2D::check_size()
{
	int resizeArray = 0;
	for (int i = 0; i < this->usedSizeOfMainArray; i++)
	{
		if(this->subArrayUsedSize[i] >= this->maxSizeOfSubArray)
		{
			resizeArray = 1;
			break;
		}
	}
	if(this->usedSizeOfMainArray >= this->maxSizeOfMainArray)
	{
		resizeArray = 1;
	}

	if(resizeArray == 1)
	{
		
		//get into temp memory
	   
		int *subArrayUsedSizeTemp = new int [this->maxSizeOfSubArray];  
		int **inputArrayTemp = new int *[this->maxSizeOfMainArray];  
		int maxSizeOfMainArrayTemp = this->maxSizeOfMainArray;
		int maxSizeOfSubArrayTemp  = this->maxSizeOfSubArray;

		for (int i = 0; i < this->maxSizeOfMainArray; i++) 
	    {
	        inputArrayTemp[i] = new int[this->maxSizeOfSubArray];
	    }
	    //storing
		for (int i = 0; i < maxSizeOfMainArrayTemp; i++)
		{
			for (int z = 0; z < maxSizeOfSubArrayTemp; z++)
			{
				inputArrayTemp[i][z] = this->inputArray[i][z];
			}
		}
		for (int i = 0; i < this->maxSizeOfSubArray; i++)
		{
			subArrayUsedSizeTemp[i] = this->subArrayUsedSize[i];
		}

		//free main memory
		free_memory();

		//resize memory
		this->maxSizeOfMainArray = this->maxSizeOfMainArray * 2;
		this->maxSizeOfSubArray  = this->maxSizeOfSubArray * 2;
		this->subArrayUsedSize = new int [this->maxSizeOfMainArray];  
		this->inputArray 	= new int *[this->maxSizeOfMainArray];  

		for (int i = 0; i < this->maxSizeOfMainArray; i++) 
	    {
	        this->inputArray[i] = new int[this->maxSizeOfSubArray];
	    }
	    //seting to zero
	    
	    this->init_zero();
	    //storing back into position 
	    for (int i = 0; i < maxSizeOfMainArrayTemp; i++)
		{
			for (int z = 0; z < maxSizeOfSubArrayTemp; z++)
			{
				this->inputArray[i][z] = inputArrayTemp[i][z];
			}
		}
		for (int i = 0; i < this->maxSizeOfSubArray; i++)
		{
			if(i < this->usedSizeOfMainArray)
			{
				this->subArrayUsedSize[i] = subArrayUsedSizeTemp[i];
			}
			else
			{
				this->subArrayUsedSize[i] = 0;
			}
		}

		//free temp memory
		for (int i = 0; i < maxSizeOfMainArrayTemp; i++) 
	    {
	        delete inputArrayTemp[i];
	    }
	    delete inputArrayTemp;
	    delete subArrayUsedSizeTemp;
	}
}

int List2D::len()
{
	return this->usedSizeOfMainArray;
}

int List2D::len(int pointer)
{
	if(pointer < this->maxSizeOfMainArray)
	{
		return this->subArrayUsedSize[pointer];	
	}
	return -1;
}