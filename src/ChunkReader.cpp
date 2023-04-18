#include "ChunkReader.hh"

const std::vector<Chunk*> ChunkReader::readSomeChunks(const std::vector<unsigned int> bytesToRead){
    std::vector<Chunk*> chunksToReturn;
    ChunkFactory* chunkFactory = new ChunkFactory();
    bool zeroLengthDetected = false;

    if(!checkIfFileIsPNG(bytesToRead)){
        std::cerr << "Wczytany plik nie ma nagłówka PNG! Pierwsze 8 bajtów się nie zgadza!";
    }
    int pointer = 8;
    while(!zeroLengthDetected){
        uint32_t dataLength = (bytesToRead[pointer] << 24) | (bytesToRead[pointer+1] << 16) | (bytesToRead[pointer+2] << 8) | bytesToRead[pointer+3];
        if(dataLength == 0) zeroLengthDetected = true;
        pointer += 4;

        uint32_t type = (bytesToRead[pointer] << 24) | (bytesToRead[pointer+1] << 16) | (bytesToRead[pointer+2] << 8) | bytesToRead[pointer+3];
        if(zeroLengthDetected == true && type != 0x49454e44){
            std::cerr << "Wykryto chunk o zerowej długości danych i nie jest to IEND -> BŁĄD!\n";
            exit(0);
        }
        pointer += 4;

        std::vector<unsigned int> data = {};
        for(int i = pointer; i < (pointer+dataLength) ; i++){
            data.push_back(bytesToRead[i]);
        }
        pointer += dataLength;

        uint32_t crc32 = (bytesToRead[pointer] << 24) | (bytesToRead[pointer+1] << 16) | (bytesToRead[pointer+2] << 8) | bytesToRead[pointer+3];
        pointer += 4;


        chunksToReturn.push_back(chunkFactory->generateChunk(dataLength, type, data, crc32));
    }

    return chunksToReturn;
}