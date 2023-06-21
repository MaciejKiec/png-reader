#ifndef CBC_HH
#define CBC_HH
#include "EncryptionDecryption/FileEncryptionDecryptionInterface.hh"
class CBC: public FileEncryptionDecryptionInterface{
    void encrypt(std::vector<Chunk*>& data, const std::string& publicKeyPath) override;
    void decrypt(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath) override; 
};


#endif