#include "EncryptionDecryption/EncryptionDecryptionManager.hh"

void PngEncryptionDecryption::reduceIDATChunksSize(){
    const int desiredChunkSize = 2048; 
    // TO DO:
    // CHANGE NORMAL POINTERS TO SMART POINTERS TO AVOID MEMORY LEAK

    std::vector<Chunk*> IDATChunks;
    std::vector<Chunk*> ResizedIDATChunks;
    int pointer = 0;
    int chunksToGenerate = 0;
    ChunkFactory* chunkFactory = new ChunkFactory();
    std::vector<unsigned int> temp;

    for(int i = 0; i < chunks.size(); i++){
        if(chunks[i]->type == IDATHeader){
            IDATChunks.push_back(chunks[i]);
        }
    }

    for(int i = 0; i < IDATChunks.size(); i++){
        chunksToGenerate = int(IDATChunks[i]->data.size() / 2048);
        if(IDATChunks[i]->data.size() % 2048 != 0) chunksToGenerate++;
        for(int j = 0; j < chunksToGenerate; j++){
            if(j != chunksToGenerate - 1){
                std::copy(IDATChunks[i]->data.begin() + j * desiredChunkSize, IDATChunks[i]->data.begin() + (j+1) * desiredChunkSize, std::back_inserter(temp));
                ResizedIDATChunks.push_back(chunkFactory->generateChunk(desiredChunkSize, IDATHeader, temp, chunksToGenerate));
            }else{
                std::copy(IDATChunks[i]->data.begin() + j * desiredChunkSize, IDATChunks[i]->data.end(), std::back_inserter(temp));
                ResizedIDATChunks.push_back(chunkFactory->generateChunk(IDATChunks[i]->data.size() - j*desiredChunkSize, IDATHeader, temp, chunksToGenerate));
            }
            temp.clear();
        }
    }
    
    chunks.erase(std::remove_if(chunks.begin(), chunks.end(), [](Chunk* chunk){
        return chunk->type == IDATHeader;
    }),chunks.end());

    chunks.insert(chunks.end() - 1, ResizedIDATChunks.begin(), ResizedIDATChunks.end());

}



void PngEncryptionDecryption::encrypt(){
    interface->encrypt(this->chunks[3]->data, this->PublicKeyPath);
}

void PngEncryptionDecryption::decrypt(){
    interface->decrypt(this->chunks, this->PrivateKeyPath);
}

std::vector<Chunk*> PngEncryptionDecryption::getChunks(){
    return chunks;
}