#include "EncryptionDecryption/EncryptionDecryptionManager.hh"
#include "headers.hh"


void PngEncryptionDecryption::reduceIDATChunksSize(){
    const int desiredChunkSize = 2048; 
    // TO DO:
    // CHANGE NORMAL POINTERS TO SMART POINTERS TO AVOID MEMORY LEAK
    
    std::vector<Chunk*> IDATChunks;
    std::vector<Chunk*> ResizedIDATChunks;

    for(int i = 0; i < chunks.size(); i++){
        if(chunks[i]->type == IDATHeader){
            IDATChunks.push_back(chunks[i]);
        }
    }

}



void PngEncryptionDecryption::encrypt(){
    interface->encrypt(this->chunks, this->PublicKeyPath);
}

void PngEncryptionDecryption::decrypt(){
    interface->decrypt(this->chunks, this->PrivateKeyPath);
}