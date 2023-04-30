#ifndef CHUNK_WRITER_HH
#define CHUNK_WRITER_HH
#include <fstream>
#include "Chunks/Chunk.hh"
#include "headers.hh"
#include "OnBytesOperations.hh"

class ChunkWriter{
    private:
    std::ofstream outputPNGFile;
    std::vector<Chunk*> criticalChunks;
    const std::string fileName;

    void getCriticalChunks(std::vector<Chunk*> chunks);
    void openPNGFile();
    void writePNGHeader();
    void writeCriticalChunks();
    void closePNGFile();
    public:
    ChunkWriter(const std::vector<Chunk*> chunks, const std::string fileName);
    bool writeCriticalChunksToFile();
};
#endif 