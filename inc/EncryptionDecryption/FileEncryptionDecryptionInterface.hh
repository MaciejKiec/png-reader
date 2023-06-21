#ifndef FILE_ENCRYPTION_DECRYPTION_INTERFACE
#define FILE_ENCRYPTION_DECRYPTION_INTERFACE
#include <vector>
#include <string>
#include "Chunks/Chunk.hh"

class FileEncryptionDecryptionInterface{
    public:
        FileEncryptionDecryptionInterface(){};
        ~FileEncryptionDecryptionInterface(){};

        virtual void encryptDecompressed(std::vector<Chunk*>& data, const std::string& publicKeyPath) = 0;
        virtual void decryptDecompressed(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath) = 0;
        virtual void encryptCompressed(std::vector<Chunk*>& data, const std::string& publicKeyPath) = 0;
        virtual void decryptCompressed(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath) = 0;  
};

#endif

