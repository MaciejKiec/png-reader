#ifndef CHUNK_DATA_ADAPTER_HH
#define CHUNK_DATA_ADAPTER_HH
#include <string>
#include <vector>

    std::string ChunkDataToString(const std::vector<unsigned int>& chunkData);
    std::vector<unsigned int> StringToChunkData(const std::string& chunkData);

#endif