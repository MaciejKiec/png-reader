#include "EncryptionDecryption/CBC.hh"

void CBC::encryptDecompressed(std::vector<Chunk*>& data, const std::string& publicKeyPath){
    std::vector<unsigned int> encrypyedBytes = loadBytesFromFile("buffer/IDATBytesEncryptedCBCDecompressed");
    for(int i = 0; i < data.size(); i++){
        if(data[i]->type != IDATHeader) continue;
        data[i]->data = encrypyedBytes;
        data[i]->dataLength = encrypyedBytes.size();       
    }
}

void CBC::decryptDecompressed(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath){
    std::vector<unsigned int> decrypyedBytes = loadBytesFromFile("buffer/IDATBytesDecryptedCBCDecompressed");
    for(int i = 0; i < encryptedData.size(); i++){
        if(encryptedData[i]->type != IDATHeader) continue;
        encryptedData[i]->data = decrypyedBytes;
        encryptedData[i]->dataLength = decrypyedBytes.size();       
    }
}

void CBC::encryptCompressed(std::vector<Chunk*>& data, const std::string& publicKeyPath){
    std::vector<unsigned int> encrypyedBytes = loadBytesFromFile("buffer/IDATBytesEncryptedCBCCompressed");
    for(int i = 0; i < data.size(); i++){
        if(data[i]->type != IDATHeader) continue;
        data[i]->data = encrypyedBytes;
        data[i]->dataLength = encrypyedBytes.size();       
    }
}

void CBC::decryptCompressed(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath){
    std::vector<unsigned int> decrypyedBytes = loadBytesFromFile("buffer/IDATBytesDecryptedCBCCompressed");
    for(int i = 0; i < encryptedData.size(); i++){
        if(encryptedData[i]->type != IDATHeader) continue;
        encryptedData[i]->data = decrypyedBytes;
        encryptedData[i]->dataLength = decrypyedBytes.size();       
    }
}

