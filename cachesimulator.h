//
// 
//

#ifndef cachesimulator_h
#define cachesimulator_h

class Cache
{
public:
    static const int slotnumberloc = 0; // slot position in the cache data array
    static const int validbitloc = 1; // validbit position in the cache data array
    static const int tagloc = 2; // tag position in the cache data array
    static const int dirtybitloc = 3; // dirty bit position in the cache data array
    static const int dataloc = 4; // data start position in the cache data array
    static const int cachesize = 16; // how big the data part of the cache is
    static const int slot = 20; // number of slots in the cache array
    static const int mainmemory = 2048; // size of main memory
    
    int cache[cachesize][slot];
    int main_mem[2048];
    
    Cache();
    void setaddress(int addressinput);
    void calctag();
    void settag();
    void calcoffset();
    void setvalidbit();
    void setbeginblock();
    void setendblock();
    void calcslot();
    void copydata();
    void setdirtybit();
    void printcache();
    void readcache();
    void writecache();
    void displaycache();
    void updatemainmem();
    void calcreverseaddress();
    
private:
    int tagnumber;
    int address;
    int offset;
    int blockbegin;
    int blockend;
    int slotset;
    int reverseaddress;
};

#endif /* cachesimulator_h */
