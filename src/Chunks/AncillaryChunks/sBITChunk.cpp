#include "Chunks/AncillaryChunks/sBITChunk.hh"

void sBITChunk::readChunkSpecifics(){
    redBits = this->data[0];
    greenBits = this->data[1];
    blueBits = this->data[2];
    alphaBits = this->data[3];
}

sBITChunk::sBITChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
Chunk(_dataLength, _type, _data, _crc32) {
    readChunkSpecifics();
};

void sBITChunk::whatChunkAmI(){
    std::cout << "I'm sBIT chunk! My specifics:\n";
    std::cout << "Red bits: " << redBits << "\n";
    std::cout << "Green bits: " << greenBits << "\n";
    std::cout << "Blue bits: " << blueBits << "\n";
    std::cout << "Alpha bits: " << alphaBits << "\n";
    std::cout << std::endl;
}