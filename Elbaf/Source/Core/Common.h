#pragma once

#include <stdint.h>
#include <glm\glm.hpp>

/* common numeric types  */
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

/* vectors and matrices */
typedef glm::vec2 Vector2f;
typedef glm::ivec2 Vector2i;
typedef glm::vec3 Vector3f;
typedef glm::ivec3 Vector3i;
typedef glm::vec4 Vector4f;
typedef glm::ivec4 Vector4i;

typedef glm::mat4 Matrix4x4;

// todo: include and typedef other useful stuff as well. maybe string?

template<class T, size_t N>
size_t length(T(&)[N]) { return N; }