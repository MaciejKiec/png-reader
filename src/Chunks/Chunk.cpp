#include "Chunks/Chunk.hh"

Chunk::Chunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
dataLength(_dataLength), type(_type), data(_data), crc32(_crc32) {};

void Chunk::whatChunkAmI(){
    uint8_t DataRead[4];
    DataRead[0] = (type & 0xFF000000) >> 24;
    DataRead[1] = (type & 0x00FF0000) >> 16;
    DataRead[2] = (type & 0x0000FF00) >> 8;
    DataRead[3] = (type & 0x000000FF);

    std::ios_base::fmtflags f(std::cout.flags()); // zapisujemy flagi strumienia, żeby tylko te informacje były wyświetlane w formie hex
    std::cout << "Im not implemented chunk, but my type is: 0x" << std::uppercase << std::hex << type << " | ";
    std::cout.flags(f); // przywracamy oryginale flagi sturmienia
    std::cout << DataRead[0] << DataRead[1] << DataRead[2] << DataRead[3] << "\n\n";
}