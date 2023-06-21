#include "EncryptionDecryption/ChunkDataAdapter.hh"


void ChunkDataToChars(const std::vector<unsigned int>& chunkData, unsigned char* table){
    for(int i = 0; i < chunkData.size(); i++){
        table[i] = static_cast<unsigned char>(chunkData[i]);
    }
}

std::vector<unsigned int> CharsToChunkData(const unsigned char* chunkData, const int& size){
    std::vector<unsigned int> toReturn(size);
    for(int i = 0; i < size; i++){
        toReturn[i] = static_cast<unsigned int>(chunkData[i]);
    }
    return toReturn;
}