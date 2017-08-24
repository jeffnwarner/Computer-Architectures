#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class DmCache
{
    public:
	   unsigned int tag; 
       int dirty;
	   int data[8];
	   DmCache()
	   {
		  tag = 0;
		  dirty = 0;
	   } //constructor
};//Dmcache class


int main(int argc, char** argv)
{
    int address, operation, data, cacheLineNum;
    unsigned int tag, mainBlockNum;
    int dirty = 0;
    int hit = 0;
    int offset = 0;
    char c = 0;

    DmCache line[32];
    char mainMemory [65535]; 
    ifstream file(argv[1]);
    ofstream ofs;
    ofs.open("dm-out.txt");

    while (file >> hex >> address >> c)
    {
    	cout << "BITCH" << endl;
    } //while file is still being read
    ofs.close();
    file.close();
	return 0;
}//main