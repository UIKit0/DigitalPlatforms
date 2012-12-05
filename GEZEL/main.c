// Result at 0200:0280
// Should be 2C2BBB0280627C28795DDC726CFAB231C7E47FB3BC7937CB0CE8B54E103A0FFB809428DA0E96078C12B3CB2E8F081EAB9A33862F6CA12B077F3913A6FE007C2F64AD9D9136B86499E74E2CCB030E2DF745B89AE9D20C7B9887B921198AAC8D079ACB241DE56161A6B01988FC9BEB8053FA0179AA40A3C85BA1525E56BEC08C05
// With wordlength of 2¹ 4A53783F8F862AC5DABFAD9C7379ABC2F3287B4971DE45754BF31B27BF0FD77DECE2B39F1B4EFA7E8CBB87780C33B4183599FEBFD02A16DD82FE6D6B0D24649F901657C072FF18302A15BCF7A5DF000CBB1E2043B2D357AA8278EF51D1683DF291E5620EF516E93A37261A6B5EC577C46AADC7DAB7A84D111FC08AA8A6AEFC1Df

#include <8051.h>
#define SIZE 128

enum {ins_idle, ins_write_data, ins_montgomery, ins_read_r, ins_ack};

volatile __xdata __at (0x0000) unsigned char m[SIZE] = {0x0D,0xD5,0x0F,0x26,0x8F,0x95,0xAD,0x59,0x24,0xA0,0xDA,0x8F,0xAE,0x27,0x9F,0xD4,0x7A,0xE7,0x7E,0xBF,0xDF,0x2D,0x12,0xDA,0x43,0x14,0x0F,0x20,0xFA,0x90,0x46,0xD5,0x39,0xF1,0xAA,0x90,0x02,0xE4,0xDC,0xA3,0x9C,0xA4,0xF2,0xFF,0x30,0xC1,0x14,0x22,0x7E,0x11,0xE3,0x77,0x00,0x1A,0xAD,0x50,0xE1,0x7B,0x91,0x4A,0x92,0x08,0x65,0x20,0x75,0x68,0x74,0xB3,0x65,0xB0,0x0C,0xC6,0x8B,0xC9,0x10,0xEF,0xC4,0x4E,0x45,0xAD,0xFA,0xD2,0x4F,0x06,0xEC,0x29,0x5C,0xF3,0xAA,0x97,0x82,0x70,0xB8,0x44,0x06,0x86,0xE0,0x67,0xFC,0x70,0x79,0xA4,0xF0,0xB3,0x0B,0x48,0xCD,0xF0,0x6C,0x6F,0x0B,0x8B,0x25,0x67,0x46,0x8F,0xEC,0xA4,0xC1,0xE3,0x6A,0x47,0x0D,0xEB,0xA3,0x81,0xB5,0xBA};
volatile __xdata __at (0x0080) unsigned char a[SIZE] = {0xA3,0x71,0x79,0x01,0xFC,0xF2,0x93,0xC7,0x1C,0x69,0x2D,0x67,0x38,0x2B,0x7C,0x1A,0x40,0x88,0xBA,0x9B,0x10,0x53,0x65,0xED,0xFE,0x39,0xB4,0x77,0x3B,0xC8,0x9B,0xB2,0xE4,0xB1,0xA3,0xC9,0xCD,0xC8,0xF2,0x69,0x01,0x91,0x87,0x67,0xAC,0x6E,0x56,0xF1,0x60,0xBF,0x1E,0x0F,0x53,0xA8,0xAF,0x40,0xDB,0x76,0xB2,0xEA,0x90,0xDD,0xFF,0x40,0x0C,0xD2,0x4D,0xDC,0x5E,0xB3,0xE7,0xFA,0xB4,0x53,0x5E,0x75,0x0B,0x91,0x92,0x14,0x7E,0xD8,0xB8,0xA7,0x05,0x95,0xD0,0x55,0x97,0x30,0x78,0x41,0x81,0xEF,0xC6,0x64,0x9F,0x4A,0x9C,0x4A,0x3A,0x0B,0xCA,0xD8,0x9C,0x1A,0x64,0xA7,0xA9,0x6E,0xC8,0x0A,0xE5,0xCE,0xE2,0x3B,0x73,0x8A,0xEF,0xF0,0xE4,0xA6,0x40,0x26,0xF3,0xD9,0x50,0x1F};
volatile __xdata __at (0x0100) unsigned char b[SIZE] = {0x08,0xA2,0x1A,0xDB,0xCB,0x27,0x58,0x66,0x6C,0xC0,0xA2,0x58,0x7E,0x96,0x9D,0x15,0xAD,0x00,0xF5,0xAD,0xBD,0xC6,0x62,0xDE,0xB3,0xC9,0xF9,0x5C,0xB8,0xC8,0x3A,0xD1,0x2A,0xCE,0x1C,0xFA,0x3F,0x88,0x60,0xC6,0xFA,0x04,0xC9,0x08,0x68,0xB5,0x2F,0x01,0x88,0x67,0xDC,0xFA,0xD2,0xF3,0x3E,0xF6,0x80,0x97,0xA0,0x7F,0x9D,0x98,0x4D,0x1B,0x20,0xEA,0xAE,0x9A,0xF8,0x5C,0x53,0x71,0xC4,0x4C,0xBD,0xDA,0xBB,0x4F,0x03,0x14,0x30,0xE4,0x94,0x72,0x49,0xAF,0x02,0xFF,0x68,0x73,0xED,0x8B,0x46,0xCF,0xD0,0x89,0xA7,0xB5,0x64,0x76,0xC2,0xBD,0x68,0xD3,0xAC,0x0F,0xD1,0x80,0xE8,0x3E,0x02,0x27,0x82,0xB3,0xEA,0x8E,0x32,0x7A,0xD0,0xE9,0x9C,0x59,0x68,0x81,0x0F,0x3C,0x9E,0xBA};

volatile __xdata __at (0x0200) unsigned char r[SIZE+1];

volatile __xdata __at (0x4000) unsigned char shared_a[SIZE];
volatile __xdata __at (0x4080) unsigned char shared_b[SIZE];
volatile __xdata __at (0x4100) unsigned char shared_m[SIZE];

unsigned short i;

void write_montgomery() {
    P1 = 0;
    
    for (i = 0; i < SIZE; i++) {
        shared_a[i] = a[SIZE-1-i];
    }

	for (i = 0; i < SIZE; i++) {
        shared_b[i] = b[SIZE-1-i];
    }

	for (i = 0; i < SIZE; i++) {
        shared_m[i] = m[SIZE-1-i];
    }

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

void montgomery() {
    P0 = ins_montgomery;
    P0 = ins_idle;
}

void terminate() {
    P3 = 0x55;
}

int main() {
    write_montgomery();
    montgomery();
    read_r();
    
    P1 = 0;

    for (i = 0; i < SIZE; i++) {
        shared_a[i] = r[i];
    }

    P0 = ins_write_data;
    P0 = ins_idle;

    while (P1 == 0) {}
	P0 = ins_ack;

    terminate();
    return 0;
}
