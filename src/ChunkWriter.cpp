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
    std::ofstream outputPNGFile(filename+".png", std::ios::binary | std::ios::out);

    if(!outputPNGFile){
        std::cerr << "Failed to create/open file " << filename << ".png!\n";
        return false;
    }

    outputPNGFile.write((char*) PNGHEADER, sizeof(PNGHEADER));
    for(int i = 0; i < criticalChunks.size(); i++){
        outputPNGFile.write((char*) &criticalChunks[i]->dataLength, sizeof(criticalChunks[i]->dataLength));
        outputPNGFile.write((char*) &criticalChunks[i]->type, sizeof(criticalChunks[i]->type));
        outputPNGFile.write((char*) &criticalChunks[i]->data, sizeof(criticalChunks[i]->data));
        outputPNGFile.write((char*) &criticalChunks[i]->crc32, sizeof(criticalChunks[i]->crc32));
    }

    outputPNGFile.close();
    return true;
}