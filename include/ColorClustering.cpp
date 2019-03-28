/********************************************************************************************
Project Name    : ColorClustering.cpp    -- getting number of patches of color in image
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 23-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept
********************************************************************************************/

/**************************************Library**********************************************/
#include <ColorClustering.h>

/**************************************Main**********************************************/

/**
 * @brief      Creates a file.pr init for scan
 *
 * @param      tempBuffer  Input buffer for processing 2D array in 1D ;form of [y0:x0------y0:xM---y1:x0-------y1:xM.....] 
 * @param[in]  widthTemp   The width of array
 * @param[in]  heightTemp  The height of array
 */
void ColorClustering::create_file(int tempBuffer [], int widthTemp, int heightTemp) 
{
	widthMatrix = widthTemp;
	heightMatrix = heightTemp;
	//Dynamically creating 2D array
	inputArray = new int *[widthMatrix]; 
	assignArray = new int *[widthMatrix];  
    for (int i = 0; i < widthMatrix; i++) 
    {
        inputArray[i] = new int[heightMatrix];
        assignArray[i] = new int[heightMatrix];
    }

	int tempCounter = 0;
	for (int i = 0; i < widthMatrix; i++)
	{
		for (int z = 0; z < heightMatrix; z++)
		{
			inputArray[i][z] = 1; 
			inputArray[i][z] = tempBuffer[tempCounter]; 
			tempCounter++;
		}
	}
}
/**
 * @brief      Scans for a cluster in the array.
 */
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
/**
 * @brief      {Processing previous location which could have been already processesd}
 *
 * @param[in]  tempX  The x position 
 * @param[in]  tempY  The y position
 */
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
					return 0;	
				}
				else
				{
					assignArray[xIndex][yIndex] = assignArray[tempX][tempY];
					currentAssigned = 1;
					return 0;
				}		
			}
			else if(assignArray[xIndex][yIndex] != assignArray[tempX][tempY])
			{
				if(assignArray[tempX][tempY] == 0)
				{
					assignArray[tempX][tempY] = assignArray[xIndex][yIndex];
					currentAssigned = 1;
					return 0;	
				}
				else
				{
					// insert_match(assignArray[tempX][tempY], assignArray[xIndex][yIndex]);
					currentAssigned = 1;
					return 0;
				}
			}
		}
	}
	return -1;	
}