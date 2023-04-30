#ifndef pHYs_CHUNK_HH
#define pHYs_CHUNK_HH
#include "../Chunk.hh"
class pHYsChunk: public Chunk{
    private:
    unsigned int horizontalResolution;
    unsigned int verticalResolution;
    unsigned int unitSpecifier;
    void readChunkSpecifics();
    public:
        pHYsChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32);
        void whatChunkAmI() override;
};
#endif