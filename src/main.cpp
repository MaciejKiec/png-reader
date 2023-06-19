#include "ChunkReader.hh"
#include "ChunkWriter.hh"
#include "EncryptionDecryption/keysGenerator.hh"
#include "EncryptionDecryption/RSA/fileEncryptorDecryptor.hh"
#include <memory>
#include "EncryptionDecryption/EncryptionDecryptionManager.hh"

int main(){

    //generateRSAKeyPair("keys/public.txt", "keys/private.txt", 16384);
    std::vector<unsigned int> fileByes = loadBytesFromFile("images/lena.png");
    ChunkReader chunkReader(fileByes);
    std::vector<Chunk*> chunks = chunkReader.readSomeChunks();
    std::shared_ptr<RsaAlgorithm> alg = std::make_shared<RsaAlgorithm>();
    PngEncryptionDecryption test = PngEncryptionDecryption(alg, chunks, "keys/public.txt", "keys/private.txt");
    test.reduceIDATChunksSize();
    chunks = test.getChunks();
    ChunkWriter chunkWriter(chunks, "test");
    chunkWriter.writeCriticalChunksToFile();

    return 0;
}