#ifndef CHUNK_READER_HH
#define CHUNK_READER_HH
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <string>
#include "ChunkFactory.hh"
#include "OnBytesOperations.hh"
class ChunkReader{
    public:
    const std::vector<Chunk*> readSomeChunks(const std::vector<unsigned int> bytesToRead);
};
#endif