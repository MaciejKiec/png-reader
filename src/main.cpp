#include "ChunkReader.hh"
#include "ChunkWriter.hh"

int main(){

    std::vector<unsigned int> bytes = loadBytesFromFile("images\\3.png");
    ChunkReader* chunkReader = new ChunkReader(bytes);
    std::vector<Chunk*> chunks = chunkReader->readSomeChunks();
    /*for(int i = 0; i < chunks.size(); i++){
       chunks[i]->whatChunkAmI();
    }*/

    ChunkWriter* chunkWriter = new ChunkWriter(chunks,"test");
    chunkWriter->writeCriticalChunksToFile();
    return 0;
}