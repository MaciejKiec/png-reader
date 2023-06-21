#ifndef CHUNK_DATA_ADAPTER_HH
#define CHUNK_DATA_ADAPTER_HH
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

    void ChunkDataToChars(const std::vector<unsigned int>& chunkData, unsigned char* table);
    std::vector<unsigned int> CharsToChunkData(const unsigned char* chunkData, const int& size);

#endif