#ifndef IEND_CHUNK_HH
#define IEND_CHUNK_HH
#include "../Chunk.hh"
class IENDChunk: public Chunk{
    public:
        IENDChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32);
        void whatChunkAmI() override;
};
#endif