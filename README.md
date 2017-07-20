# Cache-Simulator
BU MET CS 472 Project 2

"You are to design and implement a software simulation of a cache memory subsystem. You can
use any language. Note that any real cache is invisible to software. This will be a simulation of
the way that a real cache works. Your "cache" will be a software structure/class that will contain
information similar (but on a smaller and more simplified scale) to what would be in a real cache.
Your "main memory" will be a 2K array. You can make it an array of integers or shorts (16-bits),
but because it is simulating a byte-addressable memory, you won't be putting any value larger
than 0xFF (255 decimal or 11111111 binary) in it.
You will provide for these two areas by defining an array for main memory and a
structure/class/record (or array of these) for the cache. For example,
short Main_mem[2048];
So, in effect, your Main_mem array will be the "pretend" main memory area, your cache
structure/class which you define will be the "pretend" cache, your program will pretend to be the
intelligence of the memory sub-system, and requests that you type in will be the equivalent of a
processor making requests of the memory subsystem.
You will implement a direct-mapped, write-back cache. The block size will be 16 bytes and you'll
have 16 slots. Both of these numbers are smaller than a typical real cache, but make for a more
manageable simulation. You should use a structure/class to manage each slot, where the
structure consists of the appropriate information (e.g., a valid flag, tag, etc.) and you eventually
have an array of these structures. (I'm not dictating that you MUST implement the cache in this
exact way, but something close to this use of structures should make the most sense.)"
