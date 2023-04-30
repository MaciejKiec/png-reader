#ifndef CHUNK_WRITER_HH
#define CHUNK_WRITER_HH
#include <fstream>
#include "Chunks/Chunk.hh"
#include "headers.hh"

class ChunkWriter{
    private:
    std::vector<Chunk*> chunks;
    //void writeSingleChunk(Chunk* chunk);
    std::vector<Chunk*> getCriticalChunks();
    public:
    ChunkWriter(const std::vector<Chunk*> chunks);
    bool writeCriticalChunksToFile(const std::string fileName);
};
#endif 