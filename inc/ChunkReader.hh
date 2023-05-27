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
    private:
        std::vector<unsigned int> bytesToRead;
        uint32_t dataLength = 0;
        uint32_t type = 0;
        std::vector<unsigned int> data = {};
        uint32_t crc32 = 0;
    
        bool zeroLengthDetected = false;
        int pointer = 8;

        void readDataLength();
        void readChunkType();
        void readChunkData();
        void readCRC32();
        void checkHeader();
        void clearVariables();
    public:
        ChunkReader(const std::vector<unsigned int>& bytesToRead);
        const std::vector<Chunk*> readSomeChunks();
};
#endif