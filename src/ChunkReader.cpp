#include "ChunkReader.hh"

const std::vector<Chunk*> ChunkReader::readSomeChunks(){
    std::vector<Chunk*> chunksToReturn;
    ChunkFactory* chunkFactory = new ChunkFactory();

    checkHeader();
    while(!zeroLengthDetected){  
        readDataLength();
        readChunkType();
        readChunkData();
        readCRC32();
        chunksToReturn.push_back(chunkFactory->generateChunk(dataLength, type, data, crc32));
        clearVariables();
    }

    return chunksToReturn;
}

void ChunkReader::checkHeader(){
    if(!checkIfFileIsPNG(bytesToRead)){
        std::cerr << "Wczytany plik nie ma nagłówka PNG! Pierwsze 8 bajtów się nie zgadza!";
        exit(0);
    }
}

void ChunkReader::readDataLength(){
        dataLength = (bytesToRead[pointer] << 24) | (bytesToRead[pointer+1] << 16) | (bytesToRead[pointer+2] << 8) | bytesToRead[pointer+3];
        if(dataLength == 0) zeroLengthDetected = true;
        pointer += 4;
}

void ChunkReader::readChunkType(){
    type = (bytesToRead[pointer] << 24) | (bytesToRead[pointer+1] << 16) | (bytesToRead[pointer+2] << 8) | bytesToRead[pointer+3];
    if(zeroLengthDetected == true && type != 0x49454e44){
        std::cerr << "Wykryto chunk o zerowej długości danych i nie jest to IEND -> BŁĄD!\n";
        exit(0);
    }
    pointer += 4;
}

void ChunkReader::readChunkData(){
        for(int i = pointer; i < (pointer+dataLength) ; i++){
            data.push_back(bytesToRead[i]);
        }
        pointer += dataLength;
}

void ChunkReader::readCRC32(){
    crc32 = (bytesToRead[pointer] << 24) | (bytesToRead[pointer+1] << 16) | (bytesToRead[pointer+2] << 8) | bytesToRead[pointer+3];
    pointer += 4;
}

void ChunkReader::clearVariables(){
    this->dataLength = 0;
    this->type = 0;
    this->data = {};
    this->crc32 = 0;
}

ChunkReader::ChunkReader(const std::vector<unsigned int>& bytesToRead){
    this->bytesToRead = bytesToRead;
}