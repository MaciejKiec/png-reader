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

    outputPNGFile.write((char*) &PNGHEADER, sizeof(PNGHEADER));
    for(int i = 0; i < criticalChunks.size(); i++){
        //reverse bit order
        uint32_t dataLength = swapEndians(criticalChunks[i]->dataLength);
        uint32_t type = swapEndians(criticalChunks[i]->type);
        uint32_t crc32 = swapEndians(criticalChunks[i]->crc32);

        outputPNGFile.write((char*) &dataLength, sizeof(dataLength));
        outputPNGFile.write((char*) &type, sizeof(type));
        for(int j = 0; j < criticalChunks[i]->data.size(); j++){
            uint8_t singleByte = criticalChunks[i]->data[j];
            outputPNGFile.write((char*) &singleByte, sizeof(uint8_t));
        }
        outputPNGFile.write((char*) &crc32, sizeof(crc32));
    }
    outputPNGFile.close();
    return true;
}