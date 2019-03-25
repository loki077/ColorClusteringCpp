#include <iostream>

#include <string>
#include <list>
#include <iterator> 

using namespace std;

int search_list_int(list <int> toScan, int value) 
{ 
    list <int> :: iterator it; 
    for(it = toScan.begin(); it != toScan.end(); it++) 
    {
        if(*it == value)
        {
            return 0;
        }
    }
    return -1;
} 
  
list< list< int > > myListOfLists; 
int main() 
{   
    list<int> tempList;
    tempList.push_back(1);
    tempList.push_back(2);
    tempList.push_back(3);
    myListOfLists.push_back(tempList);
    myListOfLists.push_back(tempList);

    list <int> :: iterator it; 
    list <int> :: iterator it1; 
    for(it = myListOfLists.begin(); it != myListOfLists.end(); it++) 
    {
        for (it1 = *it.begin(); it1 != *it.end(); it1++)
        {
           cout << '\t' << *it1;
        }   
        
    }
} 
