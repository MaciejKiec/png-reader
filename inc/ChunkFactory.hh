#ifndef CHUNK_FACTORY_HH
#define CHUNK_FACTORY_HH
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <string>
#include "Chunks/Chunk.hh"
#include "Chunks/CriticalChunks/IDATChunk.hh"
#include "Chunks/CriticalChunks/IHDRChunk.hh"
#include "Chunks/CriticalChunks/IENDChunk.hh"
#include "Chunks/CriticalChunks/PLTEChunk.hh"
#include "Chunks/AncillaryChunks/tEXtChunk.hh"
#include "Chunks/AncillaryChunks/sBITChunk.hh"
#include "Chunks/AncillaryChunks/pHYsChunk.hh"

class ChunkFactory{
    private:
        IHDRChunk* generateIHDRChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32);
        PLTEChunk* generatePLTEChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32);
        IDATChunk* generateIDATChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32);
        IENDChunk* generateIENDChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32);
        tEXtChunk* generatetEXtChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32);
        sBITChunk* generatesBITChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32);
        pHYsChunk* generatepHYsChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32);
    public:
        Chunk* generateChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32);
};
#endif