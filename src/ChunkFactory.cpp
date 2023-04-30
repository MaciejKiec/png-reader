#include "ChunkFactory.hh"
#include "headers.hh"

IHDRChunk* ChunkFactory::generateIHDRChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
    return new IHDRChunk(dataLength, type, data, crc32);
}
PLTEChunk* ChunkFactory::generatePLTEChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
    return new PLTEChunk(dataLength, type, data, crc32);
}

IDATChunk* ChunkFactory::generateIDATChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
    return new IDATChunk(dataLength, type, data, crc32);
}

IENDChunk* ChunkFactory::generateIENDChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
    return new IENDChunk(dataLength, type, data, crc32);
}

tEXtChunk* ChunkFactory::generatetEXtChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
    return new tEXtChunk(dataLength, type, data, crc32);
}

sBITChunk* ChunkFactory::generatesBITChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
    return new sBITChunk(dataLength, type, data, crc32);
}

Chunk* ChunkFactory::generateChunk(uint32_t dataLength, uint32_t type, std::vector<unsigned int> data, uint32_t crc32){
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
        case tEXtHeader:
            return generatetEXtChunk(dataLength, type, data, crc32);
        break;
        case sBITHeader:
            return generatesBITChunk(dataLength, type, data, crc32);
        break;
        default:
            return new Chunk(dataLength, type, data, crc32);
    }
}