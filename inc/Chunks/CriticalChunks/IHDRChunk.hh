#ifndef IHDR_CHUNK_HH
#define IHDR_CHUNK_HH
#include "../Chunk.hh"
class IHDRChunk: public Chunk{
    private:
        uint32_t width;
        uint32_t height;
        unsigned int bitDepth;
        unsigned int colorType;
        unsigned int compressionMethod;
        unsigned int filterMethod;
        unsigned int interlaceMethod;
        void readChunkSpecifics(std::vector<unsigned int> data);
    public:
        IHDRChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32);
        void whatChunkAmI() override;
};
#endif