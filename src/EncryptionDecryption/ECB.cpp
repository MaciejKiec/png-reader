#include "EncryptionDecryption/ECB.hh"

void ECB::encryptDecompressed(std::vector<Chunk*>& data, const std::string& publicKeyPath){
    std::vector<unsigned int> encrypyedBytes = loadBytesFromFile("buffer/IDATBytesEncryptedECBDecompressed");
    for(int i = 0; i < data.size(); i++){
        if(data[i]->type != IDATHeader) continue;
        data[i]->data = encrypyedBytes;
        data[i]->dataLength = encrypyedBytes.size();       
    }
}

void ECB::decryptDecompressed(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath){
    std::vector<unsigned int> decrypyedBytes = loadBytesFromFile("buffer/IDATBytesDecryptedECBDecompressed");
    for(int i = 0; i < encryptedData.size(); i++){
        if(encryptedData[i]->type != IDATHeader) continue;
        encryptedData[i]->data = decrypyedBytes;
        encryptedData[i]->dataLength = decrypyedBytes.size();       
    }
}

void ECB::encryptCompressed(std::vector<Chunk*>& data, const std::string& publicKeyPath){
    std::vector<unsigned int> encrypyedBytes = loadBytesFromFile("buffer/IDATBytesEncryptedECBCompressed");
    for(int i = 0; i < data.size(); i++){
        if(data[i]->type != IDATHeader) continue;
        data[i]->data = encrypyedBytes;
        data[i]->dataLength = encrypyedBytes.size();       
    }
}

void ECB::decryptCompressed(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath){
    std::vector<unsigned int> decrypyedBytes = loadBytesFromFile("buffer/IDATBytesDecryptedECBCompressed");
    for(int i = 0; i < encryptedData.size(); i++){
        if(encryptedData[i]->type != IDATHeader) continue;
        encryptedData[i]->data = decrypyedBytes;
        encryptedData[i]->dataLength = decrypyedBytes.size();       
    }
}
