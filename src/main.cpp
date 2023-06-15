#include "ChunkReader.hh"
#include "ChunkWriter.hh"
#include "RSA/keysGenerator.hh"
#include "RSA/fileEncryptorDecryptor.hh"

int main(){

    generateRSAKeyPair("keys/public.txt", "keys/private.txt", 2048);
    const std::string publicKeyPath = "keys/public.txt";
    const std::string privateKeyPath = "keys/private.txt";
    
    std::string data = "Pewne dane";
    
    std::string encrypted = encryptRSA(data, publicKeyPath);
    std::cout << std::endl<< encrypted << std::endl;

    std::string decrypted = decryptRSA(encrypted, privateKeyPath);

    std::cout << std::endl << decrypted << std::endl;
    return 0;
}