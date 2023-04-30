#ifndef HEADERS_HH
#define HEADERS_HH
#include <vector>

std::vector<unsigned int> PNG {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x01, 0x0a};
const uint32_t IHDRHeader = 0x49484452;
const uint32_t IDATHeader = 0x49444154;
const uint32_t IENDHeader = 0x49454e44;
const uint32_t PLTEHeader = 0x504C5445;
const uint32_t tEXtHeader = 0x74455874;
const uint32_t sBITHeader = 0x73424954;
const uint32_t pHYsHeader = 0x70485973;

#endif