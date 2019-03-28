/********************************************************************************************
Project Name    : List2Dynamic.cpp     --- 2 Dimensional dynamical Array
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 23-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept
********************************************************************************************/

/**************************************Library**********************************************/
#include <List2Dynamic.h>
	
/**
 * @brief      Gets the value.
 *
 * @param[in]  pointer   1D pointer
 * @param[in]  pointer1  2D pointer
 *
 * @return     The value you want -1 wrong memory access
 */
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

/**
 * @brief      Sets the value in List.
 *
 * @param[in]  pointer   1D pointer
 * @param[in]  pointer1  2D pointer
 * @param[in]  value     The value to set in position
 *
 * @return     { 0 = Succesfull , -1 = wrong memory access }
 */
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

/**
 * @brief      { Initiallizing the List }
 *
 * @param[in]  mainArraySize  The main array size
 * @param[in]  subArraySize   The sub array size
 */
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
/**
 * @brief      { To find value in list }
 *
 * @param[in]  pointer  The pointer position 
 * @param[in]  value    The value to search
 *
 * @return     { 0 = Succesfull , -1 = Not present }
 */
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

/**
 * @brief      { To Print List}
 */
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

/**
 * @brief      Appends into 1stD of array.
 *
 * @param[in]  value   The value to append in list
 */
void ListOfList::append_main(int value)
{
	inputArray[usedSizeOfMainArray][subArrayUsedSize[usedSizeOfMainArray]] = value;
	subArrayUsedSize[usedSizeOfMainArray] += 1;
	usedSizeOfMainArray++;	
	check_size();
}

/**
 * @brief      Appends into 2ndD of array with position access.
 *
 * @param[in]  pointer  The pointer of first dimension
 * @param[in]  value    The value
 *
 * @return     { 0 = Succesfull, -1 = wrong position access  }
 */
int ListOfList::append_sub_main(int pointer, int value)
{
	if(pointer > usedSizeOfMainArray)
	{
		return -1;
	}
	inputArray[pointer][subArrayUsedSize[pointer]] = value;
	subArrayUsedSize[pointer] += 1;
	check_size();
	return 0;
}
/**
 * @brief      Appends a current sub main.
 *
 * @param[in]  value  The value
 */
void ListOfList::append_current_sub_main(int value)
{
	inputArray[usedSizeOfMainArray - 1][subArrayUsedSize[usedSizeOfMainArray - 1]] = value;
	subArrayUsedSize[usedSizeOfMainArray - 1] += 1;
	check_size();
}
/**
 * @brief      { Free Memory }
 */
void ListOfList::free_memory()
{
	for (int i = 0; i < maxSizeOfMainArray; i++) 
    {
        delete inputArray[i];
    }
    delete inputArray;
    delete subArrayUsedSize;
}
/**
 * @brief      { Check size of memory and than resize it }
 */
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