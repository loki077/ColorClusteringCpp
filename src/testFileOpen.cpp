#include <iostream>
#include <fstream>

using namespace std;

int file_load(int imageW, int imageH)
{
    char buffer[imageW * imageH];

    string fileLocation = "";
    cout << "Count Areas File Name : " << endl;
    cin >> fileLocation;
    fileLocation = "/home/lokesh/Desktop/Projects/ColorGrouping/data/sample.bin";
    ifstream myFile ("/home/lokesh/Desktop/Projects/ColorGrouping/data/sample.bin", ios::binary);
    if (!myFile.read (buffer, imageW * imageH)) 
    {
        cout << "done" << endl;
    }
    for (int i = 0; i < sizeof(buffer); ++i)
    {
        cout << hex << (int)buffer[i];
    }
    return 0;
}

int main()
{
    file_load(256, 256);
    return 0;
}