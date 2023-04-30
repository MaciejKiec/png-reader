#include "Chunks/AncillaryChunks/sBITChunk.hh"

sBITChunk::sBITChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
Chunk(_dataLength, _type, _data, _crc32) {};

void sBITChunk::whatChunkAmI(){
    std::cout << "I'm sBIT Chunk! I'm being implemented right now!\n\n";
}