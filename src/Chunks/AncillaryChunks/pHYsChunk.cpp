#include "Chunks/AncillaryChunks/pHYsChunk.hh"

void pHYsChunk::readChunkSpecifics(){
    horizontalResolution = (this->data[0] << 24 | this->data[1] << 16 | this->data[2] << 8 | this->data[3]);
    verticalResolution = (this->data[4] << 24 | this->data[5] << 16 | this->data[6] << 8 | this->data[7]);
    unitSpecifier = this->data[8];
}

pHYsChunk::pHYsChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
Chunk(_dataLength, _type, _data, _crc32) {
        readChunkSpecifics();
};

void pHYsChunk::whatChunkAmI(){
    std::cout << "Horizontal resolution: " << horizontalResolution << " pixels\n";
    std::cout << "Vertical resolution: " << verticalResolution << " pixels\n";
    if(unitSpecifier){
        std::cout << "Unit is the meter\n";
    }else{
        std::cout << "Unit is unknown\n";
    }
    std::cout << std::endl;
}