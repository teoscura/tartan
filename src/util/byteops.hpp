#ifndef BYTEOPS_H
#define BYTEOPS_H
#include <cstdint>
#include <string>
#include <vector>

#include "../minecraft/world/vector.hpp"

void writeBytes_from16bit(uint8_t *arr, uint16_t var);
void writeBytes_from32bit(uint8_t *arr, uint32_t var);
void writeBytes_from64bit(uint8_t *arr, uint64_t var);
template<typename T>
void writeBytes_fromVector(uint8_t *arr, std::vector<T> vect);
void writeBytes_fromWstring(uint8_t *arr, std::u16string string);
template<typename T>
void writeBytes_fromV2(uint8_t *arr, v2<T> vec);
template<typename T>
void writeBytes_fromV3(uint8_t *arr, v3<T> vec);
std::u16string wstring_fromBytes(const uint8_t* raw, std::size_t size);
uint16_t read2byteInt_BE(const uint8_t* raw);
uint32_t read4byteInt_BE(const uint8_t* raw);
uint64_t read8byteInt_BE(const uint8_t* raw);
void print_bytes(std::ostream& out, uint8_t* msg_buf, int dataLen, bool format = true);
std::string hexStr(const uint8_t *data, int len);

#endif