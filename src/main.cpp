#include "ChunkReader.hh"
#include "ChunkWriter.hh"
#include <memory>
#include "EncryptionDecryption/EncryptionDecryptionManager.hh"
#include "EncryptionDecryption/ECB.hh"
#include <iostream>

int main(){
    std::vector<unsigned int> fileByes = loadBytesFromFile("images/3.png");
    ChunkReader chunkReader(fileByes);
    std::vector<Chunk*> chunks = chunkReader.readSomeChunks();
    std::shared_ptr<ECB> alg = std::make_shared<ECB>();
    PngEncryptionDecryption test = PngEncryptionDecryption(alg, chunks, "keys/public.txt", "keys/private.txt");
    test.CombineIDATChunks();
    chunks = test.getChunks();
    ChunkWriter chunkWriter(chunks, "test");
    chunkWriter.writeCriticalChunksToFile();
    return 0;
}