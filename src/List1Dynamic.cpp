/********************************************************************************************
Project Name    : List1Dynamic.cpp     ---1 Dimensional dynamical Array
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 26-03-2019
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
#include "List1Dynamic.h"
	

/**
 * @brief      { Initiallizing the List }
 *
 * @param[in]  mainArraySize  The main array size
 * @param[in]  subArraySize  The sub array size
 */
void List1D::init(int mainArraySize)
{	
	this->maxSizeOfMainArray 	= mainArraySize;
	this->inputArray	= new int [this->maxSizeOfMainArray];  
	this->init_zero();
}

void List1D::init_zero()
{
	for (int i = 0; i < this->maxSizeOfMainArray; i++)
	{
		this->inputArray[i] = 0;
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
int List1D::find_in_list(int value)
{
	for (int i = 0; i < this->usedSizeOfMainArray; i++)
	{
		if(this->inputArray[i] == value)
		{
			return 0;
		}
	}
	return -1;
}

/**
 * @brief      { To Print List}
 */
void List1D::print()
{
	// cout << '['<< endl;
	for (int i = 0; i < this->usedSizeOfMainArray; i++)
	{		
		cout << this->inputArray[i] << endl;
	}
	// cout << ']' << endl;
}

/**
 * @brief      Appends into 1stD of array.
 *
 * @param[in]  value   The value to append in list
 */
int List1D::append(int value)
{
	this->inputArray[this->usedSizeOfMainArray] = value;
	this->usedSizeOfMainArray++;	
	this->check_size();
	return 0;
}

/**
 * @brief      { Free Memory }
 */
void List1D::free_memory()
{	
    delete this->inputArray;
}

/**
 * @brief      { Check size of memory and than resize it }
 */
void List1D::check_size()
{
	int resizeArray = 0;

	if(this->usedSizeOfMainArray >= this->maxSizeOfMainArray)
	{
		resizeArray = 1;
	}

	if(resizeArray == 1)
	{
		
		//get into temp memory
		int *inputArrayTemp = new int [this->maxSizeOfMainArray];  
		int maxSizeOfMainArrayTemp = this->maxSizeOfMainArray;

	    //storing
		for (int i = 0; i < maxSizeOfMainArrayTemp; i++)
		{
			inputArrayTemp[i]= this->inputArray[i];
		}

		//free main memory
		free_memory();

		//resize memory
		this->maxSizeOfMainArray = this->maxSizeOfMainArray * 2;  
		this->inputArray 	= new int [this->maxSizeOfMainArray];  
	    //storing back into position 
	    for (int i = 0; i < maxSizeOfMainArrayTemp; i++)
		{
			this->inputArray[i] = inputArrayTemp[i];
		}

		//free temp memory
		delete inputArrayTemp;
	}
}

/**
 * @brief      Gets the value.
 *
 * @param[in]  pointer   1D pointer
 *
 * @return     The value you want -1 wrong memory access
 */
int List1D::get_value(int pointer)
{
	if(pointer < this->usedSizeOfMainArray)
	{
		return this->inputArray[pointer];
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
int List1D::set_value(int pointer, int value)
{
	if(pointer < this->usedSizeOfMainArray)
	{
		this->inputArray[pointer] = value;
		return 0;
	}
	return -1;
}

int List1D::len()
{
	return this->usedSizeOfMainArray;
}
