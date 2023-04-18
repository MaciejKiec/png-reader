#ifndef PLTE_CHUNK_HH
#define PLTE_CHUNK_HH
#include "../Chunk.hh"
class PLTEChunk: public Chunk{
    private:
        int entriesNumber;
        void readChunkSpecifics(std::vector<unsigned int> data);
    public:
        PLTEChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32);
        void whatChunkAmI() override;
};
#endif