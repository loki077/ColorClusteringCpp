
/********************************************************************************************
Project Name    : List2Dynamic.h     --- 2 Dimensional dynamical Array
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 23-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept
********************************************************************************************/

/**************************************Library**********************************************/
#ifndef LIST2DYNAMIC_H_
#define LIST2DYNAMIC_H_

/***************************Library Import***************************/
#include <iostream>
#include <stdio.h> 
#include <stdlib.h>

/***************************Variable Initialization***************************/
using namespace std;

/***************************Main***************************/

/**
 * @brief      Listoflist is a Class to handle 2 dimensional Dynamic array
 */
class ListOfList
{
	private:
		int **inputArray;

		int usedSizeOfMainArray = 0;
		int *subArrayUsedSize;

		int maxSizeOfMainArray 	= 1;
		int maxSizeOfSubArray 	= 1;
		void check_size();
		
	public:
		void init(int mainArraySize, int subArraySize);
		void append_main(int value);
		void append_current_sub_main(int value);
		void print();
		void free_memory();
		int find_in_list(int pointer, int value);
		int append_sub_main(int pointer, int value);
		int get_value(int pointer, int pointer1);
		int set_value(int pointer, int pointer1, int value);
};

#endif

