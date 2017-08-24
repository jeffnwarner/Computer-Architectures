#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class DmCache
{
    public:
	   int tag, dirty;
	   int data[8];
	   DmCache()
	   {
		  tag = -1;
		  dirty = 0;
	   } //constructor
};//Dmcache class


int main(int argc, char** argv)
{
    int address, operation, tag, data, cacheLineNum, mainBlockNum;
    int lineSize = 8;
    int cacheSize = 32;
    int dirty = 0;
    int hit = 0;
    int offset = 0;

    DmCache line[cacheSize];
    char mainMemory [65535]; 
    ifstream file(argv[1]);
    ofstream ofs;
    ofs.open("sa-out.txt");

    while (file >> hex >> address >> operation >> data)
    {
    	mainBlockNum = address / lineSize;//gets rid of offset in address
    	cacheLineNum = mainBlockNum % cacheSize;//i = j mod m
    	tag = mainBlockNum / cacheSize;// gets rid of the last 8 bits (the offset and the index
        offset = address & 7;

        //cout << "DATA "<< hex << data << endl;

        //cout << address << " " << operation << " " << data << endl;
        if(line[cacheLineNum].tag == tag) //checks to see if the read in tag and the s are the same,
            hit = 1;
        else
            hit = 0;

        dirty = line[cacheLineNum].dirty;

        if(hit == 0)
        {
            if(dirty)
            {
                for(int i = 0; i < 8; i++)
                    *(mainMemory + line[cacheLineNum].tag + i) = line[cacheLineNum].data[i];
            } //when dirty we need to copy the data to main memory

            line[cacheLineNum].dirty = 0;
            for(int i = 0; i < 8; i++)
                line[cacheLineNum].data[i] = *(mainMemory + tag + i);
            line[cacheLineNum].tag = tag;
        } //if there is a cache miss, then we need to copy the data to main memory

        //operations ff,00
          if (operation)
          {
                //cout<< "DATA CHECK " << line[cacheLineNum].data[offset] << " OFFSET " << offset<< endl; 
                line[cacheLineNum].data[offset] = data;
                //cout<< "DATA ? " << hex << line[cacheLineNum].data[offset] <<endl; 
                line[cacheLineNum].dirty = 1;
          }//if operation is write
          else 
          {
                ofs << setw(2) << hex << uppercase << setfill('0') << ((int)line[cacheLineNum].data[offset] & 0xFF) << " " << hit << " " << dirty << endl;
          }//if operation is read
         // for (int i = 0; i < 8; i++)
           // cout << hex << line[cacheLineNum].data[i];
    } //while file is still being read
    ofs.close();
    file.close();
	return 0;
}//main