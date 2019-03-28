/********************************************************************************************
Project Name    : ColorCLustering.h     --- getting number of patches of color in image
Developer       : Lokesh Ramina
Platform        : c++ compiler g++ on Ubuntu 16.04
Date            : 23-03-2019
Purpose         : Task
Note			: Please go through the readme.txt file to understand the code and concept
********************************************************************************************/

/**************************************Library**********************************************/
#ifndef COLORCLUSTERING_H_
#define COLORCLUSTERING_H_

/***************************Library Import***************************/

/**************************Main*******************************/
/**
 * @brief      Class for color clustering is used to get number of color spots in an 2 dimensional array in Gray scale.
 */
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

		List2D resultList; 
		List2D resultColorList;
		List1D outputColorList;

		void create_file(int tempBuffer [], int heightTemp, int widthTemp);
		void scan_cluster();
		void print_input();
		void print_output();
		void generate_output_array();
		void color_image_output();
		void processed_location(int tempX, int tempY);
		int other_location(int tempX, int tempY);
		void insert_match(int value1, int value2);
		void insert_new_match(int value1);
		void free_memory();
};

#endif