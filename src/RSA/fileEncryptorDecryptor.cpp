#include "RSA/fileEncryptorDecryptor.hh"
#include <iostream>
// Function to encrypt data using RSA
std::string encryptRSA(const std::string& data, const std::string& publicKeyPath) {
    FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "r");
    if (!publicKeyFile) {
        std::cerr << "Error opening public key file: " << publicKeyPath << std::endl;
        return "";
    }

    RSA* rsaKey = PEM_read_RSA_PUBKEY(publicKeyFile, nullptr, nullptr, nullptr);
    fclose(publicKeyFile);

    if (!rsaKey) {
        std::cerr << "Error reading public key file" << std::endl;
        return "";
    }

    int keySize = RSA_size(rsaKey);
    std::string encryptedData(keySize, '\0');

    int result = RSA_public_encrypt(data.size(), reinterpret_cast<const unsigned char*>(data.c_str()),
                                    reinterpret_cast<unsigned char*>(&encryptedData[0]), rsaKey, RSA_PKCS1_PADDING);

    if (result == -1) {
        std::cerr << "Error encrypting data: " << ERR_error_string(ERR_get_error(), nullptr) << std::endl;
        RSA_free(rsaKey);
        return "";
    }

    RSA_free(rsaKey);
    return encryptedData;
}

// Function to decrypt data using RSA
std::string decryptRSA(const std::string& encryptedData, const std::string& privateKeyPath) {
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "r");
    if (!privateKeyFile) {
        std::cerr << "Error opening private key file: " << privateKeyPath << std::endl;
        return "";
    }

    RSA* rsaKey = PEM_read_RSAPrivateKey(privateKeyFile, nullptr, nullptr, nullptr);
    fclose(privateKeyFile);

    if (!rsaKey) {
        std::cerr << "Error reading private key file" << std::endl;
        return "";
    }

    int keySize = RSA_size(rsaKey);
    std::string decryptedData(keySize, '\0');

    int result = RSA_private_decrypt(encryptedData.size(), reinterpret_cast<const unsigned char*>(encryptedData.c_str()),
                                     reinterpret_cast<unsigned char*>(&decryptedData[0]), rsaKey, RSA_PKCS1_PADDING);

    if (result == -1) {
        std::cerr << "Error decrypting data: " << ERR_error_string(ERR_get_error(), nullptr) << std::endl;
        RSA_free(rsaKey);
        return "";
    }

    RSA_free(rsaKey);
    return decryptedData;
}