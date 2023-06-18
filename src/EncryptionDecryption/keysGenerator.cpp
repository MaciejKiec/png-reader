#include "EncryptionDecryption/keysGenerator.hh"
#include <iostream>

bool generateRSAKeyPair(const std::string& publicKeyPath, const std::string& privateKeyPath, const int& keySize){;
    RSA* rsaKey = RSA_new();
    BIGNUM* bne = BN_new();
    if (!BN_set_word(bne, RSA_F4)) {
        std::cerr << "Error setting RSA exponent" << std::endl;
        RSA_free(rsaKey);
        BN_free(bne);
        return false;
    }

    if (!RSA_generate_key_ex(rsaKey, keySize, bne, nullptr)) {
        std::cerr << "Error generating RSA key pair: " << ERR_error_string(ERR_get_error(), nullptr) << std::endl;
        RSA_free(rsaKey);
        BN_free(bne);
        return false;
    }

    EVP_PKEY* evpKey = EVP_PKEY_new();
    if (!EVP_PKEY_set1_RSA(evpKey, rsaKey)) {
        std::cerr << "Error setting RSA key" << std::endl;
        RSA_free(rsaKey);
        BN_free(bne);
        EVP_PKEY_free(evpKey);
        return false;
    }

    FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "w");
    if (!publicKeyFile) {
        std::cerr << "Error opening public key file: " << publicKeyPath << std::endl;
        RSA_free(rsaKey);
        BN_free(bne);
        EVP_PKEY_free(evpKey);
        return false;
    }

    if (!PEM_write_PUBKEY(publicKeyFile, evpKey)) {
        std::cerr << "Error writing public key file" << std::endl;
        RSA_free(rsaKey);
        BN_free(bne);
        EVP_PKEY_free(evpKey);
        fclose(publicKeyFile);
        return false;
    }

    fclose(publicKeyFile);

    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "w");
    if (!privateKeyFile) {
        std::cerr << "Error opening private key file: " << privateKeyPath << std::endl;
        RSA_free(rsaKey);
        BN_free(bne);
        EVP_PKEY_free(evpKey);
        return false;
    }

    if (!PEM_write_PKCS8PrivateKey(privateKeyFile, evpKey, nullptr, nullptr, 0, nullptr, nullptr)) {
        std::cerr << "Error writing private key file" << std::endl;
        RSA_free(rsaKey);
        BN_free(bne);
        EVP_PKEY_free(evpKey);
        fclose(privateKeyFile);
        return false;
    }

    fclose(privateKeyFile);

    RSA_free(rsaKey);
    BN_free(bne);
    EVP_PKEY_free(evpKey);
    return true;
}