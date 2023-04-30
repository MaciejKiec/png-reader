#ifndef HEADERS_HH
#define HEADERS_HH
#include <vector>

inline constexpr uint64_t PNGHEADER  = 0x0a1a0a0d474e5089;
inline constexpr uint32_t IHDRHeader = 0x49484452;
inline constexpr uint32_t IDATHeader = 0x49444154;
inline constexpr uint32_t IENDHeader = 0x49454e44;
inline constexpr uint32_t PLTEHeader = 0x504C5445;
inline constexpr uint32_t tEXtHeader = 0x74455874;
inline constexpr uint32_t sBITHeader = 0x73424954;
inline constexpr uint32_t pHYsHeader = 0x70485973;
inline constexpr uint32_t criticalChunksHeaders[4] = {IHDRHeader, PLTEHeader, IDATHeader, IENDHeader};

#endif