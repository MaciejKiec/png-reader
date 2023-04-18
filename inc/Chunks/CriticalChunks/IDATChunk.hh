#ifndef IDAT_CHUNK_HH
#define IDAT_CHUNK_HH
#include "../Chunk.hh"
class IDATChunk: public Chunk{
    public:
        IDATChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32);
        void whatChunkAmI() override;
};
#endif