#include "EncryptionDecryption/EncryptionDecryptionManager.hh"

void PngEncryptionDecryption::CombineIDATChunks(){
    std::vector<Chunk*> IDATChunks;
    ChunkFactory* chunkFactory = new ChunkFactory();
    std::vector<unsigned int> combinedData;
    std::ofstream BufferFile;

    for(int i = 0; i < chunks.size(); i++){
        if(chunks[i]->type == IDATHeader){
            IDATChunks.push_back(chunks[i]);
        }
    }

    for(int i = 0; i < IDATChunks.size(); i++){
        std::copy(IDATChunks[i]->data.begin(), IDATChunks[i]->data.end(), std::back_inserter(combinedData));
    }

    chunks.erase(std::remove_if(chunks.begin(), chunks.end(), [](Chunk* chunk){
        return chunk->type == IDATHeader;
    }), chunks.end());

    Chunk* combinedIDATChunks = chunkFactory->generateChunk(combinedData.size(), IDATHeader, combinedData, 0x00000000);

    chunks.insert(chunks.end()-1, combinedIDATChunks);

    BufferFile.open("buffer/IDATBytes", std::ios::binary | std::ios::out);
    for(int j = 0; j < combinedData.size(); j++){
        uint8_t singleByte = combinedData[j];
        BufferFile.write((char*) &singleByte, sizeof(uint8_t));
    }
    BufferFile.close();
    system("python .\\EncryptionDecryptionPython.py");
}




void PngEncryptionDecryption::encryptDecompressed(){
    interface->encryptDecompressed(this->chunks, this->PublicKeyPath);
}

void PngEncryptionDecryption::decryptDecompressed(){
    interface->decryptDecompressed(this->chunks, this->PrivateKeyPath);
}

void PngEncryptionDecryption::encryptCompressed(){
    interface->encryptCompressed(this->chunks, this->PublicKeyPath);
}

void PngEncryptionDecryption::decryptCompressed(){
    interface->decryptCompressed(this->chunks, this->PrivateKeyPath);
}

std::vector<Chunk*> PngEncryptionDecryption::getChunks(){
    return chunks;
}