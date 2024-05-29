#include "byteops.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

void writeBytes_from16bit(uint8_t *arr, uint16_t var){
    for(int i=0;i<2;i++){
        arr[i] = var>>8*((1-i));
    }//short-size
}
void writeBytes_from32bit(uint8_t *arr, uint16_t var){
    for(int i=0;i<4;i++){
        arr[i] = var>>(8*(3-i));
    }//protocol
}
void writeBytes_from64bit(uint8_t *arr, uint16_t var){
    for(int i=0;i<8;i++){
        arr[i] = var>>(8*(7-i));
    }//seed
}
void writeBytes_fromWstring(uint8_t* _dest, std::u16string string){
    auto i=0;
    for(char16_t wc : string){
        writeBytes_from16bit(_dest+i, wc);
        i = i + 2;
    }
}

std::u16string wstring_fromBytes(const uint8_t* raw, std::size_t size){
    std::u16string str;
    char16_t tmp; 
    for(int i=0;i<size*2;i=i+2){
        tmp = raw[i]; tmp <<= 8; tmp |= raw[i+1];
        str += tmp;
    }
    return str;
}

uint16_t read2byteInt_BE(const uint8_t* raw){
    uint16_t ui16 = 0;
    for(int i=0;i<2;i++){
        ui16 |= (raw[i]<<8*(1-i));
    }
    return ui16;
}

uint32_t read4byteInt_BE(const uint8_t* raw){
    uint32_t ui32 = 0;
    for(int i=0;i<4;i++){
        ui32 |= (raw[i]<<8*(3-i));
    }
    return ui32;
}

uint64_t read8byteInt_BE(const uint8_t* raw){
    uint64_t ui64 = 0;
    for(int i=0;i<8;i++){
        ui64 |= (raw[i]<<8*(7-i));
    }
    return ui64;
}

void print_bytes(std::ostream& out, uint8_t* msg_buf, int dataLen, bool format) {
    std::flush(out);
    out << std::setfill('0');
    for(size_t i = 0; i < dataLen; ++i) {
        out << std::hex << std::setw(2) << (int)msg_buf[i];
        if (format) {
            out << (((i + 1) % 16 == 0) ? "\n" : " ");
        }
    }
    out << std::endl;
    out << std::dec;
}

std::string hexStr(const uint8_t *data, int len){
    std::stringstream out;
    out << std::setfill('0') << "                    [DATA] ";
    for(size_t i = 0; i < len; ++i) {
        out << std::hex << std::setw(2) << (int)data[i];
        out << (((i + 1) % 32 == 0) ? "\n                           " : " ");
    }
    return out.str();
}

