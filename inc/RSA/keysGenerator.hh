#ifndef KEYS_GENERATOR_HH
#define KEYS_GENERATOR_HH

#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
bool generateRSAKeyPair(const std::string& publicKeyPath, const std::string& privateKeyPath, const int& keySize);
#endif