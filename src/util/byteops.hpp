#ifndef BYTEOPS_H
#define BYTEOPS_H
#include <cstdint>
#include <string>
#include <vector>

#include "../minecraft/world/vector.hpp"

void writeBytes_from16bit(uint8_t *arr, uint16_t var);
void writeBytes_from32bit(uint8_t *arr, uint32_t var);
void writeBytes_from64bit(uint8_t *arr, uint64_t var);

void writeBytes_fromWstring(uint8_t *arr, std::u16string string);

template<typename T>
void writeBytes_fromV2(uint8_t *arr, v2<T> vec);

template<typename T>
void writeBytes_fromV3(uint8_t *arr, v3<T> vec);

std::u16string wstring_fromBytes(const uint8_t* raw, std::size_t size);
uint16_t read2byteInt_BE(const uint8_t* raw);
uint32_t read4byteInt_BE(const uint8_t* raw);
uint64_t read8byteInt_BE(const uint8_t* raw);

template<typename T>
v2<T> readV2_BE(uint8_t *arr);

template<typename T>
v3<T> readV3_BE(uint8_t *arr);

void print_bytes(std::ostream& out, uint8_t* msg_buf, int dataLen, bool format = true);
std::string hexStr(const uint8_t *data, int len);

template<typename T>
void writeBytes_fromVector(uint8_t *arr, std::vector<T> vect){
    int i;
    std::size_t sz = sizeof(T);
    switch(sz){
        case 1:
            for(i=0;i<vect.size();i++){
                arr[i] = vect[i];
            }
            break;
        case 2:
            for(i=0;i<vect.size();i++){
                writeBytes_from16bit(arr+i*sz, vect[i]);
            }
            break;
        case 4:
            for(i=0;i<vect.size();i++){
                writeBytes_from32bit(arr+i*sz, vect[i]);
            }
            break;
        case 8:
            for(i=0;i<vect.size();i++){
                writeBytes_from64bit(arr+i*sz, vect[i]);
            }
            break;
    }
}

template<typename T>
void writeBytes_fromV2(uint8_t *arr, v2<T> vec){
    std::size_t sz = sizeof(T);
    switch(sz){
        case 1:
            arr[0] = vec.x;
            arr[1] = vec.z;
            break;
        case 2:
            writeBytes_from16bit(arr+0*sz, vec.x);
            writeBytes_from16bit(arr+1*sz, vec.z);
            break;
        case 4:
            writeBytes_from32bit(arr+0*sz, vec.x);
            writeBytes_from32bit(arr+1*sz, vec.z);
            break;
        case 8:
            writeBytes_from64bit(arr+0*sz, vec.x);
            writeBytes_from64bit(arr+1*sz, vec.z);
            break;
    }
}

template<typename T>
void writeBytes_fromV3(uint8_t *arr, v3<T> vec){
    std::size_t sz = sizeof(T);
    switch(sz){
        case 1:
            arr[0] = vec.x;
            arr[1] = vec.y;
            arr[2] = vec.z;
            break;
        case 2:
            writeBytes_from16bit(arr+0*sz, vec.x);
            writeBytes_from16bit(arr+1*sz, vec.y);
            writeBytes_from16bit(arr+2*sz, vec.z);
            break;
        case 4:
            writeBytes_from32bit(arr+0*sz, vec.x);
            writeBytes_from32bit(arr+1*sz, vec.y);
            writeBytes_from32bit(arr+2*sz, vec.z);
            break;
        case 8:
            writeBytes_from64bit(arr+0*sz, vec.x);
            writeBytes_from64bit(arr+1*sz, vec.y);
            writeBytes_from64bit(arr+2*sz, vec.z);
            break;
    }
}

template<typename T>
v2<T> readV2_BE(uint8_t *arr){
    std::size_t sz = sizeof(T);
    v2<T> res;
    switch(sz){
        case 1:
            res.x = arr[0];
            res.z = arr[1];
            break;
        case 2:
            res.x = read2byteInt_BE(arr+0*sz);
            res.z = read2byteInt_BE(arr+1*sz);
            break;
        case 4:
            res.x = read4byteInt_BE(arr+0*sz);
            res.z = read4byteInt_BE(arr+1*sz);
            break;
        case 8:
            res.x = read8byteInt_BE(arr+0*sz);
            res.z = read8byteInt_BE(arr+1*sz);
            break;
    }
}

template<typename T>
v3<T> readV3_BE(uint8_t *arr){
    std::size_t sz = sizeof(T);
    v3<T> res;
    switch(sz){
        case 1:
            res.x = arr[0];
            res.y = arr[1];
            res.z = arr[2];
            break;
        case 2:
            res.x = read2byteInt_BE(arr+0*sz);
            res.y = read2byteInt_BE(arr+1*sz);
            res.z = read2byteInt_BE(arr+2*sz);
            break;
        case 4:
            res.x = read4byteInt_BE(arr+0*sz);
            res.y = read4byteInt_BE(arr+1*sz);
            res.z = read4byteInt_BE(arr+2*sz);
            break;
        case 8:
            res.x = read8byteInt_BE(arr+0*sz);
            res.y = read8byteInt_BE(arr+1*sz);
            res.z = read8byteInt_BE(arr+2*sz);
            break;
    }
}

#endif