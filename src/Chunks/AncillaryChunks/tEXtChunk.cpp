#include "Chunks/AncillaryChunks/tEXtChunk.hh"

tEXtChunk::tEXtChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
Chunk(_dataLength, _type, _data, _crc32) {};

void tEXtChunk::whatChunkAmI(){
    std::cout << "I'm tEXt Chunk! I'm being implemented right now!\n\n";
}