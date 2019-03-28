/********************************************************************************************
Project Name    : 2 Dimensional dynamical Array
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 23-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept
********************************************************************************************/

#include <iostream>
#include <stdio.h> 
#include <stdlib.h>

using namespace std;

class ListOfList
{
	public:
		int **inputArray;

		int usedSizeOfMainArray = 0;
		int *subArrayUsedSize;

		int maxSizeOfMainArray 	= 1;
		int maxSizeOfSubArray 	= 1;

		void init(int mainArraySize, int subArraySize);
		void append_main(int value);
		int append_sub_main(int pointer, int value);
		int append_current_sub_main(int value);
		void print();
		int find_in_list(int pointer, int value);
		void check_size();
		void free_memory();
		int get_value(int pointer, int pointer1);
		int set_value(int pointer, int pointer1, int value);
};

int ListOfList::get_value(int pointer, int pointer1)
{
	if(pointer < usedSizeOfMainArray)
	{
		if(pointer1 < subArrayUsedSize[pointer])
		{
			return inputArray[pointer][pointer1];
		}
	}
	return -1;
}

int ListOfList::set_value(int pointer, int pointer1, int value)
{
	if(pointer < usedSizeOfMainArray)
	{
		if(pointer1 < subArrayUsedSize[pointer])
		{
			inputArray[pointer][pointer1] = value;
			return 0;
		}
	}
	return -1;
}

void ListOfList::init(int mainArraySize, int subArraySize)
{	
	maxSizeOfMainArray 		= mainArraySize;
	maxSizeOfSubArray 		= subArraySize;
	subArrayUsedSize 		= new int [maxSizeOfMainArray];  
	inputArray 	= new int *[maxSizeOfMainArray];  

	for (int i = 0; i < maxSizeOfMainArray; i++) 
    {
        inputArray[i] = new int[maxSizeOfSubArray];
    }
}

int ListOfList::find_in_list(int pointer, int value)
{
	if (pointer < usedSizeOfMainArray)
	{
		for (int i = 0; i < subArrayUsedSize[pointer]; i++)
		{
			if(inputArray[pointer][i] == value)
			{
				return 0;
			}
		}
		return -1;
	}
	return -2;
}

void ListOfList::print()
{
	cout << '[';
	for (int i = 0; i < usedSizeOfMainArray; i++)
	{
		cout << subArrayUsedSize[i] << ": ";
		for (int z = 0; z < subArrayUsedSize[i]; z++)
		{
			cout << inputArray[i][z] << " ";
		}
		cout << endl;
	}
	cout << ']' << usedSizeOfMainArray;
}

void ListOfList::append_main(int value)
{
	inputArray[usedSizeOfMainArray][subArrayUsedSize[usedSizeOfMainArray]] = value;
	subArrayUsedSize[usedSizeOfMainArray] += 1;
	usedSizeOfMainArray++;	
	check_size();
}

int ListOfList::append_sub_main(int pointer, int value)
{
	if(pointer > usedSizeOfMainArray)
	{
		return -1;
	}
	inputArray[pointer][subArrayUsedSize[pointer]] = value;
	subArrayUsedSize[pointer] += 1;
	check_size();
}

int ListOfList::append_current_sub_main(int value)
{
	inputArray[usedSizeOfMainArray - 1][subArrayUsedSize[usedSizeOfMainArray - 1]] = value;
	subArrayUsedSize[usedSizeOfMainArray - 1] += 1;
	check_size();
}

void ListOfList::free_memory()
{
	for (int i = 0; i < maxSizeOfMainArray; i++) 
    {
        delete inputArray[i];
    }
    delete inputArray;
    delete subArrayUsedSize;
}

void ListOfList::check_size()
{
	int resizeArray = 0;
	for (int i = 0; i < usedSizeOfMainArray; i++)
	{
		if(subArrayUsedSize[i] >= maxSizeOfSubArray)
		{
			resizeArray = 1;
			break;
		}
	}
	if(usedSizeOfMainArray >= maxSizeOfMainArray)
	{
		resizeArray = 1;
	}

	if(resizeArray == 1)
	{
		cout << "resizing";
		//get into temp memory
		int *subArrayUsedSizeTemp = new int [maxSizeOfSubArray];  
		int **inputArrayTemp = new int *[maxSizeOfMainArray];  
		int maxSizeOfMainArrayTemp = maxSizeOfMainArray;
		int maxSizeOfSubArrayTemp  = maxSizeOfSubArray;

		for (int i = 0; i < maxSizeOfMainArray; i++) 
	    {
	        inputArrayTemp[i] = new int[maxSizeOfSubArray];
	    }
	    //storing
		for (int i = 0; i < maxSizeOfMainArrayTemp; i++)
		{
			for (int z = 0; z < maxSizeOfSubArrayTemp; z++)
			{
				inputArrayTemp[i][z] = inputArray[i][z];
			}
		}
		for (int i = 0; i < maxSizeOfSubArray; i++)
		{
			subArrayUsedSizeTemp[i] = subArrayUsedSize[i];
		}

		//free main memory
		free_memory();

		//resize memory
		maxSizeOfMainArray = maxSizeOfMainArray * 2;
		maxSizeOfSubArray  = maxSizeOfSubArray * 2;
		subArrayUsedSize = new int [maxSizeOfMainArray];  
		inputArray 	= new int *[maxSizeOfMainArray];  

		for (int i = 0; i < maxSizeOfMainArray; i++) 
	    {
	        inputArray[i] = new int[maxSizeOfSubArray];
	    }
	    //storing back into position 
	    for (int i = 0; i < maxSizeOfMainArrayTemp; i++)
		{
			for (int z = 0; z < maxSizeOfSubArrayTemp; z++)
			{
				inputArray[i][z] = inputArrayTemp[i][z];
			}
		}
		for (int i = 0; i < maxSizeOfSubArray; i++)
		{
			subArrayUsedSize[i] = subArrayUsedSizeTemp[i];
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

int main()
{
	ListOfList list1;

	list1.init(2 ,2);
	list1.append_main(1);
	list1.append_main(2);
	list1.print();
	list1.append_main(3);
	list1.append_current_sub_main(31);
	list1.append_current_sub_main(32);
	list1.append_current_sub_main(33);
	list1.append_main(4);
	list1.print();
	list1.set_value(0,0,22);
	list1.append_main(5);
	list1.append_main(6);
	list1.print();
	// list1.append_sub_main(0, 4);
	list1.free_memory();
}