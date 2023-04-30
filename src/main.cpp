#include <iostream>
#include <vector>
#include "ChunkReader.hh"


int main(){

    std::vector<unsigned int> bytes = loadBytesFromFile("images\\3.png");
    ChunkReader* chunkReader = new ChunkReader();
    std::vector<Chunk*> chunks = chunkReader->readSomeChunks(bytes);
    for(int i = 0; i < chunks.size(); i++){
       chunks[i]->whatChunkAmI();
    }
    return 0;
}