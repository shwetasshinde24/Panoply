// #include <assert.h>
// #include <dirent.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <grp.h>
// #include <limits.h>
// #include <pthread.h>
// #include <pwd.h>
// #include <stdarg.h>
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <sys/uio.h>
// #include <unistd.h>
// #include <openssl/rand.h>
// #include <openssl/ssl.h>
// #ifdef __linux__
// #include <sys/prctl.h>
// #endif
// #include "neverbleed.h"

#define __OPTIMIZE__ 1
#include <stdarg.h>
// #include <stdio.h>      /* vsnprintf */
#include <sgx_stdio_util.h>
// #include <stdlib.h>
#include <sgx_stdlib_util.h>
#include <sgx_fcntl_util.h>>
// #include <unistd.h> 
#include <sgx_unistd_util.h>
#include <sgx/sys/types.h>
#include <sgx_sysstat_util.h>

#include <sgx_sysuio_util.h> //writev()
// #include <sgx_sysprctl_util.h>
// #include <sys/prctl.h> //prctl()
#include <sgx_grp_util.h> //initgroups()
// #include <pwd.h> //getpwnam_r()
#include <sgx_pwd_util.h>
#include <sgx_pthread_util.h>
#include <sgx_netinetin_util.h>
#include <sgx_syssocket_util.h>
#include <sgx_unistd_util.h>

#ifndef STRING_DUP_H
#define STRING_DUP_H
#include <stdlib.h>
#include <string.h>

// #include <openssl/bn.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#include <H2oEnclave_t.h>

const unsigned char my_cert_array[878] = {
  0x30,0x82,0x03,0x6A,0x30,0x82,0x02,0x52,0x02,0x09,0x00,0xE4,0xC4,0xC4,0x30,0x36,0xF5,0x58,0x58,0x30,0x0D,0x06,0x09,0x2A,
0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x0B,0x05,0x00,0x30,0x77,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x73,
0x67,0x31,0x12,0x30,0x10,0x06,0x03,0x55,0x04,0x08,0x0C,0x09,0x73,0x69,0x6E,0x67,0x61,0x70,0x6F,0x72,0x65,0x31,0x0B,0x30,
0x09,0x06,0x03,0x55,0x04,0x07,0x0C,0x02,0x73,0x67,0x31,0x0C,0x30,0x0A,0x06,0x03,0x55,0x04,0x0A,0x0C,0x03,0x6E,0x75,0x73,
0x31,0x0C,0x30,0x0A,0x06,0x03,0x55,0x04,0x0B,0x0C,0x03,0x6E,0x75,0x73,0x31,0x0D,0x30,0x0B,0x06,0x03,0x55,0x04,0x03,0x0C,
0x04,0x74,0x65,0x73,0x74,0x31,0x1C,0x30,0x1A,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x09,0x01,0x16,0x0D,0x61,0x62,
0x63,0x40,0x79,0x61,0x68,0x6F,0x6F,0x2E,0x63,0x6F,0x6D,0x30,0x1E,0x17,0x0D,0x31,0x36,0x30,0x37,0x32,0x30,0x30,0x35,0x32,
0x34,0x31,0x36,0x5A,0x17,0x0D,0x31,0x37,0x30,0x37,0x32,0x30,0x30,0x35,0x32,0x34,0x31,0x36,0x5A,0x30,0x77,0x31,0x0B,0x30,
0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x73,0x67,0x31,0x12,0x30,0x10,0x06,0x03,0x55,0x04,0x08,0x0C,0x09,0x73,0x69,0x6E,
0x67,0x61,0x70,0x6F,0x72,0x65,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x07,0x0C,0x02,0x73,0x67,0x31,0x0C,0x30,0x0A,0x06,
0x03,0x55,0x04,0x0A,0x0C,0x03,0x6E,0x75,0x73,0x31,0x0C,0x30,0x0A,0x06,0x03,0x55,0x04,0x0B,0x0C,0x03,0x6E,0x75,0x73,0x31,
0x0D,0x30,0x0B,0x06,0x03,0x55,0x04,0x03,0x0C,0x04,0x74,0x65,0x73,0x74,0x31,0x1C,0x30,0x1A,0x06,0x09,0x2A,0x86,0x48,0x86,
0xF7,0x0D,0x01,0x09,0x01,0x16,0x0D,0x61,0x62,0x63,0x40,0x79,0x61,0x68,0x6F,0x6F,0x2E,0x63,0x6F,0x6D,0x30,0x82,0x01,0x22,
0x30,0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x01,0x05,0x00,0x03,0x82,0x01,0x0F,0x00,0x30,0x82,0x01,0x0A,
0x02,0x82,0x01,0x01,0x00,0xAA,0xBF,0x70,0x54,0xF1,0x3E,0x53,0x7D,0xAA,0x82,0x9D,0x4C,0x61,0x02,0xE3,0xF9,0xB9,0x4D,0x6F,
0x1E,0xDF,0x4E,0x4B,0xA2,0x88,0x0D,0xFA,0xA3,0xCD,0x45,0xBC,0x5C,0x4F,0x45,0xC0,0x89,0x44,0xB6,0xD9,0x60,0x73,0x3C,0x99,
0x4C,0xA3,0x03,0x9B,0xDA,0x27,0x59,0x0D,0x34,0xC0,0x2B,0x49,0x7A,0xAB,0x3C,0xA6,0x7F,0xFC,0x40,0x02,0x2C,0xC7,0x03,0xC5,
0x45,0x95,0xEB,0x5E,0x17,0x1D,0xB0,0x9A,0x13,0x1A,0xEE,0xA6,0x6A,0x46,0x90,0x2E,0xAC,0x2E,0x3C,0xEF,0x19,0x3B,0x0A,0xA7,
0x59,0xB7,0x88,0x9C,0xCE,0x72,0x1A,0x4C,0x0A,0x24,0xA2,0x79,0x54,0x44,0xB9,0x3A,0xAE,0x56,0x0B,0xFE,0x46,0x5B,0xFE,0x1A,
0x3A,0xB3,0x21,0x6E,0xA8,0x12,0x7A,0x02,0xB9,0xF6,0xB5,0x36,0xC8,0xF9,0xC7,0x50,0x96,0xD8,0xE6,0x89,0x31,0xCB,0x5F,0x79,
0x55,0x4B,0xF7,0x32,0x94,0x41,0xF8,0x38,0xEC,0x18,0x41,0x80,0xEB,0x37,0xF5,0xCB,0x58,0x4C,0x2A,0x9B,0x28,0x8D,0x6E,0x58,
0x71,0x3F,0xE0,0x64,0xED,0xEF,0x1C,0xF5,0x79,0xCC,0xA1,0x92,0x11,0xC0,0x28,0x8D,0x45,0x46,0x2B,0x0A,0x3B,0xF9,0x52,0x3B,
0xDC,0x1B,0x46,0x01,0x5B,0xB7,0xE4,0x5A,0xBE,0x41,0xE6,0x15,0xBD,0x11,0x7B,0x3F,0x46,0x6C,0x2D,0x4E,0x40,0x79,0xEB,0xFE,
0x66,0x3D,0x26,0x41,0xE6,0xA3,0x38,0xA5,0xF2,0xA7,0x39,0x86,0x4F,0xD8,0x23,0xDE,0xCF,0xFB,0xA5,0xCE,0xBE,0x5D,0x58,0xF7,
0x1B,0x9A,0x04,0x1B,0xBF,0xA6,0x50,0xF0,0x87,0x6D,0xE0,0x12,0x05,0x56,0x24,0x89,0xEF,0x8B,0x15,0xFA,0x89,0x02,0x03,0x01,
0x00,0x01,0x30,0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x0B,0x05,0x00,0x03,0x82,0x01,0x01,0x00,0x96,0xEB,
0xE0,0x57,0xE3,0xE1,0x13,0xCA,0x2D,0x43,0x60,0x9B,0xE0,0xB9,0x2E,0xAD,0xE7,0xD6,0x12,0xF0,0xC6,0x00,0xB4,0xD0,0xDE,0x5D,
0xA0,0x35,0xF2,0x22,0xF0,0x2E,0xF1,0x67,0xDA,0x51,0x32,0x39,0x58,0xA6,0xF9,0x55,0x8F,0x5C,0x76,0xE3,0x91,0x2F,0x0E,0x83,
0x86,0x56,0xB7,0x71,0xBB,0x0A,0x3D,0x05,0xE1,0xC2,0x2C,0x0B,0x46,0xA5,0x71,0x9A,0x32,0xD3,0x91,0x85,0x2D,0xBB,0x15,0x59,
0x7E,0xB0,0x8A,0xFF,0x7B,0x0B,0x76,0x87,0x38,0x17,0xDF,0xB7,0x46,0x94,0xEC,0x41,0x8A,0xF1,0xC0,0x05,0xF3,0xA9,0x20,0xB3,
0x92,0x5D,0x51,0xF7,0x5C,0xE6,0x61,0xA2,0xF3,0x71,0xE7,0xB4,0x74,0x00,0x7E,0xEB,0xFB,0xC6,0xB5,0x5C,0xC0,0x94,0x5D,0x1C,
0x33,0x2F,0x33,0xC0,0x07,0xBD,0x8A,0x66,0xB5,0x1D,0xB4,0x19,0xC6,0x14,0x89,0x50,0xA6,0x18,0x37,0x46,0xCB,0xBB,0x7E,0x3E,
0x1C,0xAA,0xF7,0x60,0x11,0xA6,0xA4,0xBD,0x50,0x15,0xB8,0xE6,0x53,0x60,0x91,0xC5,0x5C,0xD1,0xD5,0x7F,0x4C,0x33,0xAC,0xE6,
0x78,0x26,0x35,0x13,0x56,0xEF,0xF7,0x62,0xE0,0x5C,0xFB,0x6C,0x94,0x95,0x99,0xBE,0x3A,0x09,0x86,0x8F,0xF7,0x56,0xE7,0x21,
0x6F,0xD8,0x0A,0x54,0x54,0x63,0x83,0x5B,0xD9,0xF8,0xDB,0x0B,0x05,0x92,0xDB,0xFA,0x70,0x3E,0x10,0x24,0x80,0x6B,0xFB,0x9F,
0x07,0xF3,0x07,0x26,0x13,0xD1,0xA5,0x2F,0x8C,0x60,0x91,0x6A,0xCC,0xAF,0x73,0x12,0xCC,0xBA,0x41,0xE2,0x05,0xCE,0x73,0xF5,
0xA2,0xDC,0x39,0x2A,0xFA,0xAF,0xD9,0x3E,0xEB,0x1B,0xBF,0x8A,0xC8,0x63 };

const unsigned char my_priv_key_arr[1192] = {
0x30,0x82,0x04,0xA4,0x02,0x01,0x00,0x02,0x82,0x01,0x01,0x00,0xAA,0xBF,0x70,0x54,0xF1,0x3E,0x53,0x7D,0xAA,0x82,0x9D,0x4C,
0x61,0x02,0xE3,0xF9,0xB9,0x4D,0x6F,0x1E,0xDF,0x4E,0x4B,0xA2,0x88,0x0D,0xFA,0xA3,0xCD,0x45,0xBC,0x5C,0x4F,0x45,0xC0,0x89,
0x44,0xB6,0xD9,0x60,0x73,0x3C,0x99,0x4C,0xA3,0x03,0x9B,0xDA,0x27,0x59,0x0D,0x34,0xC0,0x2B,0x49,0x7A,0xAB,0x3C,0xA6,0x7F,
0xFC,0x40,0x02,0x2C,0xC7,0x03,0xC5,0x45,0x95,0xEB,0x5E,0x17,0x1D,0xB0,0x9A,0x13,0x1A,0xEE,0xA6,0x6A,0x46,0x90,0x2E,0xAC,
0x2E,0x3C,0xEF,0x19,0x3B,0x0A,0xA7,0x59,0xB7,0x88,0x9C,0xCE,0x72,0x1A,0x4C,0x0A,0x24,0xA2,0x79,0x54,0x44,0xB9,0x3A,0xAE,
0x56,0x0B,0xFE,0x46,0x5B,0xFE,0x1A,0x3A,0xB3,0x21,0x6E,0xA8,0x12,0x7A,0x02,0xB9,0xF6,0xB5,0x36,0xC8,0xF9,0xC7,0x50,0x96,
0xD8,0xE6,0x89,0x31,0xCB,0x5F,0x79,0x55,0x4B,0xF7,0x32,0x94,0x41,0xF8,0x38,0xEC,0x18,0x41,0x80,0xEB,0x37,0xF5,0xCB,0x58,
0x4C,0x2A,0x9B,0x28,0x8D,0x6E,0x58,0x71,0x3F,0xE0,0x64,0xED,0xEF,0x1C,0xF5,0x79,0xCC,0xA1,0x92,0x11,0xC0,0x28,0x8D,0x45,
0x46,0x2B,0x0A,0x3B,0xF9,0x52,0x3B,0xDC,0x1B,0x46,0x01,0x5B,0xB7,0xE4,0x5A,0xBE,0x41,0xE6,0x15,0xBD,0x11,0x7B,0x3F,0x46,
0x6C,0x2D,0x4E,0x40,0x79,0xEB,0xFE,0x66,0x3D,0x26,0x41,0xE6,0xA3,0x38,0xA5,0xF2,0xA7,0x39,0x86,0x4F,0xD8,0x23,0xDE,0xCF,
0xFB,0xA5,0xCE,0xBE,0x5D,0x58,0xF7,0x1B,0x9A,0x04,0x1B,0xBF,0xA6,0x50,0xF0,0x87,0x6D,0xE0,0x12,0x05,0x56,0x24,0x89,0xEF,
0x8B,0x15,0xFA,0x89,0x02,0x03,0x01,0x00,0x01,0x02,0x82,0x01,0x00,0x7D,0xDD,0x7C,0xBA,0xC0,0xD2,0x86,0xCD,0x1D,0xC2,0x06,
0x9D,0xE4,0xED,0x32,0x8C,0x45,0x12,0x55,0x95,0x56,0x5A,0xEA,0xDA,0x36,0x9C,0xC7,0x63,0xB3,0xCF,0x72,0x18,0x41,0xBF,0x53,
0x3C,0x5C,0xD0,0xC4,0xD0,0x9A,0x61,0xD3,0x47,0x70,0xEB,0x1A,0x19,0xE7,0xE3,0x77,0x1E,0xA9,0x81,0xBF,0x3A,0x93,0xBB,0xB3,
0xA8,0xA8,0x93,0xAE,0x86,0xBF,0x75,0x82,0x17,0xD7,0x79,0x96,0xF4,0x47,0x48,0x85,0x6B,0x0B,0xF1,0x5B,0xEE,0xFF,0x71,0x0D,
0x56,0x93,0x07,0x0B,0xE1,0x77,0x6A,0x55,0x0E,0x87,0x82,0x46,0xC4,0xCF,0xCB,0x9E,0xBD,0xE3,0x5F,0x79,0x3C,0xAB,0x24,0x37,
0xA3,0x87,0x7E,0x73,0xC3,0xFD,0xD0,0x04,0x19,0xBD,0x2E,0x29,0xD9,0xEF,0x34,0xCD,0x89,0xB3,0xD8,0xC5,0x36,0x90,0x57,0x10,
0x33,0x95,0x1D,0xB0,0xFE,0xC0,0x3C,0xD4,0xCE,0xF7,0xDD,0xB3,0x05,0xAD,0x8A,0x3C,0x63,0x53,0xBE,0x9E,0x92,0xE9,0x32,0x88,
0xF0,0x00,0x21,0x92,0x40,0xD3,0xC9,0x8E,0x9D,0x41,0xE0,0x73,0x91,0x91,0x96,0x27,0x1A,0x4D,0x92,0xCF,0x5E,0x08,0xC3,0xD1,
0x0B,0xE1,0x42,0x89,0x03,0x63,0xEF,0xF1,0xD1,0xFC,0x22,0x40,0x0B,0x68,0x49,0x3A,0x51,0x49,0x1A,0xC1,0xFC,0x2B,0xD5,0x98,
0x6B,0x6A,0x06,0x47,0x3B,0x58,0xD1,0x39,0x04,0x65,0x21,0x8B,0xFD,0x56,0x2F,0x67,0x14,0xC8,0x65,0xDE,0xE1,0x64,0xA1,0xFD,
0x3B,0xF2,0x53,0x0F,0x09,0x96,0x57,0xBA,0x10,0x1B,0x1B,0xDE,0x25,0x19,0x74,0x1D,0x9C,0x90,0xC3,0xEB,0x24,0x7C,0x81,0xB1,
0xD9,0xDE,0x4D,0x41,0x39,0x02,0x81,0x81,0x00,0xDD,0x99,0xFC,0x1E,0xF2,0xF6,0xED,0xD5,0x0E,0x1F,0x4C,0x36,0xD4,0x37,0xAD,
0x25,0xB5,0xC5,0xF6,0x4B,0x93,0x55,0x42,0x4E,0x20,0x78,0xFE,0x29,0xC7,0xB5,0x0A,0xDC,0xCB,0xF5,0xD7,0xCC,0x63,0xBB,0xFA,
0xF4,0xC4,0x31,0x0E,0x0C,0x89,0x5D,0xE5,0x31,0x00,0x59,0xE3,0x4B,0xC3,0x6E,0x10,0xC7,0xB6,0x61,0xE7,0xFB,0x26,0x46,0x5D,
0x12,0xBD,0x52,0x95,0x59,0x6D,0x40,0xAD,0x0F,0x1A,0xD1,0x00,0x08,0x99,0xAC,0x1B,0x82,0xB8,0x81,0x4C,0x8F,0xCC,0x67,0x36,
0xD5,0x27,0xDE,0x0D,0x1C,0xDB,0x9B,0x48,0xCB,0x39,0xD8,0x2E,0x9B,0x70,0xF8,0x41,0x77,0x67,0x18,0x04,0x81,0x2B,0xEF,0xFD,
0x03,0x7F,0x19,0xB5,0x70,0x17,0x86,0x05,0x2D,0x30,0x64,0x2E,0x7F,0xEC,0x2E,0xE2,0x27,0x02,0x81,0x81,0x00,0xC5,0x40,0xA0,
0x5E,0x8F,0xBB,0xE0,0x5A,0xB5,0x5E,0x29,0xE5,0xF1,0xA2,0x7C,0xEC,0xBC,0xD7,0xB5,0x9E,0xBA,0x38,0xB8,0x3B,0x0F,0x36,0x96,
0x6A,0xF9,0x7F,0x65,0x92,0x87,0xCB,0x0C,0xC7,0xA9,0x71,0x20,0x76,0xC5,0x8A,0x57,0xFF,0xA9,0xB8,0xD8,0x1F,0xF2,0x1B,0x72,
0xF5,0xFD,0x8F,0x0A,0x50,0xF9,0x97,0x8E,0xE9,0x44,0x2A,0x82,0xB6,0x33,0xC9,0x2C,0xE4,0xB3,0x84,0x0F,0xA6,0x4A,0x97,0xF4,
0x02,0x8D,0xFF,0xD9,0xD2,0xFB,0xC7,0x35,0x19,0x40,0x34,0xEB,0xDA,0x12,0xCC,0x6C,0xFF,0xFA,0xA3,0x93,0x35,0x63,0x7D,0x49,
0xE6,0xA5,0xAA,0x91,0x09,0x40,0x74,0x99,0xEB,0x10,0xCD,0xC5,0xE5,0x44,0x0C,0x0C,0x4B,0xE1,0x9C,0x1B,0xFF,0x65,0x00,0x28,
0x14,0x50,0xF5,0x1B,0xCF,0x02,0x81,0x81,0x00,0x83,0xD6,0x6E,0xC6,0xC2,0xE9,0xE1,0x89,0x15,0xC3,0xCD,0x05,0xF9,0xAF,0xBE,
0x15,0x67,0x55,0x85,0x38,0x65,0x49,0x1E,0x0F,0x79,0x06,0x42,0xBF,0xFC,0x8E,0x5B,0x0E,0x0D,0x52,0x0F,0xB7,0x0B,0xC6,0xF4,
0x80,0xD6,0x90,0x10,0xB9,0xA8,0xA7,0xF2,0x08,0xFB,0x1A,0x7F,0x3D,0xBD,0xE1,0x27,0x9E,0x89,0x85,0x2A,0x0C,0xA3,0x32,0xCD,
0x80,0xAE,0x9E,0x09,0x38,0x90,0xE5,0x1F,0x90,0x92,0xF5,0xB0,0xBD,0x6D,0x1F,0x95,0xA6,0x69,0xBA,0x93,0x20,0x22,0x0D,0x6D,
0xF3,0xD6,0xAA,0x26,0xC6,0xFA,0x68,0x22,0x20,0xB6,0x23,0x45,0x67,0x39,0x08,0x99,0x7A,0x3E,0x1D,0x6D,0xE0,0xA3,0x91,0x3D,
0xC7,0xEC,0xC0,0x10,0xCF,0xC5,0x4E,0xF8,0x99,0x6F,0xE6,0xCA,0x3B,0x54,0xFA,0x77,0x95,0x02,0x81,0x80,0x08,0x64,0xF0,0xAE,
0x35,0x85,0xB4,0x4D,0x87,0xEC,0x62,0xF2,0x13,0x2F,0x6C,0x0B,0x93,0x19,0xC6,0xF3,0xE3,0x4E,0xE8,0xA0,0x32,0xCC,0x8A,0xE8,
0x30,0x87,0xF8,0x65,0x9C,0xFB,0xCA,0x26,0x71,0x12,0x8C,0x64,0x21,0x91,0xFA,0x9E,0xB9,0xB5,0x51,0x15,0x42,0xF3,0x62,0x18,
0x0F,0xDB,0x57,0x80,0x0C,0xAF,0x23,0x78,0xCF,0xDA,0xD3,0x47,0x37,0xBA,0xF6,0xFB,0x20,0x9C,0x9D,0x21,0xE1,0x88,0xC7,0xEC,
0x97,0xE8,0x6C,0x77,0xAB,0x19,0x56,0x2C,0x25,0xEC,0x5A,0xA1,0x24,0x2D,0xA8,0xF1,0xD7,0xD3,0xC0,0x3F,0x04,0x65,0xDF,0x90,
0x3E,0x3A,0x9D,0x03,0x7C,0xC7,0xB9,0x89,0x24,0x64,0xED,0x68,0x0D,0x56,0x49,0xEB,0xAC,0xC5,0x3C,0xF7,0xC8,0x6F,0x92,0x45,
0x13,0x10,0xEB,0x47,0x02,0x81,0x81,0x00,0xAB,0xF9,0x69,0xAC,0x8E,0xAD,0xF2,0x51,0x40,0x04,0x56,0x79,0xDE,0xCA,0x86,0xE0,
0x31,0x6C,0x5F,0x89,0x4B,0x81,0x53,0x8E,0x5B,0x23,0x3A,0x88,0x46,0x80,0x55,0x09,0xA5,0x9B,0xDC,0x73,0xA3,0x6A,0xE6,0x61,
0x26,0xB0,0xAE,0xFE,0x3D,0x9B,0xF3,0xCD,0x7B,0xC5,0xFB,0xCA,0xD1,0xD1,0x19,0x4B,0x67,0x5D,0x80,0xEC,0x51,0x74,0x0F,0xFD,
0x8F,0x6F,0x50,0xC1,0x9D,0xC0,0x78,0x1C,0x46,0xA7,0xF5,0xC8,0x04,0xEF,0x9F,0x48,0x97,0x83,0x7D,0x9B,0xD6,0xB1,0x3B,0x16,
0x2A,0xC8,0x3F,0xF1,0xC6,0x07,0x76,0x73,0x1A,0x77,0xC8,0xB0,0x7D,0xD9,0x8B,0x66,0xBA,0x6E,0xE3,0x76,0x3D,0x04,0xDA,0x2A,
0xB5,0xD8,0x41,0xAD,0xD5,0xCA,0x73,0xFF,0xE2,0xF1,0xE9,0x78,0x7F,0xC3,0x7C,0x6F
};

X509 *my_cert = NULL;

// extern 
static inline char *strdup (const char *s) {
  if (s == NULL) return NULL;  
    int len = strlen (s) + 1;
    char *d = (char*)malloc (len);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strncpy (d,s,len);                        // Copy the characters
    return d;                            // Return the new string
}
#endif
// #include <dirent.h>
#include <sgx_dirent_util.h>
#include "H2oEnclave.h"

int ecall_neverbleed_sample()
{
  printf("IN NEVERBLEED\n");
  return 0;

}

struct expbuf_t {
    char *buf;
    char *start;
    char *end;
    size_t capacity;
};

struct st_neverbleed_rsa_exdata_t {
    neverbleed_t *nb;
    size_t key_index;
};

struct st_neverbleed_thread_data_t {
    pid_t self_pid;
    int fd;
};

// static void warnvf(const char *fmt, va_list args)
// {
//     char errbuf[256];

//     if (errno != 0) {
//         strerror_r(errno, errbuf, sizeof(errbuf));
//     } else {
//         errbuf[0] = '\0';
//     }

//    fprintf(stderr, "[openssl-privsep] ");
//    vfprintf(stderr, fmt, args);
//    if (errbuf[0] != '\0')
//        fputs(errbuf, stderr);
//    fputc('\n', stderr);
// }

// __attribute__((format(printf, 1, 2))) static void warnf(const char *fmt, ...)
// {
//     va_list args;

//     va_start(args, fmt);
//     warnvf(fmt, args);
//     va_end(args);
// }

// __attribute__((format(printf, 1, 2), noreturn)) static void dief(const char *fmt, ...)
// {
//     va_list args;

//     va_start(args, fmt);
//     warnvf(fmt, args);
//     va_end(args);

//     abort();
// }

#define warnf(A, ...) printf(A, ##__VA_ARGS__)
#define dief(A, ...) printf(A, ##__VA_ARGS__)

static char *dirname(const char *path)
{
    const char *last_slash = strrchr(path, '/');
    char *ret;

    if (last_slash == NULL) {
        errno = 0;
        dief("dirname: no slash in given path:%s", path);
    }
    if ((ret = malloc(last_slash + 1 - path)) == NULL)
        dief("no memory");
    memcpy(ret, path, last_slash - path);
    ret[last_slash - path] = '\0';
    return ret;
}

static void set_cloexec(int fd)
{
   if (fcntl(fd, F_SETFD, O_CLOEXEC) == -1)
       dief("failed to set O_CLOEXEC to fd %d", fd);
}

static int read_nbytes(int fd, void *p, size_t sz)
{
   while (sz != 0) {
       ssize_t r;
       while ((r = read(fd, p, sz)) == -1 && errno == EINTR)
           ;
       if (r == -1) {
           return -1;
       } else if (r == 0) {
           errno = 0;
           return -1;
       }
       p = (char *)p + r;
       sz -= r;
   }
   return 0;
}

static size_t expbuf_size(struct expbuf_t *buf)
{
    return buf->end - buf->start;
}


static void expbuf_dispose(struct expbuf_t *buf)
{
   if (buf->capacity != 0)
       OPENSSL_cleanse(buf->buf, buf->capacity);
   free(buf->buf);
   memset(buf, 0, sizeof(*buf));
}

static void expbuf_reserve(struct expbuf_t *buf, size_t extra)
{
    char *n;

    if (extra <= buf->buf + buf->capacity - buf->end)
        return;

    if (buf->capacity == 0)
        buf->capacity = 4096;
    while (buf->buf + buf->capacity - buf->end < extra)
        buf->capacity *= 2;
    if ((n = realloc(buf->buf, buf->capacity)) == NULL)
        dief("realloc failed");
    buf->start += n - buf->buf;
    buf->end += n - buf->buf;
    buf->buf = n;
}

static void expbuf_push_num(struct expbuf_t *buf, size_t v)
{
    expbuf_reserve(buf, sizeof(v));
    memcpy(buf->end, &v, sizeof(v));
    buf->end += sizeof(v);
}

static void expbuf_push_str(struct expbuf_t *buf, const char *s)
{
    size_t l = strlen(s) + 1;
    expbuf_reserve(buf, l);
    memcpy(buf->end, s, l);
    buf->end += l;
}


static void expbuf_push_bytes(struct expbuf_t *buf, const void *p, size_t l)
{
    expbuf_push_num(buf, l);
    expbuf_reserve(buf, l);
    memcpy(buf->end, p, l);
    buf->end += l;
}

static int expbuf_shift_num(struct expbuf_t *buf, size_t *v)
{
    if (expbuf_size(buf) < sizeof(*v))
        return -1;
    memcpy(v, buf->start, sizeof(*v));
    buf->start += sizeof(*v);
    return 0;
}


static char *expbuf_shift_str(struct expbuf_t *buf)
{
    char *nul = memchr(buf->start, '\0', expbuf_size(buf)), *ret;
    if (nul == NULL)
        return NULL;
    ret = buf->start;
    buf->start = nul + 1;
    return ret;
}

static void *expbuf_shift_bytes(struct expbuf_t *buf, size_t *l)
{
    void *ret;
    if (expbuf_shift_num(buf, l) != 0)
        return NULL;
    if (expbuf_size(buf) < *l)
        return NULL;
    ret = buf->start;
    buf->start += *l;
    return ret;
}

static int expbuf_write(struct expbuf_t *buf, int fd)
{
   struct iovec vecs[2] = {};
   size_t bufsz = expbuf_size(buf);
   int vecindex;
   ssize_t r;

   vecs[0].iov_base = &bufsz;
   vecs[0].iov_len = sizeof(bufsz);
   vecs[1].iov_base = buf->start;
   vecs[1].iov_len = bufsz;

   for (vecindex = 0; vecindex != sizeof(vecs) / sizeof(vecs[0]);) {
       while ((r = writev(fd, vecs + vecindex, sizeof(vecs) / sizeof(vecs[0]) - vecindex)) == -1 && errno == EINTR)
           ;
       if (r == -1)
           return -1;
       assert(r != 0);
       while (r != 0 && r >= vecs[vecindex].iov_len) {
           r -= vecs[vecindex].iov_len;
           ++vecindex;
       }
       if (r != 0) {
           vecs[vecindex].iov_base += r;
           vecs[vecindex].iov_len -= r;
       }
   }

   return 0;
}

static int expbuf_read(struct expbuf_t *buf, int fd)
{
   size_t sz;

   if (read_nbytes(fd, &sz, sizeof(sz)) != 0)
       return -1;
   expbuf_reserve(buf, sz);
   if (read_nbytes(fd, buf->end, sz) != 0)
       return -1;
   buf->end += sz;
   return 0;
}

static void unlink_dir(const char *path)
{
   // DIR *dp;
   SGX_DIR_WRAPPER *dp;
   char buf[PATH_MAX];

   if ((dp = opendir(path)) != NULL) {
       struct dirent entbuf, *entp;
       while (readdir_r(dp, &entbuf, &entp) == 0 && entp != NULL) {
           if (strcmp(entp->d_name, ".") == 0 || strcmp(entp->d_name, "..") == 0)
               continue;
           snprintf(buf, PATH_MAX, "%s/%s", path, entp->d_name);
           unlink_dir(buf);
       }
       closedir(dp);
   }
   unlink(path);
   rmdir(path);
}


void dispose_thread_data(void *_thdata)
{
   struct st_neverbleed_thread_data_t *thdata = _thdata;
   assert(thdata->fd >= 0);
   close(thdata->fd);
   thdata->fd = -1;
}


struct st_neverbleed_thread_data_t *get_thread_data(neverbleed_t *nb)
{
   struct st_neverbleed_thread_data_t *thdata;
   pid_t self_pid = getpid();
   ssize_t r;

   if ((thdata = pthread_getspecific(nb->thread_key)) != NULL) {
       if (thdata->self_pid == self_pid)
           return thdata;
       /* we have been forked! */
       close(thdata->fd);
   } else {
       if ((thdata = malloc(sizeof(*thdata))) == NULL)
           dief("malloc failed");
   }

   thdata->self_pid = self_pid;
#ifdef SOCK_CLOEXEC
   if ((thdata->fd = socket(PF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0)) == -1)
       dief("socket(2) failed");
#else
   if ((thdata->fd = socket(PF_UNIX, SOCK_STREAM, 0)) == -1)
       dief("socket(2) failed");
   set_cloexec(thdata->fd);
#endif
   while (connect(thdata->fd, (void *)&nb->sun_, sizeof(nb->sun_)) != 0)
       if (errno != EINTR)
           dief("failed to connect to privsep daemon");
   while ((r = write(thdata->fd, nb->auth_token, sizeof(nb->auth_token))) == -1 && errno == EINTR)
       ;
   if (r != sizeof(nb->auth_token))
       dief("failed to send authentication token");
   pthread_setspecific(nb->thread_key, thdata);

   return thdata;
}

static void get_privsep_data(const RSA *rsa, struct st_neverbleed_rsa_exdata_t **exdata,
                            struct st_neverbleed_thread_data_t **thdata)
{
   *exdata = RSA_get_ex_data(rsa, 0);
   if (*exdata == NULL) {
       errno = 0;
       dief("invalid internal ref");
   }
   *thdata = get_thread_data((*exdata)->nb);
}

static struct {
   struct {
       pthread_mutex_t lock;
       size_t size;
       RSA **keys;
   } keys;
   neverbleed_t *nb;
} daemon_vars = {{PTHREAD_MUTEX_INITIALIZER}};



static RSA *daemon_get_rsa(size_t key_index)
{
   RSA *rsa;

   pthread_mutex_lock(&daemon_vars.keys.lock);
   rsa = daemon_vars.keys.keys[key_index];
   pthread_mutex_unlock(&daemon_vars.keys.lock);

   return rsa;
}


static size_t daemon_set_rsa(RSA *rsa)
{
   size_t index;

   pthread_mutex_lock(&daemon_vars.keys.lock);
   if ((daemon_vars.keys.keys = realloc(daemon_vars.keys.keys, sizeof(*daemon_vars.keys.keys) * (daemon_vars.keys.size + 1))) ==
       NULL)
       dief("no memory");
   index = daemon_vars.keys.size++;
   daemon_vars.keys.keys[index] = rsa;
   RSA_up_ref(rsa);
   pthread_mutex_unlock(&daemon_vars.keys.lock);

   return index;
}

static int priv_encdec_proxy(const char *cmd, int flen, const unsigned char *from, unsigned char *_to, RSA *rsa, int padding)
{
    struct st_neverbleed_rsa_exdata_t *exdata;
    struct st_neverbleed_thread_data_t *thdata;
    struct expbuf_t buf = {};
    size_t ret;
    unsigned char *to;
    size_t tolen;

   get_privsep_data(rsa, &exdata, &thdata);

    expbuf_push_str(&buf, cmd);
    expbuf_push_bytes(&buf, from, flen);
    expbuf_push_num(&buf, exdata->key_index);
    expbuf_push_num(&buf, padding);
   if (expbuf_write(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "write error" : "connection closed by daemon");
   expbuf_dispose(&buf);

   if (expbuf_read(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "read error" : "connection closed by daemon");
    if (expbuf_shift_num(&buf, &ret) != 0 || (to = expbuf_shift_bytes(&buf, &tolen)) == NULL) {
        errno = 0;
        dief("failed to parse response");
    }
    memcpy(_to, to, tolen);
   expbuf_dispose(&buf);

    return (int)ret;
}


static int priv_encdec_stub(const char *name,
                            int (*func)(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding),
                            struct expbuf_t *buf)
{
    printf("priv_encdec_stub \n");
    unsigned char *from, to[4096];
    size_t flen;
    size_t key_index, padding;
    RSA *rsa;
    int ret;

    if ((from = expbuf_shift_bytes(buf, &flen)) == NULL || expbuf_shift_num(buf, &key_index) != 0 ||
        expbuf_shift_num(buf, &padding) != 0) {
        errno = 0;
        warnf("%s: failed to parse request", name);
        return -1;
    }
   if ((rsa = daemon_get_rsa(key_index)) == NULL) {
        errno = 0;
        warnf("%s: invalid key index:%zu\n", name, key_index);
        return -1;
   }
    ret = func((int)flen, from, to, rsa, (int)padding);
    expbuf_dispose(buf);

    expbuf_push_num(buf, ret);
    expbuf_push_bytes(buf, to, ret > 0 ? ret : 0);

    return 0;
}

static int priv_enc_proxy(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding)
{
    return priv_encdec_proxy("priv_enc", flen, from, to, rsa, padding);
}

static int priv_enc_stub(struct expbuf_t *buf)
{
   return priv_encdec_stub(__FUNCTION__, RSA_private_encrypt, buf);
}

static int priv_dec_proxy(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding)
{
    return priv_encdec_proxy("priv_dec", flen, from, to, rsa, padding);
}

static int priv_dec_stub(struct expbuf_t *buf)
{
   return priv_encdec_stub(__FUNCTION__, RSA_private_decrypt, buf);
}


static int sign_proxy(int type, const unsigned char *m, unsigned int m_len, unsigned char *_sigret, unsigned *_siglen,
                      const RSA *rsa)
{
    struct st_neverbleed_rsa_exdata_t *exdata;
    struct st_neverbleed_thread_data_t *thdata;
    struct expbuf_t buf = {};
    size_t ret, siglen;
    unsigned char *sigret;

   get_privsep_data(rsa, &exdata, &thdata);

    expbuf_push_str(&buf, "sign");
    expbuf_push_num(&buf, type);
    expbuf_push_bytes(&buf, m, m_len);
    expbuf_push_num(&buf, exdata->key_index);
   if (expbuf_write(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "write error" : "connection closed by daemon");
   expbuf_dispose(&buf);

   if (expbuf_read(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "read error" : "connection closed by daemon");
    if (expbuf_shift_num(&buf, &ret) != 0 || (sigret = expbuf_shift_bytes(&buf, &siglen)) == NULL) {
        errno = 0;
        dief("failed to parse response");
    }
    memcpy(_sigret, sigret, siglen);
    *_siglen = (unsigned)siglen;
   expbuf_dispose(&buf);

    return (int)ret;
}

static int sign_stub(struct expbuf_t *buf)
{
    printf("Do this sign_stub \n");
    unsigned char *m, sigret[4096];
    size_t type, m_len, key_index;
    RSA *rsa;
    unsigned siglen = 0;
    int ret;

    if (expbuf_shift_num(buf, &type) != 0 || (m = expbuf_shift_bytes(buf, &m_len)) == NULL ||
        expbuf_shift_num(buf, &key_index) != 0) {
        errno = 0;
        warnf("%s: failed to parse request", __FUNCTION__);
        return -1;
    }
   if ((rsa = daemon_get_rsa(key_index)) == NULL) {
        errno = 0;
        warnf("%s: invalid key index:%zu", __FUNCTION__, key_index);
        return -1;
   }
   ret = RSA_sign((int)type, m, (unsigned)m_len, sigret, &siglen, rsa);
   expbuf_dispose(buf);

    expbuf_push_num(buf, ret);
    expbuf_push_bytes(buf, sigret, ret == 1 ? siglen : 0);

    return 0;
}


static EVP_PKEY *create_pkey(neverbleed_t *nb, size_t key_index, const char *ebuf, const char *nbuf)
{
    struct st_neverbleed_rsa_exdata_t *exdata;
    RSA *rsa;
    EVP_PKEY *pkey;

    if ((exdata = malloc(sizeof(*exdata))) == NULL) {
       fprintf(stderr, "no memory\n");
        abort();
    }
    exdata->nb = nb;
    exdata->key_index = key_index;

   rsa = RSA_new_method(nb->engine);
   RSA_set_ex_data(rsa, 0, exdata);
   if (BN_hex2bn(&rsa->e, ebuf) == 0) {
       fprintf(stderr, "failed to parse e:%s\n", ebuf);
        abort();
   }
   if (BN_hex2bn(&rsa->n, nbuf) == 0) {
       fprintf(stderr, "failed to parse n:%s\n", nbuf);
        abort();
   }
    rsa->flags |= RSA_FLAG_EXT_PKEY;

   pkey = EVP_PKEY_new();
   EVP_PKEY_set1_RSA(pkey, rsa);
   RSA_free(rsa);

    return pkey;
}


int neverbleed_load_private_key_file(neverbleed_t *nb, SSL_CTX *ctx, const char *fn, char *errbuf)
{
  printf("neverbleed_load_private_key_file \n");
   //  Fix me: hard code to use fixed private key
   //  struct st_neverbleed_thread_data_t *thdata = get_thread_data(nb);
   //  struct expbuf_t buf = {};
   //  size_t ret, key_index;
   //  char *estr, *nstr, *errstr;
   //  EVP_PKEY *pkey;

   //  expbuf_push_str(&buf, "load_key");
   //  expbuf_push_str(&buf, fn);
   // if (expbuf_write(&buf, thdata->fd) != 0)
   //      dief(errno != 0 ? "write error" : "connection closed by daemon");
   //  expbuf_dispose(&buf);

   // if (expbuf_read(&buf, thdata->fd) != 0)
   //      dief(errno != 0 ? "read error" : "connection closed by daemon");
   //  if (expbuf_shift_num(&buf, &ret) != 0 || expbuf_shift_num(&buf, &key_index) != 0 || (estr = expbuf_shift_str(&buf)) == NULL ||
   //      (nstr = expbuf_shift_str(&buf)) == NULL || (errstr = expbuf_shift_str(&buf)) == NULL) {
   //      errno = 0;
   //      dief("failed to parse response");
   //  }

   //  if (ret != 1) {
   //      snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "%s", errstr);
   //      return -1;
   //  }
    size_t ret = 1;

    // /* success */
    EVP_PKEY *my_priv_key = NULL;
    const unsigned char* priv_key_p = my_priv_key_arr;

    if(d2i_AutoPrivateKey(&my_priv_key, &priv_key_p, sizeof(my_priv_key_arr))==NULL)  {
        fprintf(stderr, "failed to convert priv key\n");
        return -1;        
    }

    if (SSL_CTX_use_PrivateKey(ctx, my_priv_key) != 1) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "SSL_CTX_use_PrivateKey failed");
        ret = -1;
    }
    EVP_PKEY_free(my_priv_key);
    // printf("done neverbleed_load_private_key_file %d\n", ret);
    return (int)ret;
    // return 1;
}

static int load_key_stub(struct expbuf_t *buf)
{
    char *fn;
    // FILE *fp = NULL;
   SGX_WRAPPER_FILE fp = NULL;
    RSA *rsa = NULL;
    size_t key_index = SIZE_MAX;
    char *estr = NULL, *nstr = NULL, errbuf[NEVERBLEED_ERRBUF_SIZE] = "";

    if ((fn = expbuf_shift_str(buf)) == NULL) {
        warnf("%s: failed to parse request", __FUNCTION__);
        return -1;
    }

   if ((fp = fopen(fn, "rt")) == NULL) {
        strerror_r(errno, errbuf, sizeof(errbuf));
        goto Respond;
   }
   if ((rsa = PEM_read_bio_RSAPrivateKey(fp, NULL, NULL, NULL)) == NULL) {
       // if ((rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL)) == NULL) {
        snprintf(errbuf, sizeof(errbuf), "failed to parse the private key");
        goto Respond;
   }
    key_index = daemon_set_rsa(rsa);
   estr = BN_bn2hex(rsa->e);
   nstr = BN_bn2hex(rsa->n);

Respond:
   expbuf_dispose(buf);
    expbuf_push_num(buf, rsa != NULL);
    expbuf_push_num(buf, key_index);
    expbuf_push_str(buf, estr != NULL ? estr : "");
    expbuf_push_str(buf, nstr != NULL ? nstr : "");
    expbuf_push_str(buf, errbuf);
    if (rsa != NULL)
       RSA_free(rsa);
    if (estr != NULL)
       OPENSSL_free(estr);
    if (nstr != NULL)
       OPENSSL_free(nstr);
    if (fp != NULL)
       fclose(fp);

    return 0;
}

int neverbleed_setuidgid(neverbleed_t *nb, const char *user, int change_socket_ownership)
{
    struct st_neverbleed_thread_data_t *thdata = get_thread_data(nb);
    struct expbuf_t buf = {};
    size_t ret;

    expbuf_push_str(&buf, "setuidgid");
    expbuf_push_str(&buf, user);
    expbuf_push_num(&buf, change_socket_ownership);
   if (expbuf_write(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "write error" : "connection closed by daemon");
    expbuf_dispose(&buf);

   if (expbuf_read(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "read error" : "connection closed by daemon");
    if (expbuf_shift_num(&buf, &ret) != 0) {
        errno = 0;
        dief("failed to parse response");
    }
   expbuf_dispose(&buf);

    return (int)ret;
}

static int setuidgid_stub(struct expbuf_t *buf)
{
   const char *user;
   size_t change_socket_ownership;
   struct passwd pwbuf, *pw;
   char pwstrbuf[65536]; /* should be large enough */
   int ret = -1;

   if ((user = expbuf_shift_str(buf)) == NULL || expbuf_shift_num(buf, &change_socket_ownership) != 0) {
       errno = 0;
       warnf("%s: failed to parse request", __FUNCTION__);
       return -1;
   }

   errno = 0;
   if (getpwnam_r(user, &pwbuf, pwstrbuf, sizeof(pwstrbuf), &pw) != 0) {
       warnf("%s: getpwnam_r failed", __FUNCTION__);
       goto Respond;
   }
   if (pw == NULL) {
       warnf("%s: failed to obtain information of user:%s", __FUNCTION__, user);
       goto Respond;
   }

   if (change_socket_ownership) {
       char *dir;
       if (chown(daemon_vars.nb->sun_.sun_path, pw->pw_uid, pw->pw_gid) != 0)
           dief("chown failed for:%s", daemon_vars.nb->sun_.sun_path);
       dir = dirname(daemon_vars.nb->sun_.sun_path);
       if (chown(dir, pw->pw_uid, pw->pw_gid) != 0)
           dief("chown failed for:%s", dir);
       free(dir);
   }

   /* setuidgid */
   if (setgid(pw->pw_gid) != 0) {
       warnf("%s: setgid(%d) failed", __FUNCTION__, (int)pw->pw_gid);
       goto Respond;
   }
   if (initgroups(pw->pw_name, pw->pw_gid) != 0) {
       warnf("%s: initgroups(%s, %d) failed", __FUNCTION__, pw->pw_name, (int)pw->pw_gid);
       goto Respond;
   }
   if (setuid(pw->pw_uid) != 0) {
       warnf("%s: setuid(%d) failed\n", __FUNCTION__, (int)pw->pw_uid);
       goto Respond;
   }
   ret = 0;

Respond:
   expbuf_dispose(buf);
   expbuf_push_num(buf, ret);
   return 0;
}


__attribute__((noreturn)) static void *daemon_close_notify_thread(void *_close_notify_fd)
{
    int close_notify_fd = (int)((char *)_close_notify_fd - (char *)NULL);
    char b;
    ssize_t r;
    printf("Do daemon_close_notify_thread : %d\n", close_notify_fd);
Redo:
   r = read(close_notify_fd, &b, 1);
    if (r == -1 && errno == EINTR)
        goto Redo;
    if (r > 0)
        goto Redo;
    /* close or error */

    /* unlink the temporary directory and socket file */
   unlink_dir(dirname(daemon_vars.nb->sun_.sun_path));

   _exit(0);
}

static void *daemon_conn_thread(void *_sock_fd)
{
    int sock_fd = (int)((char *)_sock_fd - (char *)NULL);
    struct expbuf_t buf = {};
    unsigned char auth_token[NEVERBLEED_AUTH_TOKEN_SIZE];

    printf("Call daemon_conn_thread %d \n", sock_fd);
    /* authenticate */
   if (read_nbytes(sock_fd, &auth_token, sizeof(auth_token)) != 0) {
        warnf("failed to receive authencication token from client");
        goto Exit;
   }
   if (memcmp(auth_token, daemon_vars.nb->auth_token, NEVERBLEED_AUTH_TOKEN_SIZE) != 0) {
        warnf("client authentication failed");
        goto Exit;
   }

    while (1) {
        char *cmd;
        if (expbuf_read(&buf, sock_fd) != 0) {
            if (errno != 0)
                warnf("read error");
            break;
        }
        if ((cmd = expbuf_shift_str(&buf)) == NULL) {
            errno = 0;
            warnf("failed to parse request");
            break;
        }
        if (strcmp(cmd, "priv_enc") == 0) {
            if (priv_enc_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "priv_dec") == 0) {
            if (priv_dec_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "sign") == 0) {
            if (sign_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "load_key") == 0) {
            if (load_key_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "setuidgid") == 0) {
            if (setuidgid_stub(&buf) != 0)
                break;
        } else {
            warnf("unknown command:%s", cmd);
            break;
        }
        if (expbuf_write(&buf, sock_fd) != 0) {
            warnf(errno != 0 ? "write error" : "connection closed by client");
            break;
        }
       expbuf_dispose(&buf);
    }

Exit:
   expbuf_dispose(&buf);
   close(sock_fd);

    return NULL;
}

static void *daemon_accept_thread(void *_listen_fd)
{
   pthread_t tid;
   int listen_fd = (int)((char *)_listen_fd - (char *)NULL);
   int sock_fd;
   while (1) {
       while ((sock_fd = accept(listen_fd, NULL, NULL)) == -1)
           ;
       if (pthread_create(&tid, PTHREAD_ATTRIBUTE_NULL, daemon_conn_thread, (char *)NULL + sock_fd) != 0)
           dief("pthread_create failed");
   }
}


// __attribute__((noreturn)) static void daemon_main(int listen_fd, int close_notify_fd, const char *tempdir)
static void daemon_main(int listen_fd, int close_notify_fd, const char *tempdir)
{
   pthread_t tid;
   SGX_WRAPPER_PTHREAD_ATTRIBUTE thattr;
   int sock_fd;

   // { /* close all descriptors (except STDIN, STDOUT, STRERR, listen_fd, close_notify_fd) */
   //     int fd = (int)sysconf(_SC_OPEN_MAX) - 1;
   //     for (; fd > 2; --fd) {
   //         if (fd == listen_fd || fd == close_notify_fd)
   //             continue;
   //         close(fd);
   //     }
   // }

   pthread_attr_init(&thattr);
   pthread_attr_setdetachstate(thattr, 1);

   // Fix me: same process, so no notify need to close at all
   // if (pthread_create(&tid, PTHREAD_ATTRIBUTE_NULL, daemon_close_notify_thread, (char *)NULL + close_notify_fd) != 0)
   //     dief("pthread_create failed");

   // while (1) {
   //     while ((sock_fd = accept(listen_fd, NULL, NULL)) == -1)
   //         ;
   //     if (pthread_create(&tid, PTHREAD_ATTRIBUTE_NULL, daemon_conn_thread, (char *)NULL + sock_fd) != 0)
   //         dief("pthread_create failed");
   // }

   if (pthread_create(&tid, thattr, daemon_accept_thread, (char *)NULL + listen_fd) != 0)
       dief("pthread_create failed");

}


static RSA_METHOD rsa_method = {
    "privsep RSA method", /* name */
    NULL,                 /* rsa_pub_enc */
    NULL,                 /* rsa_pub_dec */
    priv_enc_proxy,       /* rsa_priv_enc */
    priv_dec_proxy,       /* rsa_priv_dec */
    NULL,                 /* rsa_mod_exp */
    NULL,                 /* bn_mod_exp */
    NULL,                 /* init */
    NULL,                 /* finish */
    RSA_FLAG_SIGN_VER,    /* flags */
    NULL,                 /* app data */
    sign_proxy,           /* rsa_sign */
    NULL,                 /* rsa_verify */
    NULL                  /* rsa_keygen */
};

int neverbleed_init(neverbleed_t *nb, char *errbuf)
{
   int pipe_fds[2] = {-1, -1}, listen_fd = -1;
   char *tempdir = NULL;
   int value = 0;

   const RSA_METHOD *default_method = RSA_PKCS1_SSLeay();
   rsa_method.rsa_pub_enc = default_method->rsa_pub_enc;
   rsa_method.rsa_pub_dec = default_method->rsa_pub_dec;
   rsa_method.rsa_verify = default_method->rsa_verify;

   /* setup the daemon */
   if (pipe(pipe_fds) != 0) {
       snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "pipe(2) failed:%s", strerror(errno));
       goto Fail;
   }
   set_cloexec(pipe_fds[1]);
   if ((tempdir = strdup("/tmp/openssl-privsep.XXXXXX")) == NULL) {
       snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "no memory");
       goto Fail;
   }
   if (mkdtemp(tempdir) == NULL) {
       snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "failed to create temporary directory under /tmp:%s", strerror(errno));
       goto Fail;
   }
   memset(&nb->sun_, 0, sizeof(nb->sun_));
   nb->sun_.sun_family = AF_UNIX;
   snprintf(nb->sun_.sun_path, sizeof(nb->sun_.sun_path), "%s/_", tempdir);
    // printf("\n%s\n", nb->sun_.sun_path);
    // printf("Pointer is: %p", &nb->sun_);
    // printf("Size of the pointer: %d", sizeof(nb->sun_));
   RAND_bytes(nb->auth_token, sizeof(nb->auth_token));
   if ((listen_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
       snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "socket(2) failed:%s", strerror(errno));
       goto Fail;
   }
   
   if (bind(listen_fd, (struct sockaddr *)&(nb->sun_), sizeof(nb->sun_)) != 0) {
       snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "failed to bind to %s:%s", nb->sun_.sun_path, strerror(errno));
       goto Fail;
   }
   if (listen(listen_fd, SOMAXCONN) != 0) {
       snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "listen(2) failed:%s", strerror(errno));
       goto Fail;
   }

   // nb->daemon_pid = fork();
   nb->daemon_pid = getpid();
   switch (nb->daemon_pid) {
   case -1:
       snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "fork(2) failed:%s", strerror(errno));
       goto Fail;
   case 0:
       close(pipe_fds[1]);
// #ifdef __linux__
//        prctl(PR_SET_DUMPABLE, 0, 0, 0, 0);
// #endif
       daemon_vars.nb = nb;
       daemon_main(listen_fd, pipe_fds[0], tempdir);
       break;
   default:
        // This is added for the single process code
//        daemon_vars.nb = nb;
       daemon_main(listen_fd, pipe_fds[0], tempdir);
       break;
   }

   // close(listen_fd);
   listen_fd = -1;
   close(pipe_fds[0]);
   pipe_fds[0] = -1;

   /* setup engine */
   if ((nb->engine = ENGINE_new()) == NULL || !ENGINE_set_id(nb->engine, "neverbleed") ||
       !ENGINE_set_name(nb->engine, "privilege separation software engine") || !ENGINE_set_RSA(nb->engine, &rsa_method)) {
       snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "failed to initialize the OpenSSL engine");
       goto Fail;
   }
   ENGINE_add(nb->engine);

   /* setup thread key */
   pthread_key_create(&nb->thread_key, dispose_thread_data);

   free(tempdir);
   return 0;
Fail:
   printf("Fail because : %s \n", errbuf);
   if (pipe_fds[0] != -1)
       close(pipe_fds[0]);
   if (pipe_fds[1] != -1)
       close(pipe_fds[1]);
   if (tempdir != NULL) {
       unlink_dir(tempdir);
       free(tempdir);
   }
   if (listen_fd != -1)
       close(listen_fd);
   if (nb->engine != NULL) {
       ENGINE_free(nb->engine);
       nb->engine = NULL;
   }
   return -1;
}

static void setup_ecc_key(SSL_CTX *ssl_ctx)
{
    int nid = NID_X9_62_prime256v1;
    EC_KEY *key = EC_KEY_new_by_curve_name(nid);
    if (key == NULL) {
        fprintf(stderr, "Failed to create curve \"%s\"\n", OBJ_nid2sn(nid));
        return;
    }
    SSL_CTX_set_tmp_ecdh(ssl_ctx, key);
    EC_KEY_free(key);
}

int dumb_https_server(unsigned short port, SSL_CTX *ctx)
{
    printf("Do dumb_https_server \n");
    int listen_fd, reuse_flag;
    struct sockaddr_in sin = {};

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "failed to create socket:%s\n", strerror(errno));
        return 111;
    }
    reuse_flag = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_flag, sizeof(reuse_flag));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(0x7f000001);
    sin.sin_port = htons(8888);
    if (bind(listen_fd, (void *)&sin, sizeof(sin)) != 0) {
        fprintf(stderr, "bind failed:%s\n", strerror(errno));
        return 111;
    }
    if (listen(listen_fd, SOMAXCONN) != 0) {
        fprintf(stderr, "listen failed:%s\n", strerror(errno));
        return 111;
    }

    while (1) {
        int conn_fd;
        SSL *ssl;
        char buf[4096];
        /* accept connection */
        struct sockaddr addr;
        socklen_t len;
        while ((conn_fd = accept(listen_fd, &addr, &len)) == -1 && errno == EINTR)
            ;
        if (conn_fd == -1) {
            fprintf(stderr, "accept(2) failed:%s\n", strerror(errno));
            return 111;
        }
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, conn_fd);
        if (SSL_accept(ssl) == 1) {
            SSL_read(ssl, buf, sizeof(buf));
            const char *resp = "HTTP/1.0 200 OK\r\nContent-Length: 6\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nhello\n";
            SSL_write(ssl, resp, strlen(resp));
            SSL_shutdown(ssl);
        } else {
            fprintf(stderr, "SSL_accept failed\n");
        }
        SSL_free(ssl);
        close(conn_fd);
    }
}

int ecall_main_neverbleedtest(int argc, char **argv)
{
    unsigned short port;
    SSL_CTX *ctx;
    neverbleed_t nb;
    char errbuf[NEVERBLEED_ERRBUF_SIZE];
    int use_privsep;

    /* initialization */
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    if (neverbleed_init(&nb, errbuf) != 0) {
        fprintf(stderr, "openssl_privsep_init: %s\n", errbuf);
        return 111;
    }
    ctx = SSL_CTX_new(SSLv23_server_method());
    SSL_CTX_set_options(ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_COMPRESSION);
    setup_ecc_key(ctx);

    printf("Init neverbleed and SSL context and option \n");

    /* parse args */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <internal|privsep> <port>\n", argv[0]);
        return 111;
    }
    if (strcmp(argv[1], "internal") == 0) {
        use_privsep = 0;
    } else if (strcmp(argv[1], "privsep") == 0) {
        use_privsep = 1;
    } else {
        fprintf(stderr, "unknown mode:%s\n", argv[1]);
        return 111;
    }
    const char* port_string = strdup(argv[2]);
    if (sscanf(port_string, "%hu", &port) != 1) {
        printf("The argv2 is : %s\n", argv[2]);
        fprintf(stderr, "failed to parse port:%s\n", argv[2]);
        return 111;
    }
    
    const unsigned char* cert_p = my_cert_array;
    if(d2i_X509(&my_cert, &cert_p, sizeof(my_cert_array))==NULL) {
        fprintf(stderr, "failed to load certificate array:%s\n", argv[3]);
        return 111;      
    }

    if (SSL_CTX_use_certificate(ctx, my_cert) != 1) {
        fprintf(stderr, "failed to load certificate chain file:%s\n", argv[3]);
        return 111;
    }

    EVP_PKEY *my_priv_key = NULL;
    const unsigned char* priv_key_p = my_priv_key_arr;

    if(d2i_AutoPrivateKey(&my_priv_key, &priv_key_p, sizeof(my_priv_key_arr))==NULL)  {
        fprintf(stderr, "failed to convert priv key\n");
        return 111;        
    }

    if (use_privsep) {
        if (neverbleed_load_private_key_file(&nb, ctx, argv[4], errbuf) != 1) {
            fprintf(stderr, "failed to load private key from file:%s:%s\n", argv[4], errbuf);
            return 111;
        }
    } else {
      printf("SSL_CTX_use_PrivateKey_file \n");
       // if (SSL_CTX_use_PrivateKey_ASN1(ctx, argv[4], SSL_FILETYPE_PEM) != 1) {
       //     fprintf(stderr, "failed to load private key from file:%s\n", argv[4]);
       //     return 111;
       // }
       if (SSL_CTX_use_PrivateKey(ctx, my_priv_key) != 1) {
           fprintf(stderr, "failed to load private key from file:%s\n", argv[4]);
           return 111;
       }
    }

    /* start the httpd */
    return dumb_https_server(port, ctx);
}