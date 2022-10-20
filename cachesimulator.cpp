//
// 
//

#include <stdio.h>
#include <iostream>
#include "cachesimulator.h"
using namespace std;

// initiate cache and main memory
Cache::Cache()
{
    int count = 0;
    
    while(count < mainmemory)
    {
        for(short i = 0; i < 0xFF + 1; i++)
        {
            main_mem[count] = i;
            //cout << "main_mem[" << hex << count << "] =";
            count++;
            //cout << hex << main_mem[i] << "\n";
        }
    }
    
    int countslot = 0;
    
    for (size_t i = 0; i < cachesize; i++)
    {
        cache[i][0] = countslot;
        countslot++;
        
        for(size_t j = 1; j < slot; j++)
        {
            cache[i][j] = 0;
        }
    }
    
    //for (size_t i = 0; i < cachesize; i++)
    //{
      //for(size_t j = 0; j < slot; j++)
      //{
          //cout << cache[i][j] << " ";
      //}
    
        //cout << "\n";
    //}
    
}


// calculate address
void Cache::setaddress(int addressinput)
{
    address = addressinput;
}

// calculate slot
void Cache::calcslot()
{
    slotset = (address & 0x0F0) >> 4;
}

// calculate tag
void Cache::calctag()
{
    tagnumber = address >> 8;
    
}

// set tag in cache
void Cache::settag()
{
    cache[slotset][tagloc] = tagnumber;
}

//set offset
void Cache::calcoffset()
{
    offset = address & 0x00F;
}

// set valid bit to 1
void Cache::setvalidbit()
{
    // value of valid equals 1
    cache[slotset][validbitloc] = 1;
}

// calculate begin of block
void Cache::setbeginblock()
{
    blockbegin = address & 0xFF0;
}

// calculate end of block
void Cache::setendblock()
{
    blockend = blockbegin + 0x00F;
}

// set dirty bit
void Cache::setdirtybit()
{
    // if dirty bit is set to 1, set to 0.
    if(cache[slotset][dirtybitloc] == 1)
    {
        cache[slotset][dirtybitloc] = 0;
    }
    // if dirty bit is set to 0, set to 1
    else
    {
        cache[slotset][dirtybitloc] = 1;
    }
}

// check if cache hit/miss by checking valid bit
void Cache::copydata()
{
    setbeginblock();
    // cout << "the block is set to begin at: " << blockbegin << "\n";
    setendblock();
    
    int count2 = 0;
    
    for(int j = dataloc; j < slot; j++)
    {
        cache[slotset][j] = main_mem[blockbegin + count2];
        count2++;
    }
}

void Cache::printcache()
{
    for(size_t i = 0; i < slot; i++)
    {
        cout << hex << cache[slotset][i] << " ";
    }
}

void Cache::readcache()
{
    cout << "What address in main memory would you like to read? ";
    short addressinput;
    cin >> hex >> addressinput;
    
    while(addressinput > 0x7ff)
    {
        cout << "The address is too big. Please try an address smaller than or equal to 0x7ff: ";
        cin >> hex >> addressinput;
    }
    
    if(addressinput <= 0x7ff)
    {
        setaddress(addressinput);
        calcslot();
        calctag();
        calcoffset();
        
        if(cache[slotset][tagloc] == tagnumber && cache[slotset][validbitloc] == 1)
        {
            cout << "CACHE HIT\n";
            
            printcache();
            
            cout << "\nAt that byte, there is the value " << cache[slotset][dataloc + offset];
        }
        else
        {
            cout << "CACHE MISS \n";
            
            //cout << "Currently in cache: \n";
            
            //printcache();
            
            if(cache[slotset][dirtybitloc] == 1)
            {
                updatemainmem();
                

                setvalidbit();
                settag();
                setdirtybit();
                
                copydata();
                
                cout << "Now in cache: \n";
                printcache();
                
                cout << "\nAt that byte, there is the value " << cache[slotset][dataloc + offset];

            }
            else
            {
                setvalidbit();
                settag();
                
                copydata();
                
                cout << "Now in cache: \n";
                printcache();
                
                cout << "\nAt that byte, there is the value " << cache[slotset][dataloc + offset];
            }
        }
    }
}

void Cache::writecache()
{
    cout << "What address in main memory would you like to write to? ";
    int addressinput;
    cin >> hex >> addressinput;
    
    setaddress(addressinput);
    
    while(addressinput > 0x7ff)
    {
        cout << "The address is too big. Please try an address smaller than or equal to 0x7ff: ";
        cin >> hex >> addressinput;
    }
    
    if(addressinput <= 0x7ff)
    {
        calcslot();
        calctag();
        
        calcoffset();
        
        if(cache[slotset][tagloc] == tagnumber && cache[slotset][validbitloc] == 1)
        {
            cout << "CACHE HIT\n";
            
            cout << "Currently in cache: \n";
            
            printcache();
            
            cout << "\nWhat data would you like to write to that address? ";
            int datainput;
            cin >> hex >> datainput;
            
            cache[slotset][dataloc + offset] = datainput;
            setdirtybit();
            
            cout << "Value " << datainput << " has been written to address " << addressinput << ".\n";
            cout << "Now in cache: \n";
            printcache();
        }
        else
        {
            cout << "CACHE MISS\n";
            if(cache[slotset][dirtybitloc] == 1)
            {
                cout << "Currently in cache: \n";
                
                printcache();
                
                updatemainmem();
                
                calcslot();
                calctag();
                
                calcoffset();
                
                cout << "Now copying in new data...\n";
                
                setvalidbit();
                settag();
                setdirtybit();
                
                copydata();
                
                cout << "What data would you like to write to that address? ";
                int datainput;
                cin >> hex >> datainput;
                
                cache[slotset][dataloc + offset] = datainput;
                setdirtybit();
                
                cout << "Value " << datainput << " has been written to address " << addressinput << ".\n";
                cout << "Now in Cache: \n";
                printcache();
            }
            else
            {
                cout << "Copying in data...\n";
                
                setvalidbit();
                settag();
                
                copydata();
                
                cout << "What data would you like to write to that address? ";
                int datainput;
                cin >> hex >> datainput;
                
                cache[slotset][dataloc + offset] = datainput;
                setdirtybit();
                
                cout << "Value " << datainput << " has been written to address " << addressinput << ".\n";
                cout << "Now in Cache: \n";
                printcache();
            }
        }
    }
}

void Cache::displaycache()
{
    cout << "\nslot valid tag dirtybit data\n";
    
    for(size_t i = 0; i < cachesize; i++)
    {
        for(size_t j = 0; j < slot; j++)
        {
            cout << cache[i][j] << " ";
        }
        
        cout << "\n";
    }
}

void Cache::updatemainmem()
{
    // cout << "Dirty Bit 1 -- Copying cache data to Main Memory...";
    
    calcreverseaddress();
    
    // cout << "blockbegin starts: " << reverseaddress << "\n";
    
    int count3 = 0 ;
    
    for(int i  = dataloc; i < slot; i++)
    {
        main_mem[reverseaddress + count3] = cache[slotset][i];
        //cout << "main_mem[" << reverseaddress + count3 << "] = " << hex << main_mem[reverseaddress+count3] << "\n";
        count3++;
    }
}

void Cache::calcreverseaddress()
{
    
    reverseaddress = (cache[slotset][tagloc] << 8) + (slotset << 4);
}


