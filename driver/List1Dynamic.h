/********************************************************************************************
Project Name    : List1Dynamic.h     --- 1 Dimensional dynamical Array
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 23-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept
********************************************************************************************/

/**************************************Library**********************************************/
#ifndef LIST1DYNAMIC_H_
#define LIST1DYNAMIC_H_

/***************************Library Import***************************/
#include <iostream>
#include <stdio.h> 
#include <stdlib.h>

/***************************Variable Initialization***************************/
using namespace std;

/***************************Main***************************/

/**
 * @brief      List1D is a Class to handle 2 dimensional Dynamic array
 */
class List1D
{
	private:
		int *inputArray;
		int usedSizeOfMainArray = 0;
		int maxSizeOfMainArray 	= 1;
		void check_size();
		void init_zero();
		
	public:
		void init(int mainArraySize);
		int append(int value);
		void print();
		void free_memory();
		int find_in_list(int value);
		int get_value(int pointer);
		int set_value(int pointer, int value);
		int len();
};

#endif

