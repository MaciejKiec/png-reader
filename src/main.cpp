#include "ChunkReader.hh"
#include "ChunkWriter.hh"
#include <memory>
#include "EncryptionDecryption/EncryptionDecryptionManager.hh"
#include "EncryptionDecryption/ECB.hh"
#include "EncryptionDecryption/CBC.hh"
#include <iostream>

int main(){
    //load PNG
    std::vector<unsigned int> fileByes = loadBytesFromFile("images/dice.png");
    ChunkReader chunkReader(fileByes);
    std::vector<Chunk*> chunks = chunkReader.readSomeChunks();
    
    //ECB ENCRYPT AND DECRYPT
    std::shared_ptr<ECB> ECBPointer = std::make_shared<ECB>();
    PngEncryptionDecryption ECB = PngEncryptionDecryption(ECBPointer, chunks, "keys/public.txt", "keys/private.txt");
    ECB.CombineIDATChunks();
    ECB.encryptDecompressed();
    //DECOMPRESSED
    chunks = ECB.getChunks();
    ChunkWriter chunkWriterEcbEncDec(chunks, "GeneratedImages/ECBEncryptedDecompressed");
    chunkWriterEcbEncDec.writeCriticalChunksToFile();
    ECB.decryptDecompressed();
    chunks = ECB.getChunks();
    ChunkWriter chunkWriterEcbDeDec(chunks, "GeneratedImages/ECBDecryptedDecompressed");
    chunkWriterEcbDeDec.writeCriticalChunksToFile();
    //COMPRESSED
    ECB.encryptCompressed();
    chunks = ECB.getChunks();
    ChunkWriter chunkWriterEcbEncCom(chunks, "GeneratedImages/ECBEncryptedCompressed");
    chunkWriterEcbEncCom.writeCriticalChunksToFile();
    ECB.decryptCompressed();
    chunks = ECB.getChunks();
    ChunkWriter chunkWriterEcbDeCom(chunks, "GeneratedImages/ECBDecryptedCompressed");
    chunkWriterEcbDeCom.writeCriticalChunksToFile();

    //CBC ENCRYPT AND DECRYPT
    std::shared_ptr<CBC> CBCPointer = std::make_shared<CBC>();
    PngEncryptionDecryption CBC = PngEncryptionDecryption(CBCPointer, chunks, "keys/public.txt", "keys/private.txt");
    //DECOMPRESSED
    CBC.encryptDecompressed();
    chunks = CBC.getChunks();
    ChunkWriter chunkWriterCBCEncDec(chunks, "GeneratedImages/CBCEncryptedDecompressed");
    chunkWriterCBCEncDec.writeCriticalChunksToFile();
    CBC.decryptDecompressed();
    chunks = CBC.getChunks();
    ChunkWriter chunkWriterCBCDeDec(chunks, "GeneratedImages/CBCDecryptedDecompressed");
    chunkWriterCBCDeDec.writeCriticalChunksToFile();
    //COMPRESSED
    CBC.encryptCompressed();
    chunks = CBC.getChunks();
    ChunkWriter chunkWriterCBCEncCom(chunks, "GeneratedImages/CBCEncryptedCompressed");
    chunkWriterCBCEncCom.writeCriticalChunksToFile();
    CBC.decryptCompressed();
    chunks = CBC.getChunks();
    ChunkWriter chunkWriterCBCDeCom(chunks, "GeneratedImages/CBCDecryptedCompressed");
    chunkWriterCBCDeCom.writeCriticalChunksToFile();

    return 0;
}