#include "Chunks/CriticalChunks/IDATChunk.hh"
#include "RSA/ChunkDataAdapter.hh"
#include <iostream>

IDATChunk::IDATChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
    Chunk(_dataLength, _type, _data, _crc32) {
        std::cout << ChunkDataToString(_data);
    };

void IDATChunk::whatChunkAmI(){
    std::cout << "I'm IDAT chunk!\n";
    std::cout << "Data length: " << dataLength << " bytes\n\n";
}