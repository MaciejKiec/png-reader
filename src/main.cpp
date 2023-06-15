#include "ChunkReader.hh"
#include "ChunkWriter.hh"
#include "RSA/keysGenerator.hh"
#include "RSA/fileEncryptorDecryptor.hh"
typedef std::vector<unsigned int> PngFile;
typedef const std::vector<Chunk*> Chunks;

int main(){

    PngFile fileByes = loadBytesFromFile("images/1.png");
    ChunkReader chunkReader(fileByes);
    Chunks chunks = chunkReader.readSomeChunks();clear
    return 0;
}