# chashmap

simple open addressing hashmap, and linked hashmap in C11.

a hashmap and linked hashmap implementation with variable fixed-width
key and value that are set at initialization time. this allows a single
implementation to be configured as a hashset and linked hashset by using
zero length values. the API however still takes a value parameter just the
length can be zero. the design adopts an open-addressing hashtable with
tombstone bitmaps to eliminate the need for empty or deleted key sentinels.

the implementation does not support any advanced features like custom
deleters or multithreading. it is designed to be a simple and fast hash
table with minimal dependencies and that will compile in standard C11.

the implementation is derived from [ethical_hashmap](https://github.com/michaeljclark/ethical_hashmap)
which is a fast C++ hashmap, hashset, linked hashmap and linked hash set
implementation that supports C++ copy and move constructors, placement new
and explicit destructor calls for flexible templated key and value classes.

## build

- requires CMake.

```
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config RelWithDebInfo
build\RelWithDebInfo\test_hmap.exe
```
