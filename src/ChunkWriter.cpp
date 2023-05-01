#include "ChunkWriter.hh"


void ChunkWriter::getCriticalChunks(std::vector<Chunk*> chunks){
    for(int i = 0; i < chunks.size(); i++){
        for(int j = 0; j < 4; j++){
            if(chunks[i]->type == criticalChunksHeaders[j]){
                criticalChunks.push_back(chunks[i]);
                break;
            }
        }
    }
}

ChunkWriter::ChunkWriter(const std::vector<Chunk*> _chunks, const std::string _fileName):fileName(_fileName){
    this->getCriticalChunks(_chunks);
};


void ChunkWriter::openPNGFile(){
        this->outputPNGFile.open(fileName+".png", std::ios::binary | std::ios::out);
        if(!outputPNGFile){
        std::cerr << "Failed to create/open file " << fileName << ".png!\n";
        exit(0);
    }
}

void ChunkWriter::writePNGHeader(){
    this->outputPNGFile.write((char*) &PNGHEADER, sizeof(PNGHEADER));
}

void ChunkWriter::writeCriticalChunks(){
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
}

void ChunkWriter::closePNGFile(){
    outputPNGFile.close();
}

bool ChunkWriter::writeCriticalChunksToFile(){
    openPNGFile();
    writePNGHeader();
    writeCriticalChunks();
    closePNGFile();
    return true;
}