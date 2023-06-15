#ifndef FILE_ENCRYPTOR_DECRYTPTOR_HH
#define FILE_ENCRYPTOR_DECRYTPTOR_HH

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string>
std::string encryptRSA(const std::string& data, const std::string& publicKeyPath);
std::string decryptRSA(const std::string& encryptedData, const std::string& privateKeyPath);

#endif