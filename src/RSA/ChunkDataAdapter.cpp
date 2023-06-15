#include "RSA/ChunkDataAdapter.hh"


std::string ChunkDataToString(const std::vector<unsigned int>& chunkData){
    std::string toReturn = "";
    for(const unsigned int& byte: chunkData){
        toReturn.append(std::to_string(byte));
    }

    return toReturn;
}

std::vector<unsigned int> StringToChunkData(const std::string& chunkData){
    std::vector<unsigned int> toReturn = {};

    for(const char& byte: chunkData){
        toReturn.push_back(int(byte));
    }

    return toReturn;
}