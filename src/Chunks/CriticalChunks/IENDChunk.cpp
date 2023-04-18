#include "Chunks/CriticalChunks/IENDChunk.hh"

IENDChunk::IENDChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
    Chunk(_dataLength, _type, _data, _crc32) {};

void IENDChunk::whatChunkAmI(){
    std::cout << "I'm IEND chunk!\n\n";
}