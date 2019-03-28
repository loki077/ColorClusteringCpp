# ColorClusteringCpp
Description:
	This is a C++ code for Color Clustering Algorithm

This is a Repository maintained and developed by Lokesh Ramina
===================================================================
About: 
 	The code is about color clusturing in 2D image.
 	Taking inputs as .bin file.

Prerequisit:
	g++ should be installed

Instrution to execute file:
	Make sure the prerequisite is completed
	The main code is in ../ColorClusteringPython/main
	file name main.py
	To run the code:
		# cd .../ColorClusteringCPP/src
		# make
		#./output
		>count-areas <file full Location from root> --shape <Height>,<Width> 	//after typing width press enter make sure the spaces and value are correct
			eg:count-areas /home/lokesh/Desktop/Projects/ColorClusteringCpp/data/sample.bin --shape 256,256
	if everything is perfect output will be generated or else code will exit.

-------------------------------------------------------------------
Allgorithm explained:
	The logic is developed by Lokesh Ramina
	Considering the below matrix.
	
	| 120  120  120  003  000|
	| 120  120	120  003  003|	
	| 003  120  120  120  003|
	| 003  003  003  003  003|
	| 003  003  003  003  003|
	
	> create a parallel similar matrix which will have assignment of group value
	> moving from 0,0 to w_,h_ it will check the position is assigned or not if not than will process the positon
	> In process it checks the color value of near 8 locations and if any has same value than both gets assigned into same group and so on.
	> output below of above image assign matrix

	| 1  1  1  2  3|
	| 1  1	1  2  2|	
	| 2  1  1  1  2|
	| 2  2  2  2  2|
	| 2  2  2  2  2|

	
