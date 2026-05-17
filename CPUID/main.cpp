#include "CPUID.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <intrin.h>

using namespace std;

// Pad a number with zeros to make it 8 characters long, return the padded hex string
string ZeroPadNumber(int num, int zeros) {
	std::stringstream ss;
	// Convert integer to string
	ss << std::hex << num;
	std::string paddedString;
	// Get the string from stringstream
	ss >> paddedString;

	int stringLlength = paddedString.length();
	for (int i = 0; i < zeros - stringLlength; i++)
	{
		paddedString = "0" + paddedString;
	}
	return paddedString;
}

string GetCacheType(unsigned int cacheType)
{
	string type;
	switch (cacheType)
	{
		case 0:
			type = "No more caches";
			break;
		case 1:
			type = "Data Cache";
			break;
		case 2:
			type = "Instruction Cache";
			break;
		case 3:
			type = "Unified Cache";
			break;
		default:
			// 4 - 31 are reserved
			type = "Reserved";
			break;
	}
	return type;
}

string getCacheAndTableDescriptor(unsigned int descriptor)
{
	string description;

	switch (descriptor)
	{
		case 0x00:
			description = "Other information: null descriptor";
			break;
		case 0x01:
			description = "Instruction TLB: 4 KByte pages, 4-way set associative, 32 entries";
			break;
		case 0x02:
			description = "Instruction TLB: 2 MByte pages, fully associative, 2 entries";
			break;
		case 0x03:
			description = "Data TLB: 4 KByte pages, 4-way set associative, 64 entries";
			break;
		case 0x04:
			description = "Data TLB: 4 MByte pages, 4-way set associative, 8 entries";
			break;
		case 0x05:
			description = "Data TLB: 4 MByte pages, fully associative, 32 entries";
			break;
		case 0x06:
			description = "Level-1 instruction cache: 8 KBytes, 4-way set associative, 32 byte line size";
			break;
		case 0x08:
			description = "Level-1 instruction cache: 16 KBytes, 4-way set associative, 32 byte line size";
			break;
		case 0x09:
			description = "Level-1 instruction cache: 32 KBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x0A:
			description = "Level-1 data cache: 8 KBytes, 2-way set associative, 32 byte line size";
			break;
		case 0x0B:
			description = "Instruction TLB: 4 MByte pages, fully associative, 4 entries";
			break;
		case 0x0C:
			description = "Level-1 data cache: 16 KBytes, 4-way set associative, 32 byte line size";
			break;
		case 0x0D:
			description = "Level-1 data cache: 16 KBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x0E:
			description = "Level-1 data cache: 24 KBytes, 6-way set associative, 64 byte line size";
			break;
		case 0x0F:
			description = "Reserved";
			break;
		case 0x11:
			description = "Level-1 data cache: 16 KBytes, 4-way set associative, 32 byte line size";
			break;
		case 0x12:
		case 0x13:
		case 0x14:
			description = "Reserved";
			break;
		case 0x15:
			description = "Level-1 instruction cache: 16 KBytes, 2-way set associative, 32 byte line size";
			break;
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
			description = "Reserved";
			break;
		case 0x1A:
			description = "Level-2 cache: 96 KBytes, 6-way set associative, 64 byte line size";
			break;
		case 0x1B:
		case 0x1C:
			description = "Reserved";
			break;
		case 0x1D:
			description = "Level-2 cache: 128 KBytes, 2-way set associative, 64 byte line size";
			break;
		case 0x1E:
		case 0x1F:
		case 0x20:
			description = "Reserved";
			break;
		case 0x21:
			description = "Level-2 cache: 256 KBytes, 8-way set associative, 64 byte line size";
			break;
		case 0x22:
			description = "Level-3 cache: 512 KBytes, 4-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x23:
			description = "Level-3 cache: 1 MByte, 8-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x24:
			description = "Level-2 cache: 1 MByte, 16-way set associative, 64 byte line size";
			break;
		case 0x25:
			description = "Level-3 cache: 2 MBytes, 8-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x26:
		case 0x27:
		case 0x28:
			description = "(128-byte prefetch), Unused in any known CPU.";
			break;
		case 0x29:
			description = "Level-3 cache: 4 MBytes, 8-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x2A:
		case 0x2B:
			description = "Reserved";
			break;
		case 0x2C:
			description = "Level-1 data cache: 32 KBytes, 8-way set associative, 64 byte line size";
			break;
		case 0x2D:
		case 0x2E:
		case 0x2F:
			description = "Reserved";
			break;
		case 0x30:
			description = "Level-1 instruction cache: 32 KBytes, 8-way set associative, 64 byte line size";
			break;
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
		case 0x35:
		case 0x36:
		case 0x37:
		case 0x38:
			description = "Reserved";
			break;
		case 0x39:
			description = "Level-2 cache: 128 KBytes, 4-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x3A:
			description = "Level-2 cache: 192 KBytes, 6-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x3B:
			description = "Level-2 cache: 128 KBytes, 2-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x3C:
			description = "Level-2 cache: 256 KBytes, 4-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x3D:
			description = "Level-2 cache: 384 KBytes, 6-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x3E:
			description = "Level-2 cache: 512 KBytes, 4-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x3F:
			description = "Level-2 cache: 256 KBytes, 2-way set associative, 64 byte line size";
			break;
		case 0x40:
			description = "Other information: no L3 cache present";
			break;
		case 0x41:
			description = "Level-2 cache: 128 KBytes, 4-way set associative, 32 byte line size";
			break;
		case 0x42:
			description = "Level-2 cache: 256 KBytes, 4-way set associative, 32 byte line size";
			break;
		case 0x43:
			description = "Level-2 cache: 512 KBytes, 4-way set associative, 32 byte line size";
			break;
		case 0x44:
			description = "Level-2 cache: 1 MByte, 4-way set associative, 32 byte line size";
			break;
		case 0x45:
			description = "Level-2 cache: 2 MBytes, 4-way set associative, 32 byte line size";
			break;
		case 0x46:
			description = "Level-3 cache: 4 MBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x47:
			description = "Level-3 cache: 8 MBytes, 8-way set associative, 64 byte line size";
			break;
		case 0x48:
			description = "Level-2 cache: 3 MBytes, 12-way set associative, 64 byte line size";
			break;
		case 0x49:
			description = "Level-2/Level-3 cache: 4 MBytes, 16-way set associative, 64 byte line size";
			break;
		case 0x4A:
			description = "Level-3 cache: 6 MBytes, 12-way set associative, 64 byte line size";
			break;
		case 0x4B:
			description = "Level-3 cache: 8 MBytes, 16-way set associative, 64 byte line size";
			break;
		case 0x4C:
			description = "Level-3 cache: 12 MBytes, 12-way set associative, 64 byte line size";
			break;
		case 0x4D:
			description = "Level-3 cache: 16 MBytes, 16-way set associative, 64 byte line size";
			break;
		case 0x4E:
			description = "Level-2 cache: 6 MBytes, 24-way set associative, 64 byte line size";
			break;
		case 0x4F:
			description = "Instruction TLB: 4 KByte pages, 32 entries";
			break;
		case 0x50:
			description = "Instruction TLB: 4 KByte/2 MByte/4 MByte pages, fully associative, 64 entries";
			break;
		case 0x51:
			description = "Instruction TLB: 4 KByte/2 MByte/4 MByte pages, fully associative, 128 entries";
			break;
		case 0x52:
			description = "Instruction TLB: 4 KByte/2 MByte/4 MByte pages, fully associative, 256 entries";
			break;
		case 0x53:
		case 0x54:
			description = "Reserved";
			break;
		case 0x55:
			description = "Instruction TLB: 2 MByte/4 MByte pages, fully associative, 7 entries";
			break;
		case 0x56:
			description = "Data TLB: 4 MByte pages, 4-way set associative, 16 entries";
			break;
		case 0x57:
			description = "Data TLB: 4 KByte pages, 4-way set associative, 16 entries";
			break;
		case 0x58:
			description = "Reserved";
			break;
		case 0x59:
			description = "Data TLB: 4 KByte pages, fully associative, 16 entries";
			break;
		case 0x5A:
			description = "Data TLB: 2 MByte/4 MByte pages, 4-way set associative, 32 entries";
			break;
		case 0x5B:
			description = "Data TLB: 4 KByte/4 MByte pages, fully associative, 64 entries";
			break;
		case 0x5C:
			description = "Data TLB: 4 KByte/4 MByte pages, fully associative, 128 entries";
			break;
		case 0x5D:
			description = "Data TLB: 4 KByte/4 MByte pages, fully associative, 256 entries";
			break;
		case 0x5E:
		case 0x5F:
			description = "Reserved";
			break;
		case 0x60:
			description = "Level-1 data cache: 16 KBytes, 8-way set associative, 64 byte line size";
			break;
		case 0x61:
			description = "Instruction TLB: 4 KByte pages, fully associative, 48 entries";
			break;
		case 0x62:
			description = "Reserved";
			break;
		case 0x63:
			description = "2 Data TLBs: Table 1: 2 MByte/4 MByte pages, 4-way set associative, 4 entries and Table 2: 1 GByte pages, fully associative, 32 entries";
			break;
		case 0x64:
			description = "Data TLB: 4 KByte pages, 4-way set associative, 512 entries";
			break;
		case 0x65:
			description = "Reserved";
			break;
		case 0x66:
			description = "Level-1 data cache: 8 KBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x67:
			description = "Level-1 data cache: 16 KBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x68:
			description = "Level-1 data cache: 32 KBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x69:
			description = "Reserved";
			break;
		case 0x6A:
			description = "Data TLB: 4 KByte pages, 8-way set associative, 64 entries";
			break;
		case 0x6B:
			description = "Data TLB: 4 KByte pages, 8-way set associative, 256 entries";
			break;
		case 0x6C:
			description = "Data TLB: 2 MByte/4 MByte pages, 8-way set associative, 128 entries";
			break;
		case 0x6D:
			description = "Data TLB: 1 GByte pages, fully associative, 16 entries";
			break;
		case 0x6E:
		case 0x6F:
			description = "Reserved";
			break;
		case 0x70:
			description = "Trace cache: 12 K-μop, 8-way set associative";
			break;
		case 0x71:
			description = "Trace cache: 16 K-μop, 8-way set associative";
			break;
		case 0x72:
			description = "Trace cache: 32 K-μop, 8-way set associative";
			break;
		case 0x73:
			description = "Trace cache: 64 K-μop, 8-way set associative";
			break;
		case 0x74:
		case 0x75:
			description = "Reserved";
			break;
		case 0x76:
			description = "Instruction TLB: 2 MByte/4 MByte pages, fully associative, 8 entries";
			break;
		case 0x77:
			description = "Level-1 instruction cache: 16 KBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x78:
			description = "Level-2 cache: 1 MByte, 4-way set associative, 64 byte line size";
			break;
		case 0x79:
			description = "Level-2 cache: 128 KBytes, 8-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x7A:
			description = "Level-2 cache: 256 KBytes, 8-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x7B:
			description = "Level-2 cache: 512 KBytes, 8-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x7C:
			description = "Level-2 cache: 1 MByte, 8-way set associative, 64 byte line size, cache uses sectors of 2 cache-lines each";
			break;
		case 0x7D:
			description = "Level-2 cache: 2 MBytes, 8-way set associative, 64 byte line size";
			break;
		case 0x7E:
			description = "Level-2 cache: 256 KBytes, 8-way set associative, 128 byte line size";
			break;
		case 0x7F:
			description = "Level-2 cache: 512 KBytes, 2-way set associative, 64 byte line size";
			break;
		case 0x80:
			description = "Level-2 cache: 512 KBytes, 8-way set associative, 64 byte line size";
			break;
		case 0x81:
			description = "Level-2 cache: 128 KBytes, 8-way set associative, 32 byte line size";
			break;
		case 0x82:
			description = "Level-2 cache: 256 KBytes, 8-way set associative, 32 byte line size";
			break;
		case 0x83:
			description = "Level-2 cache: 512 KBytes, 8-way set associative, 32 byte line size";
			break;
		case 0x84:
			description = "Level-2 cache: 1 MByte, 8-way set associative, 32 byte line size";
			break;
		case 0x85:
			description = "Level-2 cache: 2 MBytes, 8-way set associative, 32 byte line size";
			break;
		case 0x86:
			description = "Level-2 cache: 512 KBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x87:
			description = "Level-2 cache: 1 MByte, 8-way set associative, 64 byte line size";
			break;
		case 0x88:
			description = "Level-3 cache: 2 MBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x89:
			description = "Level-3 cache: 4 MBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x8A:
			description = "Level-3 cache: 8 MBytes, 4-way set associative, 64 byte line size";
			break;
		case 0x8B:
		case 0x8C:
			description = "Reserved";
			break;
		case 0x8D:
			description = "Level-3 cache: 3 MBytes, 12-way set associative, 128 byte line size";
			break;
		case 0x8E:
		case 0x8F:
			description = "Reserved";
			break;
		case 0x90:
			description = "Instruction TLB: 4 KByte - 256 MByte pages, fully associative, 64 entries";
			break;
		case 0x91:
		case 0x92:
		case 0x93:
		case 0x94:
		case 0x95:
			description = "Reserved";
			break;
		case 0x96:
			description = "Data TLB: 4 KByte - 256 MByte pages, fully associative, 32 entries";
			break;
		case 0x97:
		case 0x98:
		case 0x99:
		case 0x9A:
			description = "Reserved";
			break;
		case 0x9B:
			description = "Data TLB: 4 KByte - 256 MByte pages, fully associative, 96 entries";
			break;
		case 0x9C:
		case 0x9D:
		case 0x9E:
		case 0x9F:
			description = "Reserved";
			break;
		case 0xA0:
			description = "Data TLB: 4 KByte pages, fully associative, 32 entries";
			break;
		case 0xA1:
		case 0xA2:
		case 0xA3:
		case 0xA4:
		case 0xA5:
		case 0xA6:
		case 0xA7:
		case 0xA8:
		case 0xA9:
		case 0xAA:
		case 0xAB:
		case 0xAC:
		case 0xAD:
		case 0xAE:
		case 0xAF:
			description = "Reserved";
			break;
		case 0xB0:
			description = "Instruction TLB: 4 KByte pages, 4-way set associative, 128 entries";
			break;
		case 0xB1:
			description = "Instruction TLB: 2 MByte / 4 MByte pages, 4-way set associative, 8 entries";
			break;
		case 0xB2:
			description = "Instruction TLB: 4 MByte pages, 4-way set associative, 64 entries";
			break;
		case 0xB3:
			description = "Data TLB: 4 KByte pages, 4-way set associative, 128 entries";
			break;
		case 0xB4:
			description = "Data TLB: 4 KByte pages, 4-way set associative, 256 entries";
			break;
		case 0xB5:
			description = "Instruction TLB: 4 KByte pages, 8-way set associative, 64 entries";
			break;
		case 0xB6:
			description = "Instruction TLB: 4 KByte pages, 8-way set associative, 128 entries";
			break;
		case 0xB7:
		case 0xB8:
		case 0xB9:
			description = "Reserved";
			break;
		case 0xBA:
			description = "Data TLB: 4 KByte pages, 4-way set associative, 64 entries";
			break;
		case 0xBB:
		case 0xBC:
		case 0xBD:
		case 0xBE:
		case 0xBF:
			description = "Reserved";
			break;
		case 0xC0:
			description = "Data TLB: 4 KByte / 4 MByte pages, 4-way set associative, 8 entries";
			break;
		case 0xC1:
			description = "Level-2 shared TLB: 4 KByte / 2 MByte pages, 8-way set associative, 1024 entries";
			break;
		case 0xC2:
			description = "Data TLB: 2 MByte / 4 MByte pages, 4-way set associative, 16 entries";
			break;
		case 0xC3:
			description = "Two Level-2 shared TLBs: Table 1: 4 KByte / 2 MByte pages, 6-way set associative, 1536 entries and Table 2: 1 GByte pages, 4-way set associative, 16 entries";
			break;
		case 0xC4:
			description = "Data TLB: 2 MByte / 4 MByte pages, 4-way set associative, 32 entries";
			break;
		case 0xC5:
		case 0xC6:
		case 0xC7:
		case 0xC8:
		case 0xC9:
			description = "Reserved";
			break;
		case 0xCA:
			description = "Level-2 shared TLB: 4 KByte pages, 4-way set associative, 512 entries";
			break;
		case 0xCB:
		case 0xCC:
		case 0xCD:
		case 0xCE:
		case 0xCF:
			description = "Reserved";
			break;
		case 0xD0:
			description = "Level-3 cache: 512 KBytes, 4-way set associative, 64 byte line size";
			break;
		case 0xD1:
			description = "Level-3 cache: 1 MByte, 4-way set associative, 64 byte line size";
			break;
		case 0xD2:
			description = "Level-3 cache: 2 MBytes, 4-way set associative, 64 byte line size";
			break;
		case 0xD3:
		case 0xD4:
		case 0xD5:
			description = "Reserved";
			break;
		case 0xD6:
			description = "Level-3 cache: 1 MByte, 8-way set associative, 64 byte line size";
			break;
		case 0xD7:
			description = "Level-3 cache: 2 MBytes, 8-way set associative, 64 byte line size";
			break;
		case 0xD8:
			description = "Level-3 cache: 4 MBytes, 8-way set associative, 64 byte line size";
			break;
		case 0xD9:
		case 0xDA:
		case 0xDB:
			description = "Reserved";
			break;
		case 0xDC:
			description = "Level-3 cache: 1.5 MBytes, 12-way set associative, 64 byte line size";
			break;
		case 0xDD:
			description = "Level-3 cache: 3 MBytes, 12-way set associative, 64 byte line size";
			break;
		case 0xDE:
			description = "Level-3 cache: 6 MBytes, 12-way set associative, 64 byte line size";
			break;
		case 0xDF:
		case 0xE0:
		case 0xE1:
			description = "Reserved";
			break;
		case 0xE2:
			description = "Level-3 cache: 2 MBytes, 16-way set associative, 64 byte line size";
			break;
		case 0xE3:
			description = "Level-3 cache: 4 MBytes, 16-way set associative, 64 byte line size";
			break;
		case 0xE4:
			description = "Level-3 cache: 8 MBytes, 16-way set associative, 64 byte line size";
			break;
		case 0xE5:
		case 0xE6:
		case 0xE7:
		case 0xE8:
		case 0xE9:
			description = "Reserved";
			break;
		case 0xEA:
			description = "Level-3 cache: 12 MBytes, 24-way set associative, 64 byte line size";
			break;
		case 0xEB:
			description = "Level-3 cache: 18 MBytes, 24-way set associative, 64 byte line size";
			break;
		case 0xEC:
			description = "Level-3 cache: 24 MBytes, 24-way set associative, 64 byte line size";
			break;
		case 0xED:
		case 0xEE:
		case 0xEF:
			description = "Reserved";
			break;
		case 0xF0:
			description = "Other information: 64-byte prefetch";
			break;
		case 0xF1:
			description = "Other information: 128-byte prefetch";
			break;
		case 0xF2:
		case 0xF3:
		case 0xF4:
		case 0xF5:
		case 0xF6:
		case 0xF7:
		case 0xF8:
		case 0xF9:
		case 0xFA:
		case 0xFB:
		case 0xFC:
		case 0xFD:
			description = "Reserved";
			break;
		case 0xFE:
			description = "Other information: Leaf 2 has no TLB info, use leaf 18h";
			break;
		case 0xFF:
			description = "Other information: Leaf 2 has no cache info, use leaf 4";
			break;
		default:
			description = "Unknown descriptor";
			break;
	}

	return description;
}

unsigned int extractBits(unsigned int num,
	                     unsigned int pos,
	                     unsigned int k)
{
	// Right shift 'num' by 'pos' bits
	unsigned int shifted = num >> pos;

	// Create a mask with 'k' bits set to 1
	unsigned int mask = (1 << k) - 1;

	// Apply the mask to the shifted number
	return shifted & mask;
}

int main(int argc, char* argv[]) {
	int cpuInfo[4];
	__cpuidex(cpuInfo, 0x0, 0); // Get CPU vendor

	string vendor;
	vendor += string((const char*)&cpuInfo[1], 4);
	vendor += string((const char*)&cpuInfo[3], 4);
	vendor += string((const char*)&cpuInfo[2], 4);

	std::cout << "EAX=0: Manufacturer ID: EBX = " << std::hex << "0x" << cpuInfo[1] << " " << string((const char*)&cpuInfo[1], 4) << endl;
	std::cout << "EAX=0: Manufacturer ID: EDX = " << std::hex << "0x" << cpuInfo[3] << " " << string((const char*)&cpuInfo[3], 4) << endl;
	std::cout << "EAX=0: Manufacturer ID: ECX = " << std::hex << "0x" << cpuInfo[2] << " " << string((const char*)&cpuInfo[2], 4) << endl;
	std::cout << "EAX=0: Highest Function Parameter: EAX = " << std::hex << "0x" << cpuInfo[0] << endl;
	std::cout << "CPU vendor = " << vendor << endl;
	std::cout << endl;


	__cpuidex(cpuInfo, 0x1, 0);
	bitset<32> eaxBits = bitset<32>(cpuInfo[0]);
	bitset<32> ebxBits = bitset<32>(cpuInfo[1]);
	bitset<32> ecxBits = bitset<32>(cpuInfo[2]);
	bitset<32> edxBits = bitset<32>(cpuInfo[3]);

	bitset<32> eaxBits1 = eaxBits;
	
	std::cout << "EAX=0x1: Processor Version Information [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x1: Additional Information [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x1: Feature Bits [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x1: Feature Bits [EDX] = " << edxBits << endl;

	std::cout << "EAX=0x1: Stepping ID: EAX Bits 3:0 = " << std::hex << "0x" << extractBits(cpuInfo[0], 0, 4) << endl;

	unsigned int modelId = extractBits(cpuInfo[0], 4, 4);
	unsigned int familyId = extractBits(cpuInfo[0], 8, 4);
	unsigned int extendedModelId = extractBits(cpuInfo[0], 16, 4);

	std::cout << "EAX=0x1: Family ID: EAX Bits 8:11 = " << std::hex << "0x" << familyId << endl;
	std::cout << "EAX=0x1: Model: EAX Bits 4:7 = " << std::hex << "0x" << modelId << endl;
	if (familyId == 0x6 || familyId == 0xF)
	{
		unsigned int extendedModelIdLeftShifted = extendedModelId << 4;
		unsigned int processorModel = modelId + extendedModelIdLeftShifted;
		std::cout << "Extended Model ID left-shifted by 4 bits: " << std::hex << "0x" << extendedModelIdLeftShifted << endl;
		std::cout << "EAX=0x1: Actual Model: Model (EAX Bits 4:7) + (Extended Model Id (EAX Bits 16:19) << 4)  = " << std::hex << "0x" << processorModel << endl;
	}

	std::cout << "EAX=0x1: Processor Type: EAX Bits 12:13 = " << std::hex << "0x" << extractBits(cpuInfo[0], 12, 2) << endl;
	std::cout << "EAX=0x1: Reserved: EAX Bits 14:15 = " << std::hex << "0x" << extractBits(cpuInfo[0], 14, 2) << endl;
	std::cout << "EAX=0x1: Extended Model ID: EAX Bits 16:19 = " << std::hex << "0x" << extendedModelId << endl;
	std::cout << "EAX=0x1: Extended Family ID: EAX Bits 20:27 = " << std::hex << "0x" << extractBits(cpuInfo[0], 20, 8) << endl;
	std::cout << "EAX=0x1: Reserved: EAX Bits 28:31 = " << std::hex << "0x" << extractBits(cpuInfo[0], 28, 4) << endl;
	std::cout << endl;



	std::cout << "EAX=0x1: [EBX Additional Information]" << endl;
	std::cout << "EBX bits 7:0 Brand Index = " << std::hex << "0x" << extractBits(cpuInfo[0], 0, 8) << endl;
	std::cout << "EBX bits 15:8 CLFLUSH line size (Value * 8 = cache line size in bytes) = " << std::hex << "0x" << extractBits(cpuInfo[0], 8, 8) << endl;
	std::cout << "EBX bits 23:16 Maximum number of addressable IDs for logical processors in this physical package = " << std::hex << "0x" << extractBits(cpuInfo[0], 16, 8) << endl;
	std::cout << "EBX bits 31:24 Local APIC ID: The initial APIC-ID is used to identify the executing logical processor = " << std::hex << "0x" << extractBits(cpuInfo[0], 24, 8) << endl;
	std::cout << endl;



	std::cout << "EAX=0x1: [ECX feature bits]" << endl;
	(ecxBits[0]) ? std::cout << "ECX bit 0: " << ecxBits[0] << ": [SUPPORTED] SSE3 (Prescott New Instructions - PNI) - (SSE3)" << endl : std::cout << "ECX bit 0: " << ecxBits[0] << ": [UNSUPPORTED] SSE3 (Prescott New Instructions - PNI) - (SSE3)" << endl;
	(ecxBits[1]) ? std::cout << "ECX bit 1: " << ecxBits[1] << ": [SUPPORTED] PCLMULQDQ (carry-less multiply) instruction - (PCLMULQDQ)" << endl : std::cout << "ECX bit 1: " << ecxBits[1] << ": [UNSUPPORTED] PCLMULQDQ (carry-less multiply) instruction - (PCLMULQDQ)" << endl;
	(ecxBits[2]) ? std::cout << "ECX bit 2: " << ecxBits[2] << ": [SUPPORTED] 64-bit debug store (edx bit 21) - (DTES64)" << endl : std::cout << "ECX bit 2: " << ecxBits[2] << ": [UNSUPPORTED] 64-bit debug store (edx bit 21) - (DTES64)" << endl;
	(ecxBits[3]) ? std::cout << "ECX bit 3: " << ecxBits[3] << ": [SUPPORTED] MONITOR and MWAIT instructions (PNI) - (MONITOR)" << endl : std::cout << "ECX bit 3: " << ecxBits[3] << ": [UNSUPPORTED] MONITOR and MWAIT instructions (PNI) - (MONITOR)" << endl;
	(ecxBits[4]) ? std::cout << "ECX bit 4: " << ecxBits[4] << ": [SUPPORTED] CPL qualified debug store - (DS-CPL)" << endl : std::cout << "ECX bit 4: " << ecxBits[4] << ": [UNSUPPORTED] CPL qualified debug store - (DS-CPL)" << endl;
	(ecxBits[5]) ? std::cout << "ECX bit 5: " << ecxBits[5] << ": [SUPPORTED] Virtual Machine eXtensions - (VMX)" << endl : std::cout << "ECX bit 5: " << ecxBits[5] << ": [UNSUPPORTED] Virtual Machine eXtensions - (VMX)" << endl;
	(ecxBits[6]) ? std::cout << "ECX bit 6: " << ecxBits[6] << ": [SUPPORTED] Safer Mode Extensions (LaGrande) (GETSEC instruction) - (SMX)" << endl : std::cout << "ECX bit 6: " << ecxBits[6] << ": [UNSUPPORTED] Safer Mode Extensions (LaGrande) (GETSEC instruction) - (SMX)" << endl;
	(ecxBits[7]) ? std::cout << "ECX bit 7: " << ecxBits[7] << ": [SUPPORTED] Enhanced SpeedStep - (EST)" << endl : std::cout << "ECX bit 7: " << ecxBits[7] << ": [UNSUPPORTED] Enhanced SpeedStep - (EST)" << endl;
	(ecxBits[8]) ? std::cout << "ECX bit 8: " << ecxBits[8] << ": [SUPPORTED] Thermal Monitor 2 - (TM2)" << endl : std::cout << "ECX bit 8: " << ecxBits[8] << ": [UNSUPPORTED] Thermal Monitor 2 - (TM2)" << endl;
	(ecxBits[9]) ? std::cout << "ECX bit 9: " << ecxBits[9] << ": [SUPPORTED] Supplemental SSE3 instructions - (SSSE3)" << endl : std::cout << "ECX bit 9: " << ecxBits[9] << ": [UNSUPPORTED] Supplemental SSE3 instructions - (SSSE3)" << endl;
	(ecxBits[10]) ? std::cout << "ECX bit 10: " << ecxBits[10] << ": [SUPPORTED] L1 Context ID - (CNXT-ID)" << endl : std::cout << "ECX bit 10: " << ecxBits[10] << ": [UNSUPPORTED] L1 Context ID - (CNXT-ID)" << endl;
	(ecxBits[11]) ? std::cout << "ECX bit 11: " << ecxBits[11] << ": [SUPPORTED] Silicon Debug interface - (SDBG)" << endl : std::cout << "ECX bit 11: " << ecxBits[11] << ": [UNSUPPORTED] Silicon Debug interface - (SDBG)" << endl;
	(ecxBits[12]) ? std::cout << "ECX bit 12: " << ecxBits[12] << ": [SUPPORTED] Fused multiply-add (FMA3) - (FMA)" << endl : std::cout << "ECX bit 12: " << ecxBits[12] << ": [UNSUPPORTED] Fused multiply-add (FMA3) - (FMA)" << endl;
	(ecxBits[13]) ? std::cout << "ECX bit 13: " << ecxBits[13]<< ": [SUPPORTED] CMPXCHG16B instruction - (CMPXCHG16B)"<< endl : std::cout<< "ECX bit 13: "<< ecxBits[13]<< ": [UNSUPPORTED] CMPXCHG16B instruction - (CMPXCHG16B)"<< endl;
	(ecxBits[14]) ? std::cout<< "ECX bit 14: "<< ecxBits[14]<< ": [SUPPORTED] Can disable sending task priority messages - (xTPR Update Control)"<< endl : std::cout<< "ECX bit 14: "<< ecxBits[14]<< ": [UNSUPPORTED] Can disable sending task priority messages - (xTPR Update Control)"<< endl;
	(ecxBits[15]) ? std::cout<< "ECX bit 15: "<< ecxBits[15]<< ": [SUPPORTED] Perfmon & debug capability - (PDCM)"<< endl : std::cout<< "ECX bit 15: "<< ecxBits[15]<< ": [UNSUPPORTED] Perfmon & debug capability - (PDCM)"<< endl;
	(ecxBits[16]) ? std::cout << "ECX bit 16: " << ecxBits[16] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 16: " << ecxBits[16] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[17]) ? std::cout << "ECX bit 17: " << ecxBits[17] << ": [SUPPORTED] Process context identifiers (CR4 bit 17) - (PCID)" << endl : std::cout << "ECX bit 17: " << ecxBits[17] << ": [UNSUPPORTED] Process context identifiers (CR4 bit 17) - (PCID)" << endl;
	(ecxBits[18]) ? std::cout << "ECX bit 18: " << ecxBits[18] << ": [SUPPORTED] Direct cache access for DMA writes - (DCA)" << endl : std::cout << "ECX bit 18: " << ecxBits[18] << ": [UNSUPPORTED] Direct cache access for DMA writes - (DCA)" << endl;
	(ecxBits[19]) ? std::cout << "ECX bit 19: " << ecxBits[19] << ": [SUPPORTED] SSE4.1 instructions - (SSE4.1)" << endl : std::cout << "ECX bit 19: " << ecxBits[19] << ": [UNSUPPORTED] SSE4.1 instructions - (SSE4.1)" << endl;
	(ecxBits[20]) ? std::cout << "ECX bit 20: " << ecxBits[20] << ": [SUPPORTED] SSE4.2 instructions - (SSE4.2)" << endl : std::cout << "ECX bit 20: " << ecxBits[20] << ": [UNSUPPORTED] SSE4.2 instructions - (SSE4.2)" << endl;
	(ecxBits[21]) ? std::cout << "ECX bit 21: " << ecxBits[21] << ": [SUPPORTED] x2APIC (enhanced APIC) - (X2APIC)" << endl : std::cout << "ECX bit 21: " << ecxBits[21] << ": [UNSUPPORTED] x2APIC (enhanced APIC) - (X2APIC)" << endl;
	(ecxBits[22]) ? std::cout << "ECX bit 22: " << ecxBits[22] << ": [SUPPORTED] MOVBE instruction (big-endian) - (MOVBE)" << endl : std::cout << "ECX bit 22: " << ecxBits[22] << ": [UNSUPPORTED] MOVBE instruction (big-endian) - (MOVBE)" << endl;
	(ecxBits[23]) ? std::cout << "ECX bit 23: " << ecxBits[23] << ": [SUPPORTED] POPCNT instruction - (POPCNT)" << endl : std::cout << "ECX bit 23: " << ecxBits[23] << ": [UNSUPPORTED] POPCNT instruction - (POPCNT)" << endl;
	(ecxBits[24]) ? std::cout << "ECX bit 24: " << ecxBits[24] << ": [SUPPORTED] APIC implements one-shot operation using a TSC deadline value - (TSC-Deadline)" << endl : std::cout << "ECX bit 24: " << ecxBits[24] << ": [UNSUPPORTED] APIC implements one-shot operation using a TSC deadline value - (TSC-Deadline)" << endl;
	(ecxBits[25]) ? std::cout << "ECX bit 25: " << ecxBits[25] << ": [SUPPORTED] AES instruction set - (AES-NI)" << endl : std::cout << "ECX bit 25: " << ecxBits[25] << ": [UNSUPPORTED] AES instruction set - (AES-NI)" << endl;
	(ecxBits[26]) ? std::cout << "ECX bit 26: " << ecxBits[26] << ": [SUPPORTED] Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions - (XSAVE)" << endl : std::cout << "ECX bit 26: " << ecxBits[26] << ": [UNSUPPORTED] Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions - (XSAVE)" << endl;
	(ecxBits[27]) ? std::cout << "ECX bit 27: " << ecxBits[27] << ": [SUPPORTED] XSAVE enabled by OS - (OSXSAVE)" << endl : std::cout << "ECX bit 27: " << ecxBits[27] << ": [UNSUPPORTED] XSAVE enabled by OS - (OSXSAVE)" << endl;
	(ecxBits[28]) ? std::cout<< "ECX bit 28: "<< ecxBits[28]<< ": [SUPPORTED] Advanced Vector Extensions (256-bit SIMD) - (AVX)"<< endl : std::cout<< "ECX bit 28: "<< ecxBits[28]<< ": [UNSUPPORTED] Advanced Vector Extensions (256-bit SIMD) - (AVX)"<< endl;
	(ecxBits[29]) ? std::cout<< "ECX bit 29: "<< ecxBits[29]<< ": [SUPPORTED] Floating-point conversion instructions to/from FP16 format - (F16C)"<< endl : std::cout<< "ECX bit 29: "<< ecxBits[29]<< ": [UNSUPPORTED] Floating-point conversion instructions to/from FP16 format - (F16C)"<< endl;
	(ecxBits[30]) ? std::cout<< "ECX bit 30: "<< ecxBits[30]<< ": [SUPPORTED] RDRAND (on-chip random number generator) feature - (RDRAND)"<< endl : std::cout<< "ECX bit 30: "<< ecxBits[30]<< ": [UNSUPPORTED] RDRAND (on-chip random number generator) feature - (RDRAND)"<< endl;
	(ecxBits[31]) ? std::cout<< "ECX bit 31: "<< ecxBits[31]<< ": [SUPPORTED] Hypervisor present (always zero on physical CPUs) - (Hypervisor)"<< endl : std::cout<< "ECX bit 31: "<< ecxBits[31]<< ": [UNSUPPORTED] Hypervisor present (always zero on physical CPUs) - (Hypervisor)"<< endl;
	std::cout << endl;

	std::cout << "EAX=0x1: [EDX feature bits]" << endl;
	//cout << "EDX bit 0 = " << std::hex << "0x" << edxBits[0] << endl;
	(edxBits[0]) ? std::cout << "EDX bit 0: " << edxBits[0] << ": [SUPPORTED] Onboard x87 FPU - (FPU)" << endl : std::cout << "EDX bit 0: " << edxBits[0] << ": [UNSUPPORTED] Onboard x87 FPU - (FPU)" << endl;
	(edxBits[1]) ? std::cout << "EDX bit 1: " << edxBits[1] << ": [SUPPORTED] Virtual 8086 mode extensions (such as VIF, VIP, PVI) - (VME)" << endl : std::cout << "EDX bit 1: " << edxBits[1] << ": [UNSUPPORTED] Virtual 8086 mode extensions (such as VIF, VIP, PVI) - (VME)" << endl;
	(edxBits[2]) ? std::cout << "EDX bit 2: " << edxBits[2] << ": [SUPPORTED] Debugging extensions (CR4 bit 3) - (DE)" << endl : std::cout << "EDX bit 2: " << edxBits[2] << ": [UNSUPPORTED] Debugging extensions (CR4 bit 3) - (DE)" << endl;
	(edxBits[3]) ? std::cout << "EDX bit 3: " << edxBits[3] << ": [SUPPORTED] Page Size Extension (4 MB pages) - (PSE)" << endl : std::cout << "EDX bit 3: " << edxBits[3] << ": [UNSUPPORTED] Page Size Extension (4 MB pages) - (PSE)" << endl;
	(edxBits[4]) ? std::cout << "EDX bit 4: " << edxBits[4] << ": [SUPPORTED] Time Stamp Counter and RDTSC instruction - (TSC)" << endl : std::cout << "EDX bit 4: " << edxBits[4] << ": [UNSUPPORTED] Time Stamp Counter and RDTSC instruction - (TSC)" << endl;
	(edxBits[5]) ? std::cout << "EDX bit 5: " << edxBits[5] << ": [SUPPORTED] Model-specific registers and RDMSR/WRMSR instructions  - (MSR)" << endl : std::cout << "EDX bit 5: " << edxBits[5] << ": [UNSUPPORTED] Model-specific registers and RDMSR/WRMSR instructions  - (MSR)" << endl;
	(edxBits[6]) ? std::cout << "EDX bit 6: " << edxBits[6] << ": [SUPPORTED] Physical Address Extension - (PAE)" << endl : std::cout << "EDX bit 6: " << edxBits[6] << ": [UNSUPPORTED] Physical Address Extension - (PAE)" << endl;
	(edxBits[7]) ? std::cout << "EDX bit 7: " << edxBits[7] << ": [SUPPORTED] Machine Check Exception - (MCE)" << endl : std::cout << "EDX bit 7: " << edxBits[7] << ": [UNSUPPORTED] Machine Check Exception - (MCE)" << endl;
	(edxBits[8]) ? std::cout << "EDX bit 8: " << edxBits[8] << ": [SUPPORTED] CMPXCHG8B (compare-and-swap) instruction  - (CX8)" << endl : std::cout << "EDX bit 8: " << edxBits[8] << ": [UNSUPPORTED] CMPXCHG8B (compare-and-swap) instruction  - (CX8)" << endl;
	(edxBits[9]) ? std::cout << "EDX bit 9: " << edxBits[9] << ": [SUPPORTED] Onboard Advanced Programmable Interrupt Controller - (APIC)" << endl : std::cout << "EDX bit 9: " << edxBits[9] << ": [UNSUPPORTED] Onboard Advanced Programmable Interrupt Controller - (APIC)" << endl;
	(edxBits[10]) ? std::cout << "EDX bit 10: " << edxBits[10] << ": [SUPPORTED] Reserved" << endl : std::cout<< "EDX bit 10: "<< edxBits[10]<< ": [UNSUPPORTED] Reserved"<< endl;
	(edxBits[11]) ? std::cout<< "EDX bit 11: "<< edxBits[11]<< ": [SUPPORTED] SYSENTER and SYSEXIT fast system call instructions  - (SEP)"<< endl : std::cout<< "EDX bit 11: "<< edxBits[11]<< ": [UNSUPPORTED] SYSENTER and SYSEXIT fast system call instructions  - (SEP)"<< endl;
	(edxBits[12]) ? std::cout << "EDX bit 12: " << edxBits[12] << ": [SUPPORTED] Memory Type Range Registers - (MTRR)" << endl : std::cout << "EDX bit 12: " << edxBits[12] << ": [UNSUPPORTED] Memory Type Range Registers - (MTRR)" << endl;
	(edxBits[13]) ? std::cout << "EDX bit 13: " << edxBits[13] << ": [SUPPORTED] Page Global Enable bit in CR4 - (PGE)" << endl : std::cout << "EDX bit 13: " << edxBits[13] << ": [UNSUPPORTED] Page Global Enable bit in CR4 - (PGE)" << endl;
	(edxBits[14]) ? std::cout << "EDX bit 14: " << edxBits[14] << ": [SUPPORTED] Machine Check Architecture - (MCA)" << endl : std::cout << "EDX bit 14: " << edxBits[14] << ": [UNSUPPORTED] Machine Check Architecture - (MCA)" << endl;
	(edxBits[15]) ? std::cout << "EDX bit 15: " << edxBits[15] << ": [SUPPORTED] Conditional move: CMOV, FCMOV and FCOMI instructions - (CMOV)" << endl : std::cout << "EDX bit 15: " << edxBits[15] << ": [UNSUPPORTED] Conditional move: CMOV, FCMOV and FCOMI instructions - (CMOV)" << endl;
	(edxBits[16]) ? std::cout << "EDX bit 16: " << edxBits[16] << ": [SUPPORTED] Page Attribute Table - (PAT)" << endl : std::cout << "EDX bit 16: " << edxBits[16] << ": [UNSUPPORTED] Page Attribute Table - (PAT)" << endl;
	(edxBits[17]) ? std::cout << "EDX bit 17: " << edxBits[17] << ": [SUPPORTED] 36-bit Page Size Extension - (PSE-36)" << endl : std::cout << "EDX bit 17: " << edxBits[17] << ": [UNSUPPORTED] 36-bit Page Size Extension - (PSE-36)" << endl;
	(edxBits[18]) ? std::cout << "EDX bit 18: " << edxBits[18] << ": [SUPPORTED] Processor Serial Number supported and enable - (PSN)" << endl : std::cout << "EDX bit 18: " << edxBits[18] << ": [UNSUPPORTED] Processor Serial Number supported and enable - (PSN)" << endl;
	(edxBits[19]) ? std::cout << "EDX bit 19: " << edxBits[19] << ": [SUPPORTED] CLFLUSH cache line flush instruction (SSE2)  - (CLFSH)" << endl : std::cout << "EDX bit 19: " << edxBits[19] << ": [UNSUPPORTED] CLFLUSH cache line flush instruction (SSE2)  - (CLFSH)" << endl;
	(edxBits[20]) ? std::cout << "EDX bit 20: " << edxBits[20] << ": [SUPPORTED] No-execute (NX) bit (Itanium only, reserved on other CPUs - (NX)" << endl : std::cout<< "EDX bit 20: "<< edxBits[20]<< ": [UNSUPPORTED] No-execute (NX) bit (Itanium only, reserved on other CPUs - (NX)"<< endl;
	(edxBits[21]) ? std::cout<< "EDX bit 21: "<< edxBits[21]<< ": [SUPPORTED] Debug store: save trace of executed jumps - (DS)"<< endl : std::cout<< "EDX bit 21: "<< edxBits[21]<< ": [UNSUPPORTED] Debug store: save trace of executed jumps - (DS)"<< endl;
	(edxBits[22]) ? std::cout<< "EDX bit 22: "<< edxBits[22]<< ": [SUPPORTED] Onboard thermal control MSRs for ACPI - (ACPI)"<< endl : std::cout<< "EDX bit 22: "<< edxBits[22]<< ": [UNSUPPORTED] Onboard thermal control MSRs for ACPI - (ACPI)"<< endl;
	(edxBits[23]) ? std::cout<< "EDX bit 23: "<< edxBits[23]<< ": [SUPPORTED] MMX instructions (64-bit SIMD) - (MMX)"<< endl : std::cout<< "EDX bit 23: "<< edxBits[23]<< ": [UNSUPPORTED] MMX instructions (64-bit SIMD) - (MMX)"<< endl;
	(edxBits[24]) ? std::cout << "EDX bit 24: " << edxBits[24] << ": [SUPPORTED] FXSAVE, FXRSTOR instructions, CR4 bit 9 - (FXSR)" << endl : std::cout << "EDX bit 24: " << edxBits[24] << ": [UNSUPPORTED] FXSAVE, FXRSTOR instructions, CR4 bit 9 - (FXSR)" << endl;
	(edxBits[25]) ? std::cout << "EDX bit 25: " << edxBits[25] << ": [SUPPORTED] Streaming SIMD Extensions (SSE) / Katmai New Instructions 128-bit SIMD - (SSE)" << endl : std::cout << "EDX bit 25: " << edxBits[25] << ": [UNSUPPORTED] Streaming SIMD Extensions (SSE) / Katmai New Instructions 128-bit SIMD - (SSE)" << endl;
	(edxBits[26]) ? std::cout << "EDX bit 26: " << edxBits[26] << ": [SUPPORTED] SSE2 instructions - (SSE2)" << endl : std::cout << "EDX bit 26: " << edxBits[26] << ": [UNSUPPORTED] SSE2 instructions - (SSE2)" << endl;
	(edxBits[27]) ? std::cout << "EDX bit 27: " << edxBits[27] << ": [SUPPORTED] CPU cache implements self-snoop - (SS)" << endl : std::cout << "EDX bit 27: " << edxBits[27] << ": [UNSUPPORTED] CPU cache implements self-snoop - (SS)" << endl;
	(edxBits[28]) ? std::cout << "EDX bit 28: " << edxBits[28] << ": [SUPPORTED] Max APIC IDs reserved field is Valid - (HTT)" << endl : std::cout << "EDX bit 28: " << edxBits[28] << ": [UNSUPPORTED] Max APIC IDs reserved field is Valid - (HTT)" << endl;
	(edxBits[29]) ? std::cout << "EDX bit 29: " << edxBits[29] << ": [SUPPORTED] Thermal monitor automatically limits temperature - (TM)" << endl : std::cout << "EDX bit 29: " << edxBits[29] << ": [UNSUPPORTED] Thermal monitor automatically limits temperature - (TM)" << endl;
	(edxBits[30]) ? std::cout << "EDX bit 30: " << edxBits[30] << ": [SUPPORTED] IA64 processor emulating x86 - (IA64)" << endl : std::cout << "EDX bit 30: " << edxBits[30] << ": [UNSUPPORTED] IA64 processor emulating x86 - (IA64)" << endl;
	(edxBits[31]) ? std::cout << "EDX bit 31: " << edxBits[31] << ": [SUPPORTED] Pending Break Enable (PBE# pin) wakeup capability - (PBE)" << endl : std::cout << "EDX bit 31: " << edxBits[31] << ": [UNSUPPORTED] Pending Break Enable (PBE# pin) wakeup capability - (PBE)" << endl;
	std::cout << endl;
	

	// EAX=0x2: Cache and TLB Descriptor Information
	__cpuidex(cpuInfo, 0x2, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	if (eaxBits[31])
	{
		std::cout << "EAX=0x2: [Cache and TLB Descriptor Information (EAX) = Invalid Descriptors / No valid information.]" << endl;
	}
	else
	{
		//std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX) = " << std::hex << "0x" << cpuID2.EAX() << endl;
		std::cout << "EAX=0x2: [Cache and TLB Descriptor Information (EAX)] = " << eaxBits << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) - Number of times to query CPUID with 0x2 (should be 1) = " << eaxBits[7] << eaxBits[6] << eaxBits[5] << eaxBits[4] << eaxBits[3] << eaxBits[2] << eaxBits[1] << eaxBits[0] << endl;
		int descriptorEAX0 = extractBits(cpuInfo[0], 0, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) - Number of times to query CPUID with 0x2 (should be 1) = " << std::hex << "0x" << descriptorEAX0 << endl;
		//string descriptorEAX0String = getCacheAndTableDescriptor(descriptorEAX0);
		//std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) = " << descriptorEAX0String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 1) = " << eaxBits[15] << eaxBits[14] << eaxBits[13] << eaxBits[12] << eaxBits[11] << eaxBits[10] << eaxBits[9] << eaxBits[8] << endl;
		int descriptorEAX1 = extractBits(cpuInfo[0], 8, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 1) = " << std::hex << "0x" << descriptorEAX1 << endl;
		string descriptorEAX1String = getCacheAndTableDescriptor(descriptorEAX1);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 1) = " << descriptorEAX1String << endl;
		
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 2) = " << eaxBits[23] << eaxBits[22] << eaxBits[21] << eaxBits[20] << eaxBits[19] << eaxBits[18] << eaxBits[17] << eaxBits[16] << endl;
		int descriptorEAX2 = extractBits(cpuInfo[0], 16, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 2) = " << std::hex << "0x" << descriptorEAX2 << endl;
		string descriptorEAX2String = getCacheAndTableDescriptor(descriptorEAX2);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 2) = " << descriptorEAX2String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 3) = " << eaxBits[31] << eaxBits[30] << eaxBits[29] << eaxBits[28] << eaxBits[27] << eaxBits[26] << eaxBits[25] << eaxBits[24] << endl;
		int descriptorEAX3 = extractBits(cpuInfo[0], 24, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 3) = " << std::hex << "0x" << descriptorEAX3 << endl;
		string descriptorEAX3String = getCacheAndTableDescriptor(descriptorEAX3);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 3) = " << descriptorEAX3String << endl;
	}
	std::cout << endl;
	
	if (ebxBits[31])
	{
		std::cout << "EAX=0x2: [Cache and TLB Descriptor Information (EBX) = Invalid Descriptors / No valid information.]" << endl;
	}
	else
	{
		//std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX) = " << std::hex << "0x" << cpuInfo[1] << endl;
		std::cout << "EAX=0x2: [Cache and TLB Descriptor Information (EBX)] = " << ebxBits << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 0) = " << ebxBits[7] << ebxBits[6] << ebxBits[5] << ebxBits[4] << ebxBits[3] << ebxBits[2] << ebxBits[1] << ebxBits[0] << endl;
		int descriptorEBX0 = extractBits(cpuInfo[1], 0, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 0) = " << std::hex << "0x" << descriptorEBX0 << endl;
		string descriptorEBX0String = getCacheAndTableDescriptor(descriptorEBX0);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 0) = " << descriptorEBX0String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 1) = " << ebxBits[15] << ebxBits[14] << ebxBits[13] << ebxBits[12] << ebxBits[11] << ebxBits[10] << ebxBits[9] << ebxBits[8] << endl;
		int descriptorEBX1 = extractBits(cpuInfo[1], 8, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 1) = " << std::hex << "0x" << descriptorEBX1 << endl;
		string descriptorEBX1String = getCacheAndTableDescriptor(descriptorEBX1);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 1) = " << descriptorEBX1String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 2) = " << ebxBits[23] << ebxBits[22] << ebxBits[21] << ebxBits[20] << ebxBits[19] << ebxBits[18] << ebxBits[17] << ebxBits[16] << endl;
		int descriptorEBX2 = extractBits(cpuInfo[1], 16, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 2) = " << std::hex << "0x" << descriptorEBX2 << endl;
		string descriptorEBX2String = getCacheAndTableDescriptor(descriptorEBX2);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 2) = " << descriptorEBX2String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 3) = " << ebxBits[31] << ebxBits[30] << ebxBits[29] << ebxBits[28] << ebxBits[27] << ebxBits[26] << ebxBits[25] << ebxBits[24] << endl;
		int descriptorEBX3 = extractBits(cpuInfo[1], 24, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 3) = " << std::hex << "0x" << descriptorEBX3 << endl;
		string descriptorEBX3String = getCacheAndTableDescriptor(descriptorEBX3);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 3) = " << descriptorEBX3String << endl;
	}
	std::cout << endl;

	if (ecxBits[31])
	{
		std::cout << "EAX=0x2: [Cache and TLB Descriptor Information (ECX) = Invalid Descriptors / No valid information.]" << endl;
	}
	else
	{
		//std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX) = " << std::hex << "0x" << cpuInfo[2] << endl;
		std::cout << "EAX=0x2: [Cache and TLB Descriptor Information (ECX)] = " << ecxBits << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 0) = " << ecxBits[7] << ecxBits[6] << ecxBits[5] << ecxBits[4] << ecxBits[3] << ecxBits[2] << ecxBits[1] << ecxBits[0] << endl;
		int descriptorECX0 = extractBits(cpuInfo[2], 0, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 0) = " << std::hex << "0x" << descriptorECX0 << endl;
		string descriptorECX0String = getCacheAndTableDescriptor(descriptorECX0);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 0) = " << descriptorECX0String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 1) = " << ecxBits[15] << ecxBits[14] << ecxBits[13] << ecxBits[12] << ecxBits[11] << ecxBits[10] << ecxBits[9] << ecxBits[8] << endl;
		int descriptorECX1 = extractBits(cpuInfo[2], 8, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 1) = " << std::hex << "0x" << descriptorECX1 << endl;
		string descriptorECX1String = getCacheAndTableDescriptor(descriptorECX1);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 1) = " << descriptorECX1String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 2) = " << ecxBits[23] << ecxBits[22] << ecxBits[21] << ecxBits[20] << ecxBits[19] << ecxBits[18] << ecxBits[17] << ecxBits[16] << endl;
		int descriptorECX2 = extractBits(cpuInfo[2], 16, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 2) = " << std::hex << "0x" << descriptorECX2 << endl;
		string descriptorECX2String = getCacheAndTableDescriptor(descriptorECX2);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 2) = " << descriptorECX2String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 3) = " << ecxBits[31] << ecxBits[30] << ecxBits[29] << ecxBits[28] << ecxBits[27] << ecxBits[26] << ecxBits[25] << ecxBits[24] << endl;
		int descriptorECX3 = extractBits(cpuInfo[2], 24, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 3) = " << std::hex << "0x" << descriptorECX3 << endl;
		string descriptorECX3String = getCacheAndTableDescriptor(descriptorECX3);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 3) = " << descriptorECX3String << endl;
	}
	std::cout << endl;

	if (edxBits[31])
	{
		std::cout << "EAX=0x2: [Cache and TLB Descriptor Information (EDX) = Invalid Descriptors / No valid information.]" << endl;
	}
	else
	{
		//std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX) = " << std::hex << "0x" << cpuInfo[3] << endl;
		std::cout << "EAX=0x2: [Cache and TLB Descriptor Information (EDX)] = " << edxBits << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 0) = " << edxBits[7] << edxBits[6] << edxBits[5] << edxBits[4] << edxBits[3] << edxBits[2] << edxBits[1] << edxBits[0] << endl;
		int descriptorEDX0 = extractBits(cpuInfo[3], 0, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 0) = " << std::hex << "0x" << descriptorEDX0 << endl;
		string descriptorEDX0String = getCacheAndTableDescriptor(descriptorEDX0);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 0) = " << descriptorEDX0String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 1) = " << edxBits[15] << edxBits[14] << edxBits[13] << edxBits[12] << edxBits[11] << edxBits[10] << edxBits[9] << edxBits[8] << endl;
		int descriptorEDX1 = extractBits(cpuInfo[3], 8, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 1) = " << std::hex << "0x" << descriptorEDX1 << endl;
		string descriptorEDX1String = getCacheAndTableDescriptor(descriptorEDX1);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 1) = " << descriptorEDX1String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 2) = " << edxBits[23] << edxBits[22] << edxBits[21] << edxBits[20] << edxBits[19] << edxBits[18] << edxBits[17] << edxBits[16] << endl;
		int descriptorEDX2 = extractBits(cpuInfo[3], 16, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 2) = " << std::hex << "0x" << descriptorEDX2 << endl;
		string descriptorEDX2String = getCacheAndTableDescriptor(descriptorEDX2);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 2) = " << descriptorEDX2String << endl;

		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 3) = " << edxBits[31] << edxBits[30] << edxBits[29] << edxBits[28] << edxBits[27] << edxBits[26] << edxBits[25] << edxBits[24] << endl;
		int descriptorEDX3 = extractBits(cpuInfo[3], 24, 8);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 3) = " << std::hex << "0x" << descriptorEDX3 << endl;
		string descriptorEDX3String = getCacheAndTableDescriptor(descriptorEDX3);
		std::cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 3) = " << descriptorEDX3String << endl;
	}
	std::cout << endl;

	// EAX=0x3: Processor Serial Number
	__cpuidex(cpuInfo, 0x3, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);

	std::cout << "EAX=0x3: [Processor Serial Number (PSN)]:" << endl;
	std::cout << "EAX=0x3: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x3: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x3: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x3: [EDX] = " << edxBits << endl;
	std::cout << "EAX=0x3: PSN [EAX=0x1:EDX:ECX] (Pentium 3 CPUs - 96-bit) = " << std::hex << ZeroPadNumber(eaxBits1.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(edxBits.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(ecxBits.to_ulong(), 8) << endl;
	std::cout << "EAX=0x3: PSN [EAX:EBX:ECX:EDX] (Transmeta Crusoe and Efficeon CPUs - 128-bit) = " << std::hex << ZeroPadNumber(eaxBits.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(ebxBits.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(ecxBits.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(edxBits.to_ulong(), 8) << endl;
	std::cout << endl;

	// EAX=4 and EAX=8000'001Dh: Cache Hierarchy and Topology
	std::cout << "EAX=0x4 and EAX=8000001Dh: [Cache Hierarchy and Topology Information]: " << endl;

	eaxBits = -1;
	int i = 0;
	do
	{
		__cpuidex(cpuInfo, 0x4, i);
		eaxBits = bitset<32>(cpuInfo[0]);
		ebxBits = bitset<32>(cpuInfo[1]);
		ecxBits = bitset<32>(cpuInfo[2]);
		edxBits = bitset<32>(cpuInfo[3]);
		if (eaxBits == 0)
		{
			//std::cout << "EAX=0x4: No more cache levels available. Ending loop." << endl;
			break;
		}
		std::cout << "EAX=0x4: Cache Hierarchy and Topology Information (Intel): " << i << endl;
		std::cout << "EAX=0x4: [EAX] = " << eaxBits << endl;
		std::cout << "EAX=0x4: [EBX] = " << ebxBits << endl;
		std::cout << "EAX=0x4: [ECX] = " << ecxBits << endl;
		std::cout << "EAX=0x4: [EDX] = " << edxBits << endl;
		std::cout << "EAX: " << std::hex << "0x" << ZeroPadNumber(eaxBits.to_ulong(), 8) << endl;
		std::cout << "EBX: " << std::hex << "0x" << ZeroPadNumber(ebxBits.to_ulong(), 8) << endl;
		std::cout << "ECX: " << std::hex << "0x" << ZeroPadNumber(ecxBits.to_ulong(), 8) << endl;
		std::cout << "EDX: " << std::hex << "0x" << ZeroPadNumber(edxBits.to_ulong(), 8) << endl;

		std::cout << "EAX=0x4: Cache Type: EAX Bits 0:4 = " << std::hex << "0x" << extractBits(cpuInfo[0], 0, 4) << " - " << GetCacheType(extractBits(cpuInfo[0], 0, 4)) << endl;
		//std::cout << "EAX=0x4: Processor Type: EAX Bits 0:4 = " << std::hex << "0x" << eaxBits[4] << eaxBits[3] << eaxBits[2] << eaxBits[1] << eaxBits[0] << endl;

		std::cout << "EAX=0x4: Cache Level: EAX Bits 5:7 = " << std::hex << "0x" << extractBits(cpuInfo[0], 5, 3) << endl;

		int selfInitializingCacheLevel = extractBits(cpuInfo[0], 8, 1);
		if (selfInitializingCacheLevel)
		{
			std::cout << "EAX=0x4: Self Initializing Cache Level: EAX Bit 8 = " << std::hex << "0x" << selfInitializingCacheLevel << " - This cache level is self-initializing and does not require software initialization after reset." << endl;
		}
		else
		{
			std::cout << "EAX=0x4: Self Initializing Cache Level: EAX Bit 8 = " << std::hex << "0x" << selfInitializingCacheLevel << " - This cache level is not self-initializing and requires software initialization after reset." << endl;
		}

		std::cout << "EAX=0x4: Fully Associative Cache: EAX Bit 9 = " << std::hex << "0x" << extractBits(cpuInfo[0], 9, 1) << endl;
		std::cout << "EAX=0x4: WBINVD cache invalidation execution scope (Xeon Phi \"Knights Corner\" (GenuineIntel Family 0Bh) processor only): EAX Bit 10 = " << std::hex << "0x" << extractBits(cpuInfo[0], 10, 1) << endl;
		std::cout << "EAX=0x4: Cache Inclusiveness (Xeon Phi \"Knights Corner\" (GenuineIntel Family 0Bh) processor only): EAX Bit 11 = " << std::hex << "0x" << extractBits(cpuInfo[0], 11, 1) << endl;
		std::cout << "EAX=0x4: Reserved: EAX Bits 12:13 = " << std::hex << "0x" << extractBits(cpuInfo[0], 12, 2) << endl;
		std::cout << "EAX=0x4: Maximum number of addressable IDs for logical processors sharing this cache, minus 1: EAX Bits 14:25 = " << std::hex << "0x" << extractBits(cpuInfo[0], 14, 12) << endl;
		std::cout << "EAX=0x4: Maximum number of addressable IDs for processor cores in physical package, minus 1: EAX Bits 31:26 = " << std::hex << "0x" << extractBits(cpuInfo[0], 26, 6) << endl;

		std::cout << "EAX=0x4: System coherency line size in bytes, minus 1: EBX Bits 0:11 = " << std::hex << "0x" << extractBits(cpuInfo[1], 0, 12) << endl;
		std::cout << "EAX=0x4: Physical line partitions (number of cache lines that share a cache address tag), minus 1: EBX Bits 12:21 = " << std::hex << "0x" << extractBits(cpuInfo[1], 12, 10) << endl;
		std::cout << "EAX=0x4: Ways of cache associativity, minus 1: EBX Bits 22:31 = " << std::hex << "0x" << extractBits(cpuInfo[1], 22, 10) << endl;

		int wBINVDCacheInvalidationExecutionScope = extractBits(cpuInfo[3], 0, 1);
		if (wBINVDCacheInvalidationExecutionScope)
		{
			std::cout << "EAX=0x4: WBINVD cache invalidation execution scope: EDX Bit 0 = " << std::hex << "0x" << wBINVDCacheInvalidationExecutionScope << " - INVD/WBINVD instructions: will invalidate all lower-levels caches of this cache, including caches that belong to sibling processors sharing this cache." << endl;
		}
		else
		{
			std::cout << "EAX=0x4: WBINVD cache invalidation execution scope: EDX Bit 0 = " << std::hex << "0x" << wBINVDCacheInvalidationExecutionScope << " - INVD/WBINVD instructions: lower-level caches of sibling processors that are sharing this cache are not guaranteed to be all cleared." << endl;
		}

		int cacheInclusiveness = extractBits(cpuInfo[3], 1, 1);
		if (cacheInclusiveness)
		{
			std::cout << "EAX=0x4: Cache Inclusiveness: EDX Bit 1 = " << std::hex << "0x" << cacheInclusiveness << " - This cache is inclusive of lower cache levels." << endl;
		}
		else
		{
			std::cout << "EAX=0x4: Cache Inclusiveness: EDX Bit 1 = " << std::hex << "0x" << cacheInclusiveness << " - This cache is not inclusive of lower cache levels." << endl;
		}

		int complexCachingIndex = extractBits(cpuInfo[3], 2, 1);
		if (complexCachingIndex)
		{
			std::cout << "EAX=0x4: Complex Caching Index: EDX Bit 2 = " << std::hex << "0x" << complexCachingIndex << " - This cache has a complex caching index." << endl;
		}
		else
		{
			std::cout << "EAX=0x4: Complex Caching Index: EDX Bit 2 = " << std::hex << "0x" << complexCachingIndex << " - This cache is direct mapped and does not have a complex caching index." << endl;
		}

		std::cout << "EAX=0x4: Reserved: EDX Bit 3 = " << std::hex << "0x" << extractBits(cpuInfo[3], 3, 1) << endl;
		std::cout << "EAX=0x4: Reserved, but has been observed to be set for the level-2 cache of Intel Xeon Phi x200 (\"Knights Landing\") processors: EDX Bit 4 = " << std::hex << "0x" << extractBits(cpuInfo[3], 4, 1) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 5:7 = " << std::hex << "0x" << extractBits(cpuInfo[3], 5, 3) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 8 = " << std::hex << "0x" << extractBits(cpuInfo[3], 8, 1) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 9 = " << std::hex << "0x" << extractBits(cpuInfo[3], 9, 1) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 10 = " << std::hex << "0x" << extractBits(cpuInfo[3], 10, 1) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 11 = " << std::hex << "0x" << extractBits(cpuInfo[3], 11, 1) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 12:13 = " << std::hex << "0x" << extractBits(cpuInfo[3], 12, 2) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 14:21 = " << std::hex << "0x" << extractBits(cpuInfo[3], 14, 8) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 22:25 = " << std::hex << "0x" << extractBits(cpuInfo[3], 22, 4) << endl;
		std::cout << "EAX=0x4: Reserved: EDX Bit 26:31 = " << std::hex << "0x" << extractBits(cpuInfo[3], 26, 6) << endl;

		// CacheSize = (EBX[11:0] + 1) * (EBX[21:12] + 1) * (EBX[31:22] + 1) * (ECX + 1)
		int cacheSize = (extractBits(cpuInfo[1], 0, 12) + 1) * (extractBits(cpuInfo[1], 12, 10) + 1) * (extractBits(cpuInfo[1], 22, 10) + 1) * (extractBits(cpuInfo[2], 0, 32) + 1);
		std::cout << "EAX=0x4: CacheSize: (EBX[11:0] + 1) * (EBX[21:12] + 1) * (EBX[31:22] + 1) * (ECX + 1) = " << std::hex << "0x" << cacheSize << endl;

		std::cout << endl;
		i++;
	} while (eaxBits != 0);

	eaxBits = -1;
	i = 0;
	do
	{
		__cpuidex(cpuInfo, 0x8000001D, i);
		eaxBits = bitset<32>(cpuInfo[0]);
		ebxBits = bitset<32>(cpuInfo[1]);
		ecxBits = bitset<32>(cpuInfo[2]);
		edxBits = bitset<32>(cpuInfo[3]);
		if (eaxBits == 0)
		{
			//std::cout << "EAX=0x4: No more cache levels available. Ending loop." << endl;
			break;
		}
		std::cout << "EAX=0x8000001D: Cache Hierarchy and Topology Information (AMD): " << i << endl;
		std::cout << "EAX=0x8000001D: [EAX] = " << eaxBits << endl;
		std::cout << "EAX=0x8000001D: [EBX] = " << ebxBits << endl;
		std::cout << "EAX=0x8000001D: [ECX] = " << ecxBits << endl;
		std::cout << "EAX=0x8000001D: [EDX] = " << edxBits << endl;
		std::cout << "EAX: " << std::hex << "0x" << ZeroPadNumber(eaxBits.to_ulong(), 8) << endl;
		std::cout << "EBX: " << std::hex << "0x" << ZeroPadNumber(ebxBits.to_ulong(), 8) << endl;
		std::cout << "ECX: " << std::hex << "0x" << ZeroPadNumber(ecxBits.to_ulong(), 8) << endl;
		std::cout << "EDX: " << std::hex << "0x" << ZeroPadNumber(edxBits.to_ulong(), 8) << endl;
		std::cout << "EAX=0x8000001D: Cache Type: EAX Bits 0:4 = " << std::hex << "0x" << extractBits(cpuInfo[0], 0, 4) << " - " << GetCacheType(extractBits(cpuInfo[0], 0, 4)) << endl;
		//std::cout << "EAX=0x8000001D: Processor Type: EAX Bits 0:4 = " << std::hex << "0x" << eaxBits[4] << eaxBits[3] << eaxBits[2] << eaxBits[1] << eaxBits[0] << endl;

		std::cout << "EAX=0x8000001D: Cache Level: EAX Bits 5:7 = " << std::hex << "0x" << extractBits(cpuInfo[0], 5, 3) << endl;

		int selfInitializingCacheLevel = extractBits(cpuInfo[0], 8, 1);
		if (selfInitializingCacheLevel)
		{
			std::cout << "EAX=0x8000001D: Self Initializing Cache Level: EAX Bit 8 = " << std::hex << "0x" << selfInitializingCacheLevel << " - This cache level is self-initializing and does not require software initialization after reset." << endl;
		}
		else
		{
			std::cout << "EAX=0x8000001D: Self Initializing Cache Level: EAX Bit 8 = " << std::hex << "0x" << selfInitializingCacheLevel << " - This cache level is not self-initializing and requires software initialization after reset." << endl;
		}

		std::cout << "EAX=0x8000001D: Fully Associative Cache: EAX Bit 9 = " << std::hex << "0x" << extractBits(cpuInfo[0], 9, 1) << endl;
		std::cout << "EAX=0x8000001D: WBINVD cache invalidation execution scope (Xeon Phi \"Knights Corner\" (GenuineIntel Family 0Bh) processor only): EAX Bit 10 = " << std::hex << "0x" << extractBits(cpuInfo[0], 10, 1) << endl;
		std::cout << "EAX=0x8000001D: Cache Inclusiveness (Xeon Phi \"Knights Corner\" (GenuineIntel Family 0Bh) processor only): EAX Bit 11 = " << std::hex << "0x" << extractBits(cpuInfo[0], 11, 1) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EAX Bits 12:13 = " << std::hex << "0x" << extractBits(cpuInfo[0], 12, 2) << endl;
		std::cout << "EAX=0x8000001D: Maximum number of addressable IDs for logical processors sharing this cache, minus 1: EAX Bits 14:25 = " << std::hex << "0x" << extractBits(cpuInfo[0], 14, 12) << endl;
		std::cout << "EAX=0x8000001D: Maximum number of addressable IDs for processor cores in physical package, minus 1: EAX Bits 31:26 = " << std::hex << "0x" << extractBits(cpuInfo[0], 26, 6) << endl;

		std::cout << "EAX=0x8000001D: System coherency line size in bytes, minus 1: EBX Bits 0:11 = " << std::hex << "0x" << extractBits(cpuInfo[1], 0, 12) << endl;
		std::cout << "EAX=0x8000001D: Physical line partitions (number of cache lines that share a cache address tag), minus 1: EBX Bits 12:21 = " << std::hex << "0x" << extractBits(cpuInfo[1], 12, 10) << endl;
		std::cout << "EAX=0x8000001D: Ways of cache associativity, minus 1: EBX Bits 22:31 = " << std::hex << "0x" << extractBits(cpuInfo[1], 22, 10) << endl;

		int wBINVDCacheInvalidationExecutionScope = extractBits(cpuInfo[3], 0, 1);
		if (wBINVDCacheInvalidationExecutionScope)
		{
			std::cout << "EAX=0x8000001D: WBINVD cache invalidation execution scope: EDX Bit 0 = " << std::hex << "0x" << wBINVDCacheInvalidationExecutionScope << " - INVD/WBINVD instructions: will invalidate all lower-levels caches of this cache, including caches that belong to sibling processors sharing this cache." << endl;
		}
		else
		{
			std::cout << "EAX=0x8000001D: WBINVD cache invalidation execution scope: EDX Bit 0 = " << std::hex << "0x" << wBINVDCacheInvalidationExecutionScope << " - INVD/WBINVD instructions: lower-level caches of sibling processors that are sharing this cache are not guaranteed to be all cleared." << endl;
		}

		int cacheInclusiveness = extractBits(cpuInfo[3], 1, 1);
		if (cacheInclusiveness)
		{
			std::cout << "EAX=0x8000001D: Cache Inclusiveness: EDX Bit 1 = " << std::hex << "0x" << cacheInclusiveness << " - This cache is inclusive of lower cache levels." << endl;
		}
		else
		{
			std::cout << "EAX=0x8000001D: Cache Inclusiveness: EDX Bit 1 = " << std::hex << "0x" << cacheInclusiveness << " - This cache is not inclusive of lower cache levels." << endl;
		}

		int complexCachingIndex = extractBits(cpuInfo[3], 2, 1);
		if (complexCachingIndex)
		{
			std::cout << "EAX=0x8000001D: Complex Caching Index: EDX Bit 2 = " << std::hex << "0x" << complexCachingIndex << " - This cache has a complex caching index." << endl;
		}
		else
		{
			std::cout << "EAX=0x8000001D: Complex Caching Index: EDX Bit 2 = " << std::hex << "0x" << complexCachingIndex << " - This cache is direct mapped and does not have a complex caching index." << endl;
		}

		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 3 = " << std::hex << "0x" << extractBits(cpuInfo[3], 3, 1) << endl;
		std::cout << "EAX=0x8000001D: Reserved, but has been observed to be set for the level-2 cache of Intel Xeon Phi x200 (\"Knights Landing\") processors: EDX Bit 4 = " << std::hex << "0x" << extractBits(cpuInfo[3], 4, 1) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 5:7 = " << std::hex << "0x" << extractBits(cpuInfo[3], 5, 3) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 8 = " << std::hex << "0x" << extractBits(cpuInfo[3], 8, 1) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 9 = " << std::hex << "0x" << extractBits(cpuInfo[3], 9, 1) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 10 = " << std::hex << "0x" << extractBits(cpuInfo[3], 10, 1) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 11 = " << std::hex << "0x" << extractBits(cpuInfo[3], 11, 1) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 12:13 = " << std::hex << "0x" << extractBits(cpuInfo[3], 12, 2) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 14:21 = " << std::hex << "0x" << extractBits(cpuInfo[3], 14, 8) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 22:25 = " << std::hex << "0x" << extractBits(cpuInfo[3], 22, 4) << endl;
		std::cout << "EAX=0x8000001D: Reserved: EDX Bit 26:31 = " << std::hex << "0x" << extractBits(cpuInfo[3], 26, 6) << endl;

		// CacheSize = (EBX[11:0] + 1) * (EBX[21:12] + 1) * (EBX[31:22] + 1) * (ECX + 1)
		int cacheSize = (extractBits(cpuInfo[1], 0, 12) + 1) * (extractBits(cpuInfo[1], 12, 10) + 1) * (extractBits(cpuInfo[1], 22, 10) + 1) * (extractBits(cpuInfo[2], 0, 32) + 1);
		std::cout << "EAX=0x8000001D: CacheSize: (EBX[11:0] + 1) * (EBX[21:12] + 1) * (EBX[31:22] + 1) * (ECX + 1) = " << std::hex << "0x" << cacheSize << endl;
		std::cout << endl;
		i++;
	} while (eaxBits != 0);

	// EAX=4 and EAX=Bh: Intel Thread/Core and Cache Topology
	__cpuidex(cpuInfo, 0x4, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x4: [Intel Thread/Core and Cache Topology]: " << endl;
	std::cout << "EAX=0x4: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x4: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x4: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x4: [EDX] = " << edxBits << endl;
	std::cout << "EAX: " << std::hex << "0x" << ZeroPadNumber(eaxBits.to_ulong(), 8) << endl;
	std::cout << "EBX: " << std::hex << "0x" << ZeroPadNumber(ebxBits.to_ulong(), 8) << endl;
	std::cout << "ECX: " << std::hex << "0x" << ZeroPadNumber(ecxBits.to_ulong(), 8) << endl;
	std::cout << "EDX: " << std::hex << "0x" << ZeroPadNumber(edxBits.to_ulong(), 8) << endl;
	std::cout << endl;

	__cpuidex(cpuInfo, 0xB, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0xB: [Intel Thread/Core and Cache Topology]: " << endl;
	std::cout << "EAX=0xB: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0xB: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0xB: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0xB: [EDX] = " << edxBits << endl;
	std::cout << "EAX: " << std::hex << "0x" << ZeroPadNumber(eaxBits.to_ulong(), 8) << endl;
	std::cout << "EBX: " << std::hex << "0x" << ZeroPadNumber(ebxBits.to_ulong(), 8) << endl;
	std::cout << "ECX: " << std::hex << "0x" << ZeroPadNumber(ecxBits.to_ulong(), 8) << endl;
	std::cout << "EDX: " << std::hex << "0x" << ZeroPadNumber(edxBits.to_ulong(), 8) << endl;
	std::cout << endl;

	// EAX=5: MONITOR/MWAIT Features
	__cpuidex(cpuInfo, 0x5, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x5: [MONITOR/MWAIT Features]:" << endl;
	std::cout << "EAX=0x5: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x5: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x5: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x5: [EDX] = " << edxBits << endl;

	std::cout << "EAX=0x5: Smallest monitor-line size in bytes: EAX Bits 0:15 = " << std::hex << "0x" << extractBits(cpuInfo[0], 0, 16) << endl;
	std::cout << "EAX=0x5: Reserved: EAX Bits 16:31 = " << std::hex << "0x" << extractBits(cpuInfo[0], 16, 16) << endl;

	std::cout << "EAX=0x5: Largest  monitor-line size in bytes: EBX Bits 0:15 = " << std::hex << "0x" << extractBits(cpuInfo[1], 0, 16) << endl;
	std::cout << "EAX=0x5: Reserved: EBX Bits 16:31 = " << std::hex << "0x" << extractBits(cpuInfo[1], 16, 16) << endl;

	std::cout << "EAX=0x5: Enumeration of MONITOR/MWAIT extensions in ECX and EDX supported (EMX): ECX Bit 0 = " << std::hex << "0x" << extractBits(cpuInfo[2], 0, 1) << endl;
	std::cout << "EAX=0x5: Supports treating interrupts as break-events for MWAIT even when interrupts are disabled (IBE): ECX Bit 1 = " << std::hex << "0x" << extractBits(cpuInfo[2], 1, 1) << endl;
	std::cout << "EAX=0x5: Reserved: ECX Bit 2 = " << std::hex << "0x" << extractBits(cpuInfo[2], 2, 1) << endl;
	std::cout << "EAX=0x5: Allow MWAIT to be used for power management without setting up memory monitoring with MONITOR (Monitorless_­MWAIT): ECX Bit 3 = " << std::hex << "0x" << extractBits(cpuInfo[2], 3, 1) << endl;
	std::cout << "EAX=0x5: Reserved: ECX Bits 31:4 = " << std::hex << "0x" << extractBits(cpuInfo[2], 4, 28) << endl;

	std::cout << "EAX=0x5: Number of C0 sub-states supported for MWAIT: EDX Bits 3:0 = " << std::hex << "0x" << extractBits(cpuInfo[3], 0, 4) << endl;
	std::cout << "EAX=0x5: Number of C1 sub-states supported for MWAIT: EDX Bits 7:4 = " << std::hex << "0x" << extractBits(cpuInfo[3], 4, 4) << endl;
	std::cout << "EAX=0x5: Number of C2 sub-states supported for MWAIT: EDX Bits 11:8 = " << std::hex << "0x" << extractBits(cpuInfo[3], 8, 4) << endl;
	std::cout << "EAX=0x5: Number of C3 sub-states supported for MWAIT: EDX Bits 15:12 = " << std::hex << "0x" << extractBits(cpuInfo[3], 12, 4) << endl;
	std::cout << "EAX=0x5: Number of C4 sub-states supported for MWAIT: EDX Bits 19:16 = " << std::hex << "0x" << extractBits(cpuInfo[3], 16, 4) << endl;
	std::cout << "EAX=0x5: Number of C5 sub-states supported for MWAIT: EDX Bits 23:20 = " << std::hex << "0x" << extractBits(cpuInfo[3], 20, 4) << endl;
	std::cout << "EAX=0x5: Number of C6 sub-states supported for MWAIT: EDX Bits 27:24 = " << std::hex << "0x" << extractBits(cpuInfo[3], 24, 4) << endl;
	std::cout << "EAX=0x5: Number of C7 sub-states supported for MWAIT: EDX Bits 31:28 = " << std::hex << "0x" << extractBits(cpuInfo[3], 28, 4) << endl;

	std::cout << endl;

	// EAX=6: Thermal and Power Management
	__cpuidex(cpuInfo, 0x6, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x6: [Thermal and Power Management]:" << endl;
	std::cout << "EAX=0x6: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x6: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x6: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x6: [EDX] = " << edxBits << endl;

	std::cout << "EAX=0x6: [Thermal/power management feature bits in EAX]" << endl;
	(eaxBits[0]) ? std::cout << "EAX bit 0: " << eaxBits[0] << ": [SUPPORTED] Digital Thermal Sensor capability - (DTS)" << endl : std::cout << "EAX bit 0: " << eaxBits[0] << ": [UNSUPPORTED] Digital Thermal Sensor capability - (DTS)" << endl;
	(eaxBits[1]) ? std::cout << "EAX bit 1: " << eaxBits[1] << ": [SUPPORTED] Intel Turbo Boost Technology capability - (TURBO_BOOST)" << endl : std::cout << "EAX bit 1: " << eaxBits[1] << ": [UNSUPPORTED] Intel Turbo Boost Technology capability - (TURBO_BOOST)" << endl;
	(eaxBits[2]) ? std::cout << "EAX bit 2: " << eaxBits[2] << ": [SUPPORTED] Always Running APIC Timer capability  - (ARAT)" << endl : std::cout << "EAX bit 2: " << eaxBits[2] << ": [UNSUPPORTED] Always Running APIC Timer capability - (ARAT)" << endl;
	(eaxBits[3]) ? std::cout << "EAX bit 3: " << eaxBits[3] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 3: " << eaxBits[3] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[4]) ? std::cout << "EAX bit 4: " << eaxBits[4] << ": [SUPPORTED] Power Limit Notification capability - (PLN)" << endl : std::cout << "EAX bit 4: " << eaxBits[4] << ": [UNSUPPORTED] Power Limit Notification capability - (PLN)" << endl;
	(eaxBits[5]) ? std::cout << "EAX bit 5: " << eaxBits[5] << ": [SUPPORTED] Extended Clock Modulation Duty capability - (ECMD)" << endl : std::cout << "EAX bit 5: " << eaxBits[5] << ": [UNSUPPORTED] Extended Clock Modulation Duty capability - (ECMD)" << endl;
	(eaxBits[6]) ? std::cout << "EAX bit 6: " << eaxBits[6] << ": [SUPPORTED] Package Thermal Management capability - (PTM)" << endl : std::cout << "EAX bit 6: " << eaxBits[6] << ": [UNSUPPORTED] Package Thermal Management capability - (PTM)" << endl;
	(eaxBits[7]) ? std::cout << "EAX bit 7: " << eaxBits[7] << ": [SUPPORTED] Hardware-controlled Performance States. MSRs added: IA32_PM_ENABLE(770h), IA32_HWP_CAPABILITIES(771h), IA32_HWP_REQUEST(774h), IA32_HWP_STATUS(777h) - (HWP)" << endl : std::cout << "EAX bit 7: " << eaxBits[7] << ": [UNSUPPORTED] Hardware-controlled Performance States. MSRs added: IA32_PM_ENABLE(770h), IA32_HWP_CAPABILITIES(771h), IA32_HWP_REQUEST(774h), IA32_HWP_STATUS(777h) - (HWP)" << endl;
	(eaxBits[8]) ? std::cout << "EAX bit 8: " << eaxBits[8] << ": [SUPPORTED] HWP notification of dynamic guaranteed performance change - IA32_HWP_INTERRUPT(773h) MSR - (HWP_Notification)" << endl : std::cout << "EAX bit 8: " << eaxBits[8] << ": [UNSUPPORTED] HWP notification of dynamic guaranteed performance change - IA32_HWP_INTERRUPT(773h) MSR - (HWP_Notification)" << endl;
	(eaxBits[9]) ? std::cout << "EAX bit 9: " << eaxBits[9] << ": [SUPPORTED] HWP Activity Window control - bits 41:32 of IA32_HWP_REQUEST MSR - (HWP_Activity_Window)" << endl : std::cout << "EAX bit 9: " << eaxBits[9] << ": [UNSUPPORTED] HWP Activity Window control - bits 41:32 of IA32_HWP_REQUEST MSR - (HWP_Activity_Window)" << endl;
	(eaxBits[10]) ? std::cout << "EAX bit 10: " << eaxBits[10] << ": [SUPPORTED] HWP Energy/performance preference control - bits 31:24 of IA32_HWP_REQUEST MSR - (HWP_Energy_Performance_Preference)" << endl : std::cout << "EAX bit 10: " << eaxBits[10] << ": [UNSUPPORTED] HWP Energy/performance preference control - bits 31:24 of IA32_HWP_REQUEST MSR - (HWP_Energy_­Performance_Preference)" << endl;
	(eaxBits[11]) ? std::cout << "EAX bit 11: " << eaxBits[11] << ": [SUPPORTED] HWP Package-level control - IA32_HWP_REQUEST_PKG(772h) MSR - (HWP_Package_Level_Request)" << endl : std::cout << "EAX bit 11: " << eaxBits[11] << ": [UNSUPPORTED] HWP Package-level control - IA32_HWP_REQUEST_PKG(772h) MSR - (HWP_Package_Level_Request)" << endl;
	(eaxBits[12]) ? std::cout << "EAX bit 12: " << eaxBits[12] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 12: " << eaxBits[12] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[13]) ? std::cout << "EAX bit 13: " << eaxBits[13] << ": [SUPPORTED] Hardware Duty Cycling supported. MSRs added: IA32_PKG_HDC_CTL(DB0h), IA32_PM_CTL1(DB1h), IA32_THREAD_STALL(DB2h) - (HDC)" << endl : std::cout << "EAX bit 13: " << eaxBits[13] << ": [UNSUPPORTED] Hardware Duty Cycling supported. MSRs added: IA32_PKG_HDC_CTL(DB0h), IA32_PM_CTL1(DB1h), IA32_THREAD_STALL(DB2h) - (HDC)" << endl;
	(eaxBits[14]) ? std::cout << "EAX bit 14: " << eaxBits[14] << ": [SUPPORTED] Intel Turbo Boost Max Technology 3.0 available - (TURBO_BOOST_MAX)" << endl : std::cout << "EAX bit 14: " << eaxBits[14] << ": [UNSUPPORTED] Intel Turbo Boost Max Technology 3.0 available - (TURBO_BOOST_MAX)" << endl;
	(eaxBits[15]) ? std::cout << "EAX bit 15: " << eaxBits[15] << ": [SUPPORTED] Interrupts upon changes to IA32_HWP_CAPABILITIES.Highest_Performance (bits 7:0) supported - (HWP_CAP)" << endl : std::cout << "EAX bit 15: " << eaxBits[15] << ": [UNSUPPORTED] Interrupts upon changes to IA32_HWP_CAPABILITIES.Highest_Performance (bits 7:0) supported - (HWP_CAP)" << endl;
	(eaxBits[16]) ? std::cout << "EAX bit 16: " << eaxBits[16] << ": [SUPPORTED] HWP PECI override supported - bits 63:60 of IA32_HWP_PECI_REQUEST_INFO(775h) MSR - (HWP_PECI_OVERRIDE)" << endl : std::cout << "EAX bit 16: " << eaxBits[16] << ": [UNSUPPORTED] HWP PECI override supported - bits 63:60 of IA32_HWP_PECI_REQUEST_INFO(775h) MSR - (HWP_PECI_OOVERRIDE)" << endl;
	(eaxBits[17]) ? std::cout << "EAX bit 17: " << eaxBits[17] << ": [SUPPORTED] Flexible HWP - bits 63:59 of IA32_HWP_REQUEST MSR - (FLEXIBLE_HWP)" << endl : std::cout << "EAX bit 17: " << eaxBits[17] << ": [UNSUPPORTED] Flexible HWP - bits 63:59 of IA32_HWP_REQUEST MSR - (FLEXIBLE_HWP)" << endl;
	(eaxBits[18]) ? std::cout << "EAX bit 18: " << eaxBits[18] << ": [SUPPORTED] Fast access mode for IA32_HWP_REQUEST MSR supported - (HWP_REQUEST_FAST_ACCESS)" << endl : std::cout << "EAX bit 18: " << eaxBits[18] << ": [UNSUPPORTED] Fast access mode for IA32_HWP_REQUEST MSR supported - (HWP_REQUEST_FAST_ACCESS)" << endl;
	(eaxBits[19]) ? std::cout << "EAX bit 19: " << eaxBits[19] << ": [SUPPORTED] Hardware Feedback Interface. Added MSRs: IA32_HW_FEEDBACK_PTR(17D0h), IA32_HW_FEEDBACK_CONFIG(17D1h) (bit 0 enables HFI, bit 1 enables Intel Thread Director) - (HW_FEEDBACK)" << endl : std::cout << "EAX bit 19: " << eaxBits[19] << ": [UNSUPPORTED] Hardware Feedback Interface. Added MSRs: IA32_HW_FEEDBACK_PTR(17D0h), IA32_HW_FEEDBACK_CONFIG(17D1h) (bit 0 enables HFI, bit 1 enables Intel Thread Director) - (HW_FEEDBACK)" << endl;
	(eaxBits[20]) ? std::cout << "EAX bit 20: " << eaxBits[20] << ": [SUPPORTED] IA32_HWP_REQUEST of idle logical processor ignored when only one of two logical processors that share a physical processor is active. - (HWP_REQUEST_IGNORE_IDLE)" << endl : std::cout << "EAX bit 20: " << eaxBits[20] << ": [UNSUPPORTED] IA32_HWP_REQUEST of idle logical processor ignored when only one of two logical processors that share a physical processor is active. - (HWP_REQUEST_IGNORE_IDLE)" << endl;
	(eaxBits[21]) ? std::cout << "EAX bit 21: " << eaxBits[21] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 21: " << eaxBits[21] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[22]) ? std::cout << "EAX bit 22: " << eaxBits[22] << ": [SUPPORTED] IA32_HWP_CTL(776h) MSR supported - (HWP Control MSR)" << endl : std::cout << "EAX bit 22: " << eaxBits[22] << ": [UNSUPPORTED] IA32_HWP_CTL(776h) MSR supported - (HWP Control MSR)" << endl;
	(eaxBits[23]) ? std::cout << "EAX bit 23: " << eaxBits[23] << ": [SUPPORTED] Intel Thread Director supported. Added MSRs: IA32_THREAD_FEEDBACK_CHAR(17D2h), IA32_HW_FEEDBACK_THREAD_CONFIG(17D4h) - (THREAD_DIRECTOR)" << endl : std::cout << "EAX bit 23: " << eaxBits[23] << ": [UNSUPPORTED] Intel Thread Director supported. Added MSRs: IA32_THREAD_FEEDBACK_CHAR(17D2h), IA32_HW_FEEDBACK_THREAD_CONFIG(17D4h) - (THREAD_DIRECTOR)" << endl;
	(eaxBits[24]) ? std::cout << "EAX bit 24: " << eaxBits[24] << ": [SUPPORTED] (IA32_THERM_INTERRUPT MSR bit 25 supported)" << endl : std::cout << "EAX bit 24: " << eaxBits[24] << ": [UNSUPPORTED] (IA32_THERM_INTERRUPT MSR bit 25 supported)" << endl;
	(eaxBits[25]) ? std::cout << "EAX bit 25: " << eaxBits[25] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 25: " << eaxBits[25] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[26]) ? std::cout << "EAX bit 26: " << eaxBits[26] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 26: " << eaxBits[26] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[27]) ? std::cout << "EAX bit 27: " << eaxBits[27] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 27: " << eaxBits[27] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[28]) ? std::cout << "EAX bit 28: " << eaxBits[28] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 28: " << eaxBits[28] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[29]) ? std::cout << "EAX bit 29: " << eaxBits[29] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 29: " << eaxBits[29] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[30]) ? std::cout << "EAX bit 30: " << eaxBits[30] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 30: " << eaxBits[30] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[31]) ? std::cout << "EAX bit 31 " << eaxBits[31] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 31: " << eaxBits[31] << ": [UNSUPPORTED] Reserved" << endl;

	std::cout << "EAX=0x6: [Thermal / power management feature fields in EBX, ECX and EDX]" << endl;
	std::cout << "EAX=0x6: Number of Interrupt Thresholds in Digital Thermal Sensor: EBX Bits 3:0 = " << std::hex << "0x" << extractBits(cpuInfo[1], 0, 4) << endl;
	std::cout << "EAX=0x6: Number of Interrupt Thresholds in Digital Thermal Sensor: EBX Bits 31:4 = " << std::hex << "0x" << extractBits(cpuInfo[1], 7, 28) << endl;

	(ecxBits[0]) ? std::cout << "ECX bit 0: " << ecxBits[0] << ": [SUPPORTED] Effective frequency interface supported - IA32_MPERF(0E7h) and IA32_APERF(0E8h) MSRs" << endl : std::cout << "ECX bit 0: " << ecxBits[0] << ": [UNSUPPORTED] Effective frequency interface supported - IA32_MPERF(0E7h) and IA32_APERF(0E8h) MSRs" << endl;
	(ecxBits[1]) ? std::cout << "ECX bit 1: " << ecxBits[1] << ": [SUPPORTED] ACNT2 Capability supported" << endl : std::cout << "ECX bit 1: " << ecxBits[1] << ": [UNSUPPORTED] ACNT2 Capability supported" << endl;
	(ecxBits[2]) ? std::cout << "ECX bit 2: " << ecxBits[2] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 2: " << ecxBits[2] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[3]) ? std::cout << "ECX bit 3: " << ecxBits[3] << ": [SUPPORTED] Performance-Energy Bias capability - IA32_ENERGY_PERF_BIAS(1B0h) MSR" << endl : std::cout << "ECX bit 3: " << ecxBits[3] << ": [UNSUPPORTED] Performance-Energy Bias capability - IA32_ENERGY_PERF_BIAS(1B0h) MSR" << endl;
	std::cout << "EAX=0x6: Reserved: ECX Bits 7:4 = " << std::hex << "0x" << extractBits(cpuInfo[2], 4, 4) << endl;
	std::cout << "EAX=0x6: Number of Intel Thread Director classes supported by hardware: ECX Bits 15:8 = " << std::hex << "0x" << extractBits(cpuInfo[2], 8, 8) << endl;
	std::cout << "EAX=0x6: Reserved: ECX Bits 31:16 = " << std::hex << "0x" << extractBits(cpuInfo[2], 16, 16) << endl;

	(edxBits[0]) ? std::cout << "EDX bit 0: " << edxBits[0] << ": [SUPPORTED] Hardware Feedback reporting: Performance Capability Reporting supported" << endl : std::cout << "EDX bit 0: " << edxBits[0] << ": [UNSUPPORTED] Hardware Feedback reporting: Performance Capability Reporting supported" << endl;
	(edxBits[1]) ? std::cout << "EDX bit 1: " << edxBits[1] << ": [SUPPORTED] Hardware Feedback reporting: Efficiency Capability Reporting supported" << endl : std::cout << "EDX bit 1: " << edxBits[1] << ": [UNSUPPORTED] Hardware Feedback reporting: Efficiency Capability Reporting supported" << endl;
	std::cout << "EAX=0x6: Reserved: EDX Bits 7:2 = " << std::hex << "0x" << extractBits(cpuInfo[3], 2, 6) << endl;
	std::cout << "EAX=0x6: Size of Hardware Feedback interface structure (in units of 4 KiB) minus 1: EDX Bits 11:8 = " << std::hex << "0x" << extractBits(cpuInfo[3], 8, 4) << endl;
	std::cout << "EAX=0x6: Reserved: EDX Bits 15:12 = " << std::hex << "0x" << extractBits(cpuInfo[3], 12, 4) << endl;
	std::cout << "EAX=0x6: Index of this logical processor's row in hardware feedback interface structure: EDX Bits 31:16 = " << std::hex << "0x" << extractBits(cpuInfo[3], 16, 16) << endl;

	std::cout << endl;

	// EAX=7, ECX=0: Extended Features
	// EAX=7, ECX=1: Extended Features
	// EAX=7, ECX=2: Extended Features
	__cpuidex(cpuInfo, 0x7, 0x0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x7: ECX=0x0 [Extended Features]:" << endl;
	std::cout << "EAX=0x7: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x7: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x7: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x7: [EDX] = " << edxBits << endl;
	std::cout << endl;

	__cpuidex(cpuInfo, 0x7, 0x1);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x7: ECX=0x1 [Extended Features]:" << endl;
	std::cout << "EAX=0x7: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x7: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x7: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x7: [EDX] = " << edxBits << endl;
	std::cout << endl;

	__cpuidex(cpuInfo, 0x7, 0x2);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x7: ECX=0x2 [Extended Features]:" << endl;
	std::cout << "EAX=0x7: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x7: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x7: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x7: [EDX] = " << edxBits << endl;
	std::cout << endl;

	// EAX=0Dh: XSAVE Features and State Components
	__cpuidex(cpuInfo, 0xD, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0xD: [XSAVE Features and State Components]:" << endl;
	std::cout << "EAX=0xD: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0xD: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0xD: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0xD: [EDX] = " << edxBits << endl;
	std::cout << endl;

	// EAX=12h: SGX Capabilities
	__cpuidex(cpuInfo, 0x12, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x12: [SGX Capabilities]:" << endl;
	std::cout << "EAX=0x12: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x12: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x12: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x12: [EDX] = " << edxBits << endl;
	std::cout << endl;

	// EAX=14h: Processor Trace
	__cpuidex(cpuInfo, 0x14, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x14: [Processor Trace]:" << endl;
	std::cout << "EAX=0x14: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x14: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x14: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x14: [EDX] = " << edxBits << endl;
	std::cout << endl;

	// EAX = 15h and EAX = 16h: CPU, TSC, Bus and Core Crystal Clock Frequencies
	__cpuidex(cpuInfo, 0x15, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x15:	[TSC and Core Crystal frequency information]:" << endl;
	std::cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator (EAX) = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[0], 8) << endl;
	std::cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator (EAX) = " << eaxBits << endl;
	std::cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator (EBX) = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[1], 8) << endl;
	std::cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator (EBX) = " << ebxBits << endl;
	std::cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz (ECX) = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[2], 8) << endl;
	std::cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz (ECX) = " << ecxBits << endl;
	std::cout << "EAX=0x15: TSC frequency, in units of Hz (EDX) = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[3], 8) << endl;
	std::cout << "EAX=0x15: TSC frequency, in units of Hz (EDX) = " << edxBits << endl;
	std::cout << endl;

	__cpuidex(cpuInfo, 0x16, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x16: [Processor and Bus specification frequencies]:" << endl;
	std::cout << "EAX=0x16: Processor Base Frequency (in MHz): EAX Bits 15:0 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[0], 15, 0), 8) << endl;
	std::cout << "EAX=0x16: Processor Base Frequency (in MHz): EAX Bits 15:0 = " << extractBits(cpuInfo[0], 15, 0) << endl;
	std::cout << "EAX=0x16: Processor Maximum Frequency (in MHz): EBX Bits 15:0 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[1], 15, 0), 8) << endl;
	std::cout << "EAX=0x16: Processor Maximum Frequency (in MHz): EBX Bits 15:0 = " << extractBits(cpuInfo[1], 15, 0) << endl;
	std::cout << "EAX=0x16: Bus/Reference frequency (in MHz): ECX Bits 15:0 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[2], 15, 0), 8) << endl;
	std::cout << "EAX=0x16: Bus/Reference frequency (in MHz): ECX Bits 15:0 = " << extractBits(cpuInfo[2], 15, 0) << endl;
	std::cout << "EAX=0x16: Reserved: EDX = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[3], 8) << endl;
	std::cout << "EAX=0x16: Reserved: EDX = " << edxBits << endl;
	std::cout << endl;







	// EAX=17h: SoC Vendor Attribute Enumeration
	// EAX=18h: TLB Hierarchy and Topology
	// EAX=19h: Intel Key Locker Features
	// EAX=1Dh: Intel AMX Tile Information
	// EAX=1Eh: Intel AMX Tile Multiplier (TMUL) Information
	// EAX=21h: Reserved for TDX enumeration
	// EAX=24h, ECX=0: AVX10 Converged Vector ISA
	// EAX=24h, ECX=1: Discrete AVX10 Features
	// EAX=2000'0000h: Highest Xeon Phi Function Implemented
	// EAX=2000'0001h: Xeon Phi Feature Bits
	// EAX=4000'0000h-4FFFF'FFFh: Reserved for Hypervisors
	// EAX=8000'0000h: Highest Extended Function Implemented
	// EAX=8000'0001h: Extended Processor Info and Feature Bits
	// EAX=8000'0002h,8000'0003h,8000'0004h: Processor Brand String
	// EAX=8000'0005h: L1 Cache and TLB Identifiers
	// EAX=8000'0006h: Extended L2 Cache Features
	// EAX=8000'0007h: Processor Power Management Information and RAS Capabilities
	// EAX=8000'0008h: Virtual and Physical Address Sizes
	// EAX=8000'000Ah: SVM features
	// EAX=8000'001Fh: Encrypted Memory Capabilities
	// EAX=8000'0021h: Extended Feature Identification
	// EAX=8000'0025h: Encrypted Memory Capabilities 2
	// EAX=8C86'0000h: Hygon Extended Feature Flags
	// EAX=8FFF'FFFEh and EAX=8FFF'FFFFh: AMD Easter Eggs
	// EAX=C000'0000h: Highest Centaur Extended Function
	// EAX=C000'0001h: Centaur Feature Information
	// EAX=C000'0002h: Centaur Extended CPUID Performance Data
	// EAX=C000'0006h, ECX=0: Zhaoxin Feature Information







	return 0;
}


