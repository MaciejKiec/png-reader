#ifndef ECB_HH
#define ECB_HH
#include "EncryptionDecryption/FileEncryptionDecryptionInterface.hh"
#include "OnBytesOperations.hh"
#include "headers.hh"
class ECB: public FileEncryptionDecryptionInterface{
    void encryptDecompressed(std::vector<Chunk*>& data, const std::string& publicKeyPath) override;
    void decryptDecompressed(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath) override;
    void encryptCompressed(std::vector<Chunk*>& data, const std::string& publicKeyPath) override;
    void decryptCompressed(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath) override;  
};


#endif