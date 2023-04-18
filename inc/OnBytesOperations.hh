#ifndef ON_BYTES_OPERATIONS_HH
#define ON_BYTES_OPERATIONS_HH
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <string>

std::vector<unsigned int> loadBytesFromFile(const std::string filename);
void printHexFromLoadedBytes(const std::vector<unsigned int> bytes);
bool checkIfFileIsPNG(const std::vector<unsigned int> bytes);

#endif