#ifndef FILE_ENCRYPTION_DECRYPTION_INTERFACE
#define FILE_ENCRYPTION_DECRYPTION_INTERFACE
#include <vector>
#include <string>
#include "Chunks/Chunk.hh"

class FileEncryptionDecryptionInterface{
    public:
        FileEncryptionDecryptionInterface(){};
        ~FileEncryptionDecryptionInterface(){};

        virtual void encrypt(std::vector<unsigned int >& data, const std::string& publicKeyPath) = 0;
        virtual void decrypt(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath) = 0; 
};

#endif

