#include "Chunks/CriticalChunks/PLTEChunk.hh"


void PLTEChunk::readChunkSpecifics(std::vector<unsigned int> data){
    entriesNumber = data.size() / 3;
}

PLTEChunk::PLTEChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32): Chunk(_dataLength, _type, _data, _crc32){
    if(_data.size() % 3 != 0){
        std::cout << "PLTE chunk error! Data length is not divisible by 3!\n";
        std::cout << "Actual PLTE data length: " << _data.size() << "\n";
        exit(0);
    }
    readChunkSpecifics(_data);
};

void PLTEChunk::whatChunkAmI(){
    std::cout << "I'm PLTE chunk!\n";
    std::cout << "Number of entries: " << entriesNumber << "\n\n";
}