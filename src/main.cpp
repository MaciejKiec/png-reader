#include "ChunkReader.hh"
#include "ChunkWriter.hh"
#include "EncryptionDecryption/keysGenerator.hh"
#include "EncryptionDecryption/RSA/fileEncryptorDecryptor.hh"
typedef std::vector<unsigned int> PngFile;
typedef const std::vector<Chunk*> Chunks;

int main(){

    //generateRSAKeyPair("keys/public.txt", "keys/private.txt", 16384);
    // PngFile fileByes = loadBytesFromFile("images/2.png");
    // ChunkReader chunkReader(fileByes);
    // Chunks chunks = chunkReader.readSomeChunks();
    // ChunkWriter chunkWriter(chunks, "test");
    // chunkWriter.writeCriticalChunksToFile(); 

    return 0;
}