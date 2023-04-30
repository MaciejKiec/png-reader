#include "ChunkWriter.hh"
ChunkWriter::ChunkWriter(const std::vector<Chunk*> _chunks):
chunks(_chunks) {};

std::vector<Chunk*> ChunkWriter::getCriticalChunks(){
    std::vector<Chunk*> criticalChunks;
    for(int i = 0; i < this->chunks.size(); i++){
        for(int j = 0; j < 4; j++){
            if(this->chunks[i]->type == criticalChunksHeaders[j]){
                criticalChunks.push_back(chunks[i]);
                break;
            }
        }
    }
    return criticalChunks;
}

bool ChunkWriter::writeCriticalChunksToFile(const std::string filename){
    std::vector<Chunk*> criticalChunks = this->getCriticalChunks();
    return true;
}