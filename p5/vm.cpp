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
            //for (int i = 0; i < 4; i++)
                //cout << useBit[i] << " "; 
            //cout<<endl;
            useBit[j] = 0;
            j++;
            if (j > 3)
                j = 0;
        }
       /* for (int i = 0; i < 4; i++)
            cout << useBit[i] << " ";
        cout << endl; */
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
    int rounds = 0;
    bool flip = false;
    bool noMore = false;
    int both = 0;
    for (int i = 0; i < 4; i++)
        pages[i] = 0;
    unsigned int address;
    unsigned int zero = 0;
    char addressString[] = "";
    stringstream str[1000];
    int a = 0;
    int j = 0;
    char c = 0;
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
            //cout<< a << " address" << " "<< hex << (address >> 12) << endl;
        }
    } 
    for (int i = 2; i < 6; i++)
            {
               pages[i] = 0;
               //cout << hex << pages[i] << " ";
            }
            //cout << j << endl;
    a = 0;
    bool reached = false;
    bool first_round = false;
    while (i2fs >> addressString)
    {
        for (int i = 2; i < 6; i++)
            {
               //cout << hex << pages[i] << " ";
            }
            //cout << j << " " << a << endl;
        address = strtoul(addressString, 0, 16);
        if (a > 31)
        {
            for (int i = 2; i < 6; i++)
            {
               //cout << hex << pages[i] << " ";
            }
            //cout << j << endl;
            //cout << hex << address <<endl;
            /*if (j > 3)
            {
               if (reached == true || first_round == false)
               {
                j = 0;
                reached = false;
                first_round = true;
               }  
               else
               {
                j = 3;
                reached = true;
               }
            }*/
            bool inRAM = false;
            for (int i = 2; i < 6; i++)
            {
                //cout << "hihihiii" <<endl;
                //cout << "address " << hex << (address) << " pages[i] " << (pages[i]) << endl;
               if ((address >> 12) == (pages[i] >> 12))
                {
                   inRAM = true;
                   //if ((i - 1) == clock.getLeftOff())
                   //{
                    //cout << "i" << i -2  << endl;
                    clock.setBit(i - 2);
                   //}
                   //cout << "really? " << pages[i] << " " << address << endl;
                }
            }
            if (inRAM == false)
            {
                //cout << "meep"<< endl;
                for (int i = 0; i < 32; i++)
                {
                    //cout << hex << (address >> 12) << " " << (pageTable[i] >> 12) << endl; 
                    if ((address >> 12) == (pageTable[i] >> 12))
                    {    
                        //cout << "hello" <<endl;
                        //cout << "b " << clock.getLeftOff()<<endl;
                        j = clock.getUseBit(clock.getLeftOff());
                        //cout << "bit " << j << " " << endl;
                        clock.setLeftOff(j);
                        rounds++;
                       /* if (rounds > 8 && noMore == false)
                        {
                            noMore = true;
                            flip = true;
                        }
                        if (flip == true && j > 1)
                        {
                           if (clock.getLeftOff() - 1 == 3)
                            pages[4] = pageTable[i];
                           else if (clock.getLeftOff() - 1 == 2)
                            pages[5] = pageTable[i];
                           both++;
                           if (both >= 2)
                           {
                            both = 0;
                            flip = false;
                           }
                        }
                        //cout << "a " << clock.getLeftOff()<<endl;
                        else */
                          pages[j + 2] = pageTable[i];
                        
                        //cout << hex << RAM[j - 1] << " H I " << endl;
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
                //cout << " " << j << endl;
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