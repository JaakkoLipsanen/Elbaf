#pragma once

#include <stdint.h>

typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;

typedef float float32;
typedef double double64;

typedef uint8_t byte;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong; // most likely same as uint
typedef unsigned long long ulonglong;

// todo: include and typedef other useful stuff as well. maybe string?

template<class T, size_t N>
size_t length(T(&)[N]) { return N; }