//
//  
#include <iostream>
#include "cachesimulator.h"
using namespace std;

int main()
{
    Cache cacheSim;
    
    while(!cin.eof() && cin.good())
    {
        cout << "\nwhat would you like to do? (r)ead, (w)rite, (d)isplay cache? ";
        char answer;
        cin >> answer;
        
        if(cin.eof())
        {
            cout << "Good Bye. \n" << endl;
        }
        else
        {
            if(answer == 'r')
            {
                cacheSim.readcache();
            }
            else if(answer == 'w')
            {
                cacheSim.writecache();
            }
            else
            {
                cacheSim.displaycache();
            }
        }
    }
    
    return 0;
    
}
