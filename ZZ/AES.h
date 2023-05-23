#pragma once
#pragma once
#include <string.h>
#include <stdio.h>

static const struct aes128 {
	unsigned char key[16], txt[16], out[16];
} cases[] = {
	{{ 0x00, 0x01, 0x20, 0x01, 0x71, 0x01, 0x98, 0xae, 0xda, 0x79, 0x17, 0x14, 0x60, 0x15, 0x35, 0x94 },
	{ 0x00, 0x01, 0x00, 0x01, 0x01, 0xa1, 0x98, 0xaf, 0xda, 0x78, 0x17, 0x34, 0x86, 0x15, 0x35 ,0x66 },
	{ 0x6c, 0xdd, 0x59, 0x6b, 0x8f, 0x56, 0x42, 0xcb, 0xd2, 0x3b, 0x47, 0x98, 0x1a, 0x65, 0x42, 0x2a } },
	{{ 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c },
	{ 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 },
	{ 0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32 } }
};
static const struct aes192 {
	unsigned char txt[16], key[24], out[16];
} cases1[] = {
	{{ 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0 },
	{ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 },
	{ 0x9c, 0xa4, 0x7e, 0xff, 0x6f, 0xd2, 0x88, 0x0b, 0x74, 0x22, 0x63, 0x49, 0x6d, 0x1c, 0x3d, 0x3e } },
}; 
static const struct aes256 {
	unsigned char txt[16], key[32], out[16];
} cases2[] = {
	{{ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
	{ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f  },
	{ 0x5a, 0x6e, 0x04, 0x57, 0x08, 0xfb, 0x71, 0x96, 0xf0, 0x2e, 0x55, 0x3d, 0x02, 0xc3, 0xa6, 0x92 } },
	
};
class AES
{
public:
	AES() {};
	AES(const unsigned char key[], int keyBytes);
	virtual ~AES() {};
	void encrypt(const unsigned char data[16], unsigned char out[16]);
	void decrypt(const unsigned char data[16], unsigned char out[16]);
	int mNb;
	int mNk;
	int mNr;
	unsigned char mKey[32];
	unsigned char mW[60][4];
	static unsigned char S_Box[];
	static unsigned char inv_S_Box[];
	static unsigned char rcon[];
	void Sub_Bytes(unsigned char state[][4]);
	void Shift_Rows(unsigned char state[][4]);
	void Mix_Columns(unsigned char state[][4]);
	void Add_RoundKey(unsigned char state[][4], int k);
	void Inv_SubBytes(unsigned char state[][4]);
	void Inv_ShiftRows(unsigned char state[][4]);
	void Inv_MixColumns(unsigned char state[][4]);
	void Key_Expansion();
	unsigned char GF28_Multi(unsigned char s, unsigned char a);
	void Rot_Word(unsigned char w[]);
	void Sub_Word(unsigned char w[]);
	int compare(unsigned char data[16], unsigned char temp[16]);
};