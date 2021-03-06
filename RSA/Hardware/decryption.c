#include <8051.h>
#define SIZE 128

enum {ins_idle, ins_write_data, ins_montgomery_exp, ins_read_r, ins_ack};

volatile __xdata __at (0x4101) unsigned char rmodm[SIZE] = {0xA3,0x10,0x6B,0x83,0x7C,0x40,0xBF,0xB2,0x54,0x28,0x20,0x4D,0xB2,0xD4,0xF8,0xA6,0xE5,0xB7,0x51,0xBA,0xE8,0xD1,0x95,0x9A,0xFE,0xAB,0x0A,0x48,0x23,0xA2,0x70,0xB3,0xCC,0x7B,0x8F,0x44,0xF4,0x5B,0x53,0x78,0x7D,0xE2,0xF2,0xAF,0xD2,0xBA,0x06,0x0F,0xEE,0xA4,0x37,0x06,0xE7,0x04,0x2C,0x90,0x3C,0x8B,0xFD,0x54,0xCD,0xB9,0x94,0xAD,0x64,0x8E,0x26,0xDE,0x8C,0xC5,0x33,0x92,0x24,0xEF,0x76,0x34,0xC4,0xB8,0xEC,0xF1,0x9A,0x79,0x61,0x80,0xC1,0xBC,0x6D,0x03,0x49,0x95,0x94,0xC8,0x6F,0x14,0xB0,0x16,0x14,0x63,0xD0,0x94,0xD9,0x10,0x4B,0x44,0x03,0xC2,0xCC,0x04,0x68,0x98,0x6C,0xD9,0x69,0xC7,0x1A,0x0F,0xC5,0x39,0x5C,0x6A,0x5A,0x67,0x0B,0x47,0xF4,0x77,0x1E,0x2B};
volatile __xdata __at (0x4081) unsigned char r2modm[SIZE] = {0x4B,0x61,0xD1,0xA8,0x05,0x36,0xB5,0xE7,0xC6,0x6A,0x09,0x48,0xE1,0x09,0x9A,0x62,0x6C,0xCC,0xB9,0x82,0x01,0x88,0xED,0x37,0xC7,0xDD,0xEB,0x8C,0xC1,0xF2,0x96,0x83,0x19,0x5E,0xD1,0x3F,0xF6,0x80,0x15,0xBB,0xAC,0x60,0x27,0x80,0x83,0x3C,0x25,0x9B,0xF1,0x89,0xE3,0x78,0x10,0x3D,0x53,0x21,0x16,0x4A,0xA3,0x0C,0xAD,0x64,0xD2,0x50,0xC2,0x10,0x48,0x87,0xDA,0xC2,0xEB,0xF1,0xFC,0x8F,0xFF,0xE5,0xCA,0x4D,0xA9,0x68,0xCD,0x3A,0x7B,0x41,0x83,0x53,0x5E,0xBB,0x44,0x8D,0x9A,0x34,0x86,0xB3,0x62,0x7F,0x9D,0x96,0xB0,0xAC,0xB1,0x30,0xCD,0x25,0x60,0xB0,0x42,0xC3,0xE7,0xB0,0xED,0xDA,0xB9,0x11,0x7D,0x2C,0x27,0xF6,0x8C,0xD8,0xAA,0x3B,0xE7,0x4F,0x86,0x1F,0x96,0x2E};
volatile __xdata __at (0x4201) unsigned char modulus[SIZE] = {0x5D,0xEF,0x94,0x7C,0x83,0xBF,0x40,0x4D,0xAB,0xD7,0xDF,0xB2,0x4D,0x2B,0x07,0x59,0x1A,0x48,0xAE,0x45,0x17,0x2E,0x6A,0x65,0x01,0x54,0xF5,0xB7,0xDC,0x5D,0x8F,0x4C,0x33,0x84,0x70,0xBB,0x0B,0xA4,0xAC,0x87,0x82,0x1D,0x0D,0x50,0x2D,0x45,0xF9,0xF0,0x11,0x5B,0xC8,0xF9,0x18,0xFB,0xD3,0x6F,0xC3,0x74,0x02,0xAB,0x32,0x46,0x6B,0x52,0x9B,0x71,0xD9,0x21,0x73,0x3A,0xCC,0x6D,0xDB,0x10,0x89,0xCB,0x3B,0x47,0x13,0x0E,0x65,0x86,0x9E,0x7F,0x3E,0x43,0x92,0xFC,0xB6,0x6A,0x6B,0x37,0x90,0xEB,0x4F,0xE9,0xEB,0x9C,0x2F,0x6B,0x26,0xEF,0xB4,0xBB,0xFC,0x3D,0x33,0xFB,0x97,0x67,0x93,0x26,0x96,0x38,0xE5,0xF0,0x3A,0xC6,0xA3,0x95,0xA5,0x98,0xF4,0xB8,0x0B,0x88,0xE1,0xD4};
volatile __xdata __at (0x4000) unsigned char message[SIZE+1] = {0xcb,0xd0,0x7a,0xfc,0x21,0x61,0x42,0x14,0x1f,0xf0,0x50,0x6b,0x46,0x15,0x8d,0x8f,0xb2,0x3b,0xeb,0xdd,0xa7,0xdc,0x0c,0x2c,0x6d,0x31,0x99,0xf9,0xc1,0xc6,0x7e,0xec,0xfe,0x13,0xae,0x24,0x61,0x91,0xb0,0xf6,0x69,0xed,0x03,0x06,0x8b,0xd1,0x7c,0x29,0x5b,0x5d,0x5c,0xad,0xb9,0xa4,0x24,0x6e,0x3a,0x34,0xf9,0xb8,0xe7,0x10,0x97,0x82,0x96,0xa5,0xce,0x2b,0x80,0x83,0x3e,0x75,0x56,0xa4,0x3e,0x3e,0xdb,0xdd,0xb0,0xdb,0xef,0x10,0x35,0x6c,0xb8,0xab,0xa4,0xe9,0x1c,0xb0,0xf5,0xb9,0xf1,0x3e,0x2b,0x0a,0xf3,0xdf,0x02,0x87,0xaf,0xa8,0xb3,0x37,0x03,0x7c,0xc1,0xc5,0x71,0x76,0x72,0x1d,0x82,0x98,0xa9,0x3e,0xc3,0xe2,0xad,0x1a,0x4e,0x43,0x79,0x7a,0xc3,0xbe,0x8a,0x6e};
volatile __xdata __at (0x4181) unsigned char dec_exp[SIZE] = {0xA1,0x80,0x48,0x28,0xC3,0xFE,0x04,0xB3,0xF2,0xEF,0xAF,0x3E,0x55,0x46,0x4E,0xC8,0x47,0x7A,0x1C,0x83,0x74,0xD7,0x11,0xD1,0xFB,0x16,0x44,0x72,0x8C,0x4B,0xD5,0xFD,0xB9,0xFA,0x04,0xE1,0x3E,0x3A,0x16,0x04,0x55,0x41,0xD0,0x8A,0x92,0x38,0xF4,0xD4,0xAE,0x7A,0x60,0xE2,0x69,0xAA,0xA6,0x63,0xA1,0xEB,0x05,0x71,0x99,0x71,0xE3,0x67,0x2A,0x57,0xF7,0x6B,0x82,0xB3,0xF0,0x82,0x58,0x54,0xAF,0xC3,0xD1,0xEF,0x68,0x7E,0x88,0xBD,0x39,0x2B,0x2A,0x7C,0x14,0xF8,0xC7,0xD0,0xF9,0x64,0x9A,0xBA,0x6F,0x45,0x28,0x5D,0xD7,0xE2,0xC4,0x8E,0x9F,0x6F,0xA8,0x88,0xAD,0xFD,0x28,0x92,0x4F,0x63,0x41,0x70,0x22,0xAD,0xAB,0x4E,0x1D,0x63,0x89,0xCC,0x09,0x42,0xFE,0xBC,0xCF,0x3A};

volatile __xdata __at (0x5000) unsigned char r[SIZE+1];

unsigned short i;

void write_data() {
    P1 = 0;

    P0 = ins_write_data;
    P0 = ins_idle;

    while (P1 == 0) {}
    P0 = ins_ack;
}

void read_r() {
    P0 = ins_read_r;
    while (P1 == 0) {}
    P0 = ins_ack;

    P0 = ins_idle;
}

void montgomery_exp() {
    P0 = ins_montgomery_exp;
    P0 = ins_idle;
}

void terminate() {
    P3 = 0x55;
}

int main() {
    write_data();
    montgomery_exp();
    read_r();

    terminate();
    return 0;
}
