#include "OnBytesOperations.hh"

std::vector<unsigned int> loadBytesFromFile(const std::string filename){
    std::ifstream input;
    input.open(filename, std::ios::binary);
    if(!input){
        std::cerr << "Failed to load the file! File name: " << filename << "\n";
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

unsigned int reverse(unsigned int x){
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));
}

int swapEndians(int value){
    int leftmost_byte;
    int left_middle_byle;
    int right_middle_byte;
    int rightmost_byte;
    int result;
    leftmost_byte = (value & 0x000000FF) >> 0;
    left_middle_byle = (value & 0x0000FF00) >> 8;
    right_middle_byte = (value & 0x00FF0000) >> 16;
    rightmost_byte = (value & 0xFF000000) >> 24;
    leftmost_byte <<= 24;
    left_middle_byle <<= 16;
    right_middle_byte <<= 8;
    rightmost_byte <<= 0;
    result = (leftmost_byte | left_middle_byle |
              right_middle_byte | rightmost_byte);
    return result;
}