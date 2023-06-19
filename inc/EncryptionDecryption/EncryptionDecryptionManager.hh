#ifndef ENCRYPTION_DECRYPTION_MANAGER_HH
#define ENCRYPTION_DECRYPTION_MANAGER_HH
#include "EncryptionDecryption/FileEncryptionDecryptionInterface.hh"
#include "headers.hh"
#include "ChunkFactory.hh"
#include <memory>
#include <algorithm>

class PngEncryptionDecryption{
    private:
        std::shared_ptr<FileEncryptionDecryptionInterface> interface;
        std::vector<Chunk*> chunks;
        const std::string PublicKeyPath;
        const std::string PrivateKeyPath;

    public:
        PngEncryptionDecryption(std::shared_ptr<FileEncryptionDecryptionInterface> _interface, std::vector<Chunk*>& _chunks, const std::string& _PublicKeyPath, const std::string& _PrivateKeyPath):
        interface(_interface), chunks(_chunks), PublicKeyPath(_PublicKeyPath), PrivateKeyPath(_PrivateKeyPath){};
        void encrypt();
        void decrypt();
        void reduceIDATChunksSize();
        std::vector<Chunk*> getChunks();
};


#endif