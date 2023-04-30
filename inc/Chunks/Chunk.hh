#ifndef CHUNK_HH
#define CHUNK_HH
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <string>
#include <utility>
class Chunk{
 public:
    uint32_t dataLength;
    uint32_t type;
    std::vector<unsigned int> data;
    uint32_t crc32;

    Chunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32);
    virtual void whatChunkAmI();
};

#endif