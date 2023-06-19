#ifndef FILE_ENCRYPTOR_DECRYTPTOR_HH
#define FILE_ENCRYPTOR_DECRYTPTOR_HH

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include "EncryptionDecryption/FileEncryptionDecryptionInterface.hh"
#include "EncryptionDecryption/ChunkDataAdapter.hh"

class RsaAlgorithm: public FileEncryptionDecryptionInterface{
    void encrypt(std::vector<unsigned int>& data, const std::string& publicKeyPath) override;
    void decrypt(std::vector<Chunk*>& encryptedData, const std::string& privateKeyPath) override;
};

#endif