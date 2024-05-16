#ifndef BYTEOPS_H
#define BYTEOPS_H
#include <cstdint>
#include <string>

void writeBytes_from16bit(uint8_t *arr, uint16_t var);
void writeBytes_from32bit(uint8_t *arr, uint16_t var);
void writeBytes_from64bit(uint8_t *arr, uint16_t var);
void writeBytes_fromWstring(uint8_t *arr, std::u16string string);
std::u16string wstring_fromBytes(const uint8_t* raw, std::size_t size);
uint16_t read2byteInt_BE(const uint8_t* raw);
uint32_t read4byteInt_BE(const uint8_t* raw);
uint64_t read8byteInt_BE(const uint8_t* raw);
void print_bytes(std::ostream& out, uint8_t* msg_buf, int dataLen, bool format = true);
std::string hexStr(const uint8_t *data, int len);

#endif