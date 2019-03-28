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

		list <int> resultStringList, resultColorList;
		list <int> outputColorList;

		void create_file(int buffer [], int widthTemp, int heightTemp);
		void scan_cluster();
		void print_output();
		void generate_output_array();
		void color_image_output();
		void processed_location(int tempX, int tempY);
		void other_location(int tempX, int tempY);
		void insert_match(int value1, int value2);
		void insert_new_match(int value1);
};

void ColorClustering::create_file(int buffer [], int widthTemp, int heightTemp) 
{
	widthMatrix = widthTemp
	heightMatrix = heightTemp
	int tempCounter = 0;
	for (int i = 0; i < heightMatrix; ++i)
	{
		for (int z = 0; z < widthMatrix; ++z)
		{
			inputArray[i][z] = buffer[tempCounter]; 
			tempCounter++;
		}
	}
	inputArray = np.zeros(shape=(widthTemp, heightTemp))
	assignArray = np.zeros(shape=(widthTemp, heightTemp))
	inputArray = inputMatrix
}



int insert_match(int value1, int value2)
{
		int valueStored = 0;
		for (int x = 0; x < len(resultStringList); x++)
		{		
			if (value1 in resultStringList[x])
			{
				if (value2 in resultStringList[x])
				{
					valueStored = 1;
				}
				else
				{
					resultStringList[x].append(value2);
					resultColorList[x].append(currentValue);					
					valueStored = 1;
				}
			}
			else if (value2 in resultStringList[x])
			{
				if (value1 in resultStringList[x])
				{
					valueStored = 1;
				}
				else
				{
					resultStringList[x].append(value1);
					resultColorList[x].append(currentValue);					
					valueStored = 1;
				}
			}
		}
		if (valueStored == 0)
		{
			resultStringList.append([value1, value2]);
			resultColorList.append([currentValue]);
		}					
}
	def insert_new_match( value1):
		valueStored = 0

		for x in xrange(0, len(resultStringList)):
			if value1 in resultStringList[x]:
				valueStored = 1

		if valueStored == 0:
			resultStringList.append([value1])
			resultColorList.append([currentValue])					

void scan_cluster()
{
	for (int xIndex = 0; i < widthMatrix; i++)
	{
		for (int yIndex = 0; i < heightMatrix; i++)
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