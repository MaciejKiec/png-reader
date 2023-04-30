#ifndef tEXt_CHUNK_HH
#define tEXt_CHUNK_HH
#include "../Chunk.hh"
class tEXtChunk: public Chunk{
    std::string keyword;
    std::string text;
    void readChunkSpecifics();
    public:
        tEXtChunk(uint32_t _dataLength, uint32_t _type, std::vector<unsigned int> _data, uint32_t _crc32);
        void whatChunkAmI() override;
};
#endif