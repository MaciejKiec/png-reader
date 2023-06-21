#ifndef ENCRYPTION_DECRYPTION_MANAGER_HH
#define ENCRYPTION_DECRYPTION_MANAGER_HH
#include "EncryptionDecryption/FileEncryptionDecryptionInterface.hh"
#include "EncryptionDecryption/ChunkDataAdapter.hh"
#include "headers.hh"
#include "ChunkFactory.hh"
#include <memory>
#include <zlib.h>
#include <algorithm>

class PngEncryptionDecryption{
    private:
        std::shared_ptr<FileEncryptionDecryptionInterface> interface;
        std::vector<Chunk*> chunks;
        const std::string PublicKeyPath;
        const std::string PrivateKeyPath;

    public:
        PngEncryptionDecryption(std::shared_ptr<FileEncryptionDecryptionInterface> _interface, const std::vector<Chunk*>& _chunks, const std::string& _PublicKeyPath, const std::string& _PrivateKeyPath):
        interface(_interface), chunks(_chunks), PublicKeyPath(_PublicKeyPath), PrivateKeyPath(_PrivateKeyPath){};
        void encrypt();
        void decrypt();
        void CombineIDATChunks();
        std::vector<Chunk*> getChunks();
};


#endif