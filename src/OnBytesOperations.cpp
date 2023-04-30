#include "OnBytesOperations.hh"

std::vector<unsigned int> loadBytesFromFile(const std::string filename){
    std::ifstream input;
    input.open(filename, std::ios::binary);
    if(!input){
        std::cerr << "Failed to load the file!\n";
        exit(0);
    }

    std::vector<char> bytesRead(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    input.close();

    std::vector<unsigned int> bytesToReturn;

    for(int i = 0; i < bytesRead.size(); i++){
        bytesToReturn.push_back((0xff & (unsigned int)bytesRead[i]));
    }

    return bytesToReturn;
}

void printHexFromLoadedBytes(const std::vector<unsigned int> bytes){
    for(int i = 0; i < bytes.size(); i++){
        std::cout << std::setfill('0') << std::setw(2) << std::hex << bytes[i] << " ";
        if((i % 30 == 0) && (i != 0)) std::cout << "\n";
    }
}

bool checkIfFileIsPNG(const std::vector<unsigned int> bytes){
    if (bytes[0] != 0x89) return false;
    if (bytes[1] != 0x50) return false;
    if (bytes[2] != 0x4E) return false;
    if (bytes[3] != 0x47) return false;
    if (bytes[4] != 0x0D) return false;
    if (bytes[5] != 0x0A) return false;
    if (bytes[6] != 0x1A) return false;
    if (bytes[7] != 0x0A) return false;
   return true;
}