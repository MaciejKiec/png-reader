#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <string>
#include "headers.cpp"

//to do
//napisać klasy, struktury reprezentujące zadane chunki
//sprawdzić poprawność wczytywanych chunków za pomocą nayuki.io
//wykorzystać wzorzec fabryka


std::vector<unsigned int> loadBytesFromFile(const std::string filename){
    std::ifstream input(filename, std::ios::binary);
    std::vector<char> bytesRead(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    input.close();

    std::vector<unsigned int> bytesToReturn;

    for(int i = 0; i < bytesRead.size(); i++){
        bytesToReturn.push_back((0xff & (unsigned int)bytesRead[i]));
    }

    return bytesToReturn;
}

void printHexFromLoadedBytes(const std::vector<unsigned int> bytes){
    for(int i = 0; i < bytes.size(); i++){
        std::cout << std::setfill('0') << std::setw(2) << std::hex << bytes[i] << " ";
        if((i % 30 == 0) && (i != 0)) std::cout << "\n";
    }
}

bool checkIfFileIsPNG(const std::vector<unsigned int> bytes){
    if (bytes[0] != 0x89) return false;
    if (bytes[1] != 0x50) return false;
    if (bytes[2] != 0x4E) return false;
    if (bytes[3] != 0x47) return false;
    if (bytes[4] != 0x0D) return false;
    if (bytes[5] != 0x0A) return false;
    if (bytes[6] != 0x1A) return false;
    if (bytes[7] != 0x0A) return false;
   return true;
}

class Chunk{
 public:
    uint32_t dataLength;
    uint32_t type;
    std::vector<unsigned int> data;
    uint32_t crc32;

    Chunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
    dataLength(_dataLength), type(_type), data(_data), crc32(_crc32) {};

    virtual void whatChunkAmI(){
        std::ios_base::fmtflags f(std::cout.flags()); // zapisujemy flagi strumienia, żeby tylko te informacje były wyświetlane w formie hex
        std::cout << "Im not implemented chunk, but my type is: " << std::hex <<type << "\n\n";
        std::cout.flags(f); // przywracamy oryginale flagi sturmienia
    }
};

class IHDRChunk: public Chunk{
    private:
        uint32_t width;
        uint32_t height;
        unsigned int bitDepth;
        unsigned int colorType;
        unsigned int compressionMethod;
        unsigned int filterMethod;
        unsigned int interlaceMethod;

        void readChunkSpecifics(std::vector<unsigned int> data){
            width = (data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]);
            height = (data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7]);
            bitDepth = data[8];
            colorType = data[9];
            compressionMethod = data[10];
            filterMethod = data[11];
            interlaceMethod = data[12];
        }
    public:
        IHDRChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32): Chunk(_dataLength, _type, _data, _crc32){
            readChunkSpecifics(_data);
        };

        void whatChunkAmI() override{
            std::cout << "I'm HDR chunk! My specifics:\n";
            std::cout << "Width: " << width << " pixels\n";
            std::cout << "Height: " << height << " pixels\n";
            std::cout << "Bit depth: " << bitDepth << " bits per pixel\n";
            std::cout << "Color type: " << colorType << "\n";
            std::cout << "Filter method: " << filterMethod<< "\n";
            std::cout << "Interlace method: " << interlaceMethod << "\n\n";
        }
};

class PLTEChunk: public Chunk{
    private:
        int entriesNumber = 0;

        void readChunkSpecifics(std::vector<unsigned int> data){
            entriesNumber = data.size() / 3;
        }

    public:
        PLTEChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32): Chunk(_dataLength, _type, _data, _crc32){
            if(_data.size() % 3 != 0){
                std::cout << "PLTE chunk error! Data length is not divisible by 3!\n";
            }
            readChunkSpecifics(_data);
        };

        void whatChunkAmI() override{
            std::cout << "I'm PLTE chunk!\n";
            std::cout << "Number of entries: " << entriesNumber << "\n\n";
        }
};

class IDATChunk: public Chunk{
    public:
        IDATChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
            Chunk(_dataLength, _type, _data, _crc32) {};

        void whatChunkAmI() override{
            std::cout << "I'm IDAT chunk!\n";
            std::cout << "Data length: " << dataLength << " bytes\n\n";
        }
};

class IENDChunk: public Chunk{
    public:
        IENDChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32):
            Chunk(_dataLength, _type, _data, _crc32) {};

        void whatChunkAmI() override{
            std::cout << "I'm IEND chunk!\n\n";
        }
};

class ChunkFactory{
    private:
        IHDRChunk* generateIHDRChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
            return new IHDRChunk(dataLength, type, data, crc32);
        }
        PLTEChunk* generatePLTEChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
            return new PLTEChunk(dataLength, type, data, crc32);
        }

        IDATChunk* generateIDATChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
            return new IDATChunk(dataLength, type, data, crc32);
        }

        IENDChunk* generateIENDChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
            return new IENDChunk(dataLength, type, data, crc32);
        }
    public:
        Chunk* generateChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
            switch(type){
                case IHDRHeader:
                    return generateIHDRChunk(dataLength, type, data, crc32);
                break;
                case PLTEHeader:
                    return generatePLTEChunk(dataLength, type, data, crc32);
                break;
                case IDATHeader:
                    return generateIDATChunk(dataLength, type, data, crc32);
                break;
                case IENDHeader:
                    return generateIENDChunk(dataLength, type, data, crc32);
                break;
                default:
                    return new Chunk(dataLength, type, data, crc32);
            }
        }

};

class ChunkReader{
    public:
    const std::vector<Chunk*> readSomeChunks(const std::vector<unsigned int> bytesToRead){
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

};

int main(){
    std::vector<unsigned int> bytes = loadBytesFromFile("2.png");
    ChunkReader* chunkReader = new ChunkReader();
    std::vector<Chunk*> chunks = chunkReader->readSomeChunks(bytes);
    for(int i = 0; i < chunks.size(); i++){
       chunks[i]->whatChunkAmI();
    }
    return 0;
}




/*
std::vector<unsigned int> bytes = loadBytesFromFile("2.png");
ChunkReader *chunkReader = new ChunkReader();
std::vector<Chunk> chunks = chunkReader->readSomeChunks(bytes);
for(int i = 0; i < chunks.size(); i++){
    std::cout << chunks[i].dataLength << "\n";
}
*/