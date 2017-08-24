#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Clock
{
    public:
       int leftOff;
       int useBit[4];
       Clock()
       {
          leftOff = 0;
          for (int i = 0; i < 4; i++)
          {
            useBit[i] = 0;
          }
       } //constructor
       int getUseBit(int bit)
       {
        int rBit;
        int j = bit;

        if (j > 3)
            j = 0;
        while (useBit[j] == 1)
        {
            useBit[j] = 0;
            j++;
            if (j > 3)
                j = 0;
        }
        rBit = j;
        useBit[j] = 1;
        return rBit;
       }
       int getLeftOff()
       {
        return leftOff;
       }
       void setLeftOff(int bit)
       {
          leftOff = bit + 1;
       }
       void setBit(int bit)
       {
        useBit[bit] = 1;
       }
};

int main(int argc, char** argv)
{
    //initial variables
    Clock clock;
    unsigned int pageTable[32];
    unsigned int pages[6];
    for (int i = 0; i < 4; i++)
        pages[i] = 0;
    unsigned int address;
    char addressString[] = "";
    int a = 0;
    int j = 0;
    ifstream ifs(argv[1]);
    ifstream i2fs(argv[1]);
    ofstream ofs("vm-out.txt");

    while (ifs >> addressString)
    {
        if (a < 32)
        {
            address = strtoul(addressString, 0, 16);
            pageTable[a] = address;
            a++;
        }
    } 
    for (int i = 2; i < 6; i++)
            {
               pages[i] = 0;
            }
    a = 0;
    bool reached = false;
    while (i2fs >> addressString)
    {
        address = strtoul(addressString, 0, 16);
        if (a > 31)
        {
            bool inRAM = false;
            for (int i = 2; i < 6; i++)
            {
               if ((address >> 12) == (pages[i] >> 12))
                {
                   inRAM = true;
                   clock.setBit(i - 2);
                }
            }
            if (inRAM == false)
            {
                for (int i = 0; i < 32; i++)
                {
                    if ((address >> 12) == (pageTable[i] >> 12))
                    {    
                        j = clock.getUseBit(clock.getLeftOff());
                        pages[j + 2] = pageTable[i];
                        break;
                    }
                }
            }
            for (int i = 2; i < 5; i++)
            {
               if (pages[i] > 0) 
               {
                  //cout << hex << pages[i];
                  ofs << hex << pages[i];
               }
               if (pages[i + 1] > 0)
                {
                  //cout << " ";
                  ofs << " ";
                }
            }
            if (pages[5] > 0)
            {
               //cout << hex << pages[5] << " " << j << reached<< endl;
               ofs << hex << pages[5] << endl;
            }
            else
            {
                ofs << endl;
            }
        }
        else
        {
           a++;
        }
    }
    ifs.close();
    ofs.close();
	return 0;
}//main
