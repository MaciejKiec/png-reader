#ifndef sBIT_CHUNK_HH
#define sBIT_CHUNK_HH
#include "../Chunk.hh"
class sBITChunk: public Chunk{
    private:
        unsigned int redBits;
        unsigned int greenBits;
        unsigned int blueBits;
        unsigned int alphaBits;
        void readChunkSpecifics();
    public:
        sBITChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32);
        void whatChunkAmI() override;
};
#endif