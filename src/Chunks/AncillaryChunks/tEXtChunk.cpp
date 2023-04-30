#include "Chunks/AncillaryChunks/tEXtChunk.hh"

void tEXtChunk::readChunkSpecifics(){
    char singleSign;
    int pointer = 0;
    while(this->data[pointer] != 0x00){
        singleSign = (char) this->data[pointer];
        this->keyword.append(1,singleSign);;
        pointer++;
    }

    pointer++;

    while(pointer < this->data.size()){
        singleSign = (char) this->data[pointer];        
        this->text.append(1,singleSign);
        pointer++;
    }
}


tEXtChunk::tEXtChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
Chunk(_dataLength, _type, _data, _crc32) {
    readChunkSpecifics();
};

void tEXtChunk::whatChunkAmI(){
    std::cout << "I'm tEXT chunk! My specifics:\n";
    std::cout << "Keyword: " << keyword << std::endl;
    std::cout << "Text: " << text << std::endl;
    std::cout << std::endl;
}