#include "Chunks/CriticalChunks/IHDRChunk.hh"

void IHDRChunk::readChunkSpecifics(std::vector<unsigned int> data){
    width = (data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]);
    height = (data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7]);
    bitDepth = data[8];
    colorType = data[9];
    compressionMethod = data[10];
    filterMethod = data[11];
    interlaceMethod = data[12];
}

IHDRChunk::IHDRChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32): Chunk(_dataLength, _type, _data, _crc32){
    readChunkSpecifics(_data);
};

void IHDRChunk::whatChunkAmI(){
    std::cout << "I'm HDR chunk! My specifics:\n";
    std::cout << "Width: " << width << " pixels\n";
    std::cout << "Height: " << height << " pixels\n";
    std::cout << "Bit depth: " << bitDepth << " bits per pixel\n";
    std::cout << "Color type: " << colorType << "\n";
    std::cout << "Filter method: " << filterMethod<< "\n";
    std::cout << "Interlace method: " << interlaceMethod << "\n\n";
}