#include "EncryptionDecryption/EncryptionDecryptionManager.hh"

void PngEncryptionDecryption::CombineIDATChunks(){
    std::vector<Chunk*> IDATChunks;
    ChunkFactory* chunkFactory = new ChunkFactory();
    std::vector<unsigned int> combinedData;

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

}




void PngEncryptionDecryption::encrypt(){
    interface->encrypt(this->chunks, this->PublicKeyPath);
}

void PngEncryptionDecryption::decrypt(){
    interface->decrypt(this->chunks, this->PrivateKeyPath);
}

std::vector<Chunk*> PngEncryptionDecryption::getChunks(){
    return chunks;
}