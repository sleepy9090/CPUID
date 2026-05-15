#include "CPUID.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>

using namespace std;

// pad a number with zeros to make it 8 characters long
string ZeroPadNumber(int num) {
	std::stringstream ss;
	ss << num; // Convert integer to string
	std::string paddedString;
	ss >> paddedString; // Get the string from stringstream

	// Append zeros to the left
	int str_length = paddedString.length();
	for (int i = 0; i < 8 - str_length; i++)
	{
		paddedString = "0" + paddedString; // Prepend zeros
	}
	return paddedString;
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
	CPUID cpuID(0x0); // Get CPU vendor

	string vendor;
	vendor += string((const char*)&cpuID.EBX(), 4);
	vendor += string((const char*)&cpuID.EDX(), 4);
	vendor += string((const char*)&cpuID.ECX(), 4);

	cout << "EAX=0: Manufacturer ID: EBX = " << std::hex << "0x" << cpuID.EBX() << " " << string((const char*)&cpuID.EBX(), 4) << endl;
	cout << "EAX=0: Manufacturer ID: EDX = " << std::hex << "0x" << cpuID.EDX() << " " << string((const char*)&cpuID.EDX(), 4) << endl;
	cout << "EAX=0: Manufacturer ID: ECX = " << std::hex << "0x" << cpuID.ECX() << " " << string((const char*)&cpuID.ECX(), 4) << endl;
	cout << "EAX=0: Highest Function Parameter: EAX = " << std::hex << "0x" << cpuID.EAX() << endl;
	cout << "CPU vendor = " << vendor << endl;
	cout << endl;


	CPUID cpuID1(0x1);
	// Example number from which bits are to be extracted
	//unsigned int num = cpuID1.EAX();
	// Starting position of bits to extract
	//unsigned int pos = 0;
	// Number of bits to extract
	//unsigned int k = 4;
	//unsigned int steppingId = extractBits(cpuID1.EAX(), 0, 4);

	bitset<32> eaxBits = bitset<32>(cpuID1.EAX());
	bitset<32> ebxBits = bitset<32>(cpuID1.EBX());
	bitset<32> ecxBits = bitset<32>(cpuID1.ECX());
	bitset<32> edxBits = bitset<32>(cpuID1.EDX());

	bitset<32> eaxBits1 = eaxBits;
	
	cout << "EAX=0x1: Processor Version Information [EAX] = " << eaxBits << endl;
	cout << "EAX=0x1: Additional Information [EBX] = " << ebxBits << endl;
	cout << "EAX=0x1: Feature Bits [ECX] = " << ecxBits << endl;
	cout << "EAX=0x1: Feature Bits [EDX] = " << edxBits << endl;

	cout << "EAX=0x1: Stepping ID: EAX Bits 3:0 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 0, 4) << endl;

	unsigned int modelId = extractBits(cpuID1.EAX(), 4, 4);
	unsigned int familyId = extractBits(cpuID1.EAX(), 8, 4);
	unsigned int extendedModelId = extractBits(cpuID1.EAX(), 16, 4);

	cout << "EAX=0x1: Family ID: EAX Bits 8:11 = " << std::hex << "0x" << familyId << endl;
	cout << "EAX=0x1: Model: EAX Bits 4:7 = " << std::hex << "0x" << modelId << endl;
	if (familyId == 0x6 || familyId == 0xF)
	{
		unsigned int extendedModelIdLeftShifted = extendedModelId << 4;
		unsigned int processorModel = modelId + extendedModelIdLeftShifted;
		cout << "Extended Model ID left-shifted by 4 bits: " << std::hex << "0x" << extendedModelIdLeftShifted << endl;
		cout << "EAX=0x1: Actual Model: Model (EAX Bits 4:7) + (Extended Model Id (EAX Bits 16:19) << 4)  = " << std::hex << "0x" << processorModel << endl;
	}

	cout << "EAX=0x1: Processor Type: EAX Bits 12:13 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 12, 2) << endl;
	cout << "EAX=0x1: Reserved: EAX Bits 14:15 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 14, 2) << endl;
	cout << "EAX=0x1: Extended Model ID: EAX Bits 16:19 = " << std::hex << "0x" << extendedModelId << endl;
	cout << "EAX=0x1: Extended Family ID: EAX Bits 20:27 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 20, 8) << endl;
	cout << "EAX=0x1: Reserved: EAX Bits 28:31 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 28, 4) << endl;
	cout << endl;



	cout << "EAX=0x1: [EBX Additional Information]" << endl;
	cout << "EBX bits 7:0 Brand Index = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 0, 8) << endl;
	cout << "EBX bits 15:8 CLFLUSH line size (Value * 8 = cache line size in bytes) = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 8, 8) << endl;
	cout << "EBX bits 23:16 Maximum number of addressable IDs for logical processors in this physical package = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 16, 8) << endl;
	cout << "EBX bits 31:24 Local APIC ID: The initial APIC-ID is used to identify the executing logical processor = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 24, 8) << endl;
	cout << endl;



	cout << "EAX=0x1: [ECX feature bits]" << endl;
	(ecxBits[0]) ? cout << "ECX bit 0: " << ecxBits[0] << ": [SUPPORTED] SSE3 (Prescott New Instructions - PNI) - (SSE3)" << endl : cout << "ECX bit 0: " << ecxBits[0] << ": [UNSUPPORTED] SSE3 (Prescott New Instructions - PNI) - (SSE3)" << endl;
	(ecxBits[1]) ? cout << "ECX bit 1: " << ecxBits[1] << ": [SUPPORTED] PCLMULQDQ (carry-less multiply) instruction - (PCLMULQDQ)" << endl : cout << "ECX bit 1: " << ecxBits[1] << ": [UNSUPPORTED] PCLMULQDQ (carry-less multiply) instruction - (PCLMULQDQ)" << endl;
	(ecxBits[2]) ? cout << "ECX bit 2: " << ecxBits[2] << ": [SUPPORTED] 64-bit debug store (edx bit 21) - (DTES64)" << endl : cout << "ECX bit 2: " << ecxBits[2] << ": [UNSUPPORTED] 64-bit debug store (edx bit 21) - (DTES64)" << endl;
	(ecxBits[3]) ? cout << "ECX bit 3: " << ecxBits[3] << ": [SUPPORTED] MONITOR and MWAIT instructions (PNI) - (MONITOR)" << endl : cout << "ECX bit 3: " << ecxBits[3] << ": [UNSUPPORTED] MONITOR and MWAIT instructions (PNI) - (MONITOR)" << endl;
	(ecxBits[4]) ? cout << "ECX bit 4: " << ecxBits[4] << ": [SUPPORTED] CPL qualified debug store - (DS-CPL)" << endl : cout << "ECX bit 4: " << ecxBits[4] << ": [UNSUPPORTED] CPL qualified debug store - (DS-CPL)" << endl;
	(ecxBits[5]) ? cout << "ECX bit 5: " << ecxBits[5] << ": [SUPPORTED] Virtual Machine eXtensions - (VMX)" << endl : cout << "ECX bit 5: " << ecxBits[5] << ": [UNSUPPORTED] Virtual Machine eXtensions - (VMX)" << endl;
	(ecxBits[6]) ? cout << "ECX bit 6: " << ecxBits[6] << ": [SUPPORTED] Safer Mode Extensions (LaGrande) (GETSEC instruction) - (SMX)" << endl : cout << "ECX bit 6: " << ecxBits[6] << ": [UNSUPPORTED] Safer Mode Extensions (LaGrande) (GETSEC instruction) - (SMX)" << endl;
	(ecxBits[7]) ? cout << "ECX bit 7: " << ecxBits[7] << ": [SUPPORTED] Enhanced SpeedStep - (EST)" << endl : cout << "ECX bit 7: " << ecxBits[7] << ": [UNSUPPORTED] Enhanced SpeedStep - (EST)" << endl;
	(ecxBits[8]) ? cout << "ECX bit 8: " << ecxBits[8] << ": [SUPPORTED] Thermal Monitor 2 - (TM2)" << endl : cout << "ECX bit 8: " << ecxBits[8] << ": [UNSUPPORTED] Thermal Monitor 2 - (TM2)" << endl;
	(ecxBits[9]) ? cout << "ECX bit 9: " << ecxBits[9] << ": [SUPPORTED] Supplemental SSE3 instructions - (SSSE3)" << endl : cout << "ECX bit 9: " << ecxBits[9] << ": [UNSUPPORTED] Supplemental SSE3 instructions - (SSSE3)" << endl;
	(ecxBits[10]) ? cout << "ECX bit 10: " << ecxBits[10] << ": [SUPPORTED] L1 Context ID - (CNXT-ID)" << endl : cout << "ECX bit 10: " << ecxBits[10] << ": [UNSUPPORTED] L1 Context ID - (CNXT-ID)" << endl;
	(ecxBits[11]) ? cout << "ECX bit 11: " << ecxBits[11] << ": [SUPPORTED] Silicon Debug interface - (SDBG)" << endl : cout << "ECX bit 11: " << ecxBits[11] << ": [UNSUPPORTED] Silicon Debug interface - (SDBG)" << endl;
	(ecxBits[12]) ? cout << "ECX bit 12: " << ecxBits[12] << ": [SUPPORTED] Fused multiply-add (FMA3) - (FMA)" << endl : cout << "ECX bit 12: " << ecxBits[12] << ": [UNSUPPORTED] Fused multiply-add (FMA3) - (FMA)" << endl;
	(ecxBits[13]) ? cout << "ECX bit 13: " << ecxBits[13] << ": [SUPPORTED] CMPXCHG16B instruction - (CMPXCHG16B)" << endl : cout << "ECX bit 13: " << ecxBits[13] << ": [UNSUPPORTED] CMPXCHG16B instruction - (CMPXCHG16B)" << endl;
	(ecxBits[14]) ? cout << "ECX bit 14: " << ecxBits[14] << ": [SUPPORTED] Can disable sending task priority messages - (xTPR Update Control)" << endl : cout << "ECX bit 14: " << ecxBits[14] << ": [UNSUPPORTED] Can disable sending task priority messages - (xTPR Update Control)" << endl;
	(ecxBits[15]) ? cout << "ECX bit 15: " << ecxBits[15] << ": [SUPPORTED] Perfmon & debug capability - (PDCM)" << endl : cout << "ECX bit 15: " << ecxBits[15] << ": [UNSUPPORTED] Perfmon & debug capability - (PDCM)" << endl;
	(ecxBits[16]) ? cout << "ECX bit 16: " << ecxBits[16] << ": [SUPPORTED] Reserved" << endl : cout << "ECX bit 16: " << ecxBits[16] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[17]) ? cout << "ECX bit 17: " << ecxBits[17] << ": [SUPPORTED] Process context identifiers (CR4 bit 17) - (PCID)" << endl : cout << "ECX bit 17: " << ecxBits[17] << ": [UNSUPPORTED] Process context identifiers (CR4 bit 17) - (PCID)" << endl;
	(ecxBits[18]) ? cout << "ECX bit 18: " << ecxBits[18] << ": [SUPPORTED] Direct cache access for DMA writes - (DCA)" << endl : cout << "ECX bit 18: " << ecxBits[18] << ": [UNSUPPORTED] Direct cache access for DMA writes - (DCA)" << endl;
	(ecxBits[19]) ? cout << "ECX bit 19: " << ecxBits[19] << ": [SUPPORTED] SSE4.1 instructions - (SSE4.1)" << endl : cout << "ECX bit 19: " << ecxBits[19] << ": [UNSUPPORTED] SSE4.1 instructions - (SSE4.1)" << endl;
	(ecxBits[20]) ? cout << "ECX bit 20: " << ecxBits[20] << ": [SUPPORTED] SSE4.2 instructions - (SSE4.2)" << endl : cout << "ECX bit 20: " << ecxBits[20] << ": [UNSUPPORTED] SSE4.2 instructions - (SSE4.2)" << endl;
	(ecxBits[21]) ? cout << "ECX bit 21: " << ecxBits[21] << ": [SUPPORTED] x2APIC (enhanced APIC) - (X2APIC)" << endl : cout << "ECX bit 21: " << ecxBits[21] << ": [UNSUPPORTED] x2APIC (enhanced APIC) - (X2APIC)" << endl;
	(ecxBits[22]) ? cout << "ECX bit 22: " << ecxBits[22] << ": [SUPPORTED] MOVBE instruction (big-endian) - (MOVBE)" << endl : cout << "ECX bit 22: " << ecxBits[22] << ": [UNSUPPORTED] MOVBE instruction (big-endian) - (MOVBE)" << endl;
	(ecxBits[23]) ? cout << "ECX bit 23: " << ecxBits[23] << ": [SUPPORTED] POPCNT instruction - (POPCNT)" << endl : cout << "ECX bit 23: " << ecxBits[23] << ": [UNSUPPORTED] POPCNT instruction - (POPCNT)" << endl;
	(ecxBits[24]) ? cout << "ECX bit 24: " << ecxBits[24] << ": [SUPPORTED] APIC implements one-shot operation using a TSC deadline value - (TSC-Deadline)" << endl : cout << "ECX bit 24: " << ecxBits[24] << ": [UNSUPPORTED] APIC implements one-shot operation using a TSC deadline value - (TSC-Deadline)" << endl;
	(ecxBits[25]) ? cout << "ECX bit 25: " << ecxBits[25] << ": [SUPPORTED] AES instruction set - (AES-NI)" << endl : cout << "ECX bit 25: " << ecxBits[25] << ": [UNSUPPORTED] AES instruction set - (AES-NI)" << endl;
	(ecxBits[26]) ? cout << "ECX bit 26: " << ecxBits[26] << ": [SUPPORTED] Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions - (XSAVE)" << endl : cout << "ECX bit 26: " << ecxBits[26] << ": [UNSUPPORTED] Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions - (XSAVE)" << endl;
	(ecxBits[27]) ? cout << "ECX bit 27: " << ecxBits[27] << ": [SUPPORTED] XSAVE enabled by OS - (OSXSAVE)" << endl : cout << "ECX bit 27: " << ecxBits[27] << ": [UNSUPPORTED] XSAVE enabled by OS - (OSXSAVE)" << endl;
	(ecxBits[28]) ? cout << "ECX bit 28: " << ecxBits[28] << ": [SUPPORTED] Advanced Vector Extensions (256-bit SIMD) - (AVX)" << endl : cout << "ECX bit 28: " << ecxBits[28] << ": [UNSUPPORTED] Advanced Vector Extensions (256-bit SIMD) - (AVX)" << endl;
	(ecxBits[29]) ? cout << "ECX bit 29: " << ecxBits[29] << ": [SUPPORTED] Floating-point conversion instructions to/from FP16 format - (F16C)" << endl : cout << "ECX bit 29: " << ecxBits[29] << ": [UNSUPPORTED] Floating-point conversion instructions to/from FP16 format - (F16C)" << endl;
	(ecxBits[30]) ? cout << "ECX bit 30: " << ecxBits[30] << ": [SUPPORTED] RDRAND (on-chip random number generator) feature - (RDRAND)" << endl : cout << "ECX bit 30: " << ecxBits[30] << ": [UNSUPPORTED] RDRAND (on-chip random number generator) feature - (RDRAND)" << endl;
	(ecxBits[31]) ? cout << "ECX bit 31: " << ecxBits[31] << ": [SUPPORTED] Hypervisor present (always zero on physical CPUs) - (Hypervisor)" << endl : cout << "ECX bit 31: " << ecxBits[31] << ": [UNSUPPORTED] Hypervisor present (always zero on physical CPUs) - (Hypervisor)" << endl;
	cout << endl;

	cout << "EAX=0x1: [EDX feature bits]" << endl;
	//cout << "EDX bit 0 = " << std::hex << "0x" << edxBits[0] << endl;
	(edxBits[0]) ? cout << "EDX bit 0: " << edxBits[0] << ": [SUPPORTED] Onboard x87 FPU - (FPU)" << endl : cout << "EDX bit 0: " << edxBits[0] << ": [UNSUPPORTED] Onboard x87 FPU - (FPU)" << endl;
	(edxBits[1]) ? cout << "EDX bit 1: " << edxBits[1] << ": [SUPPORTED] Virtual 8086 mode extensions (such as VIF, VIP, PVI) - (VME)" << endl : cout << "EDX bit 1: " << edxBits[1] << ": [UNSUPPORTED] Virtual 8086 mode extensions (such as VIF, VIP, PVI) - (VME)" << endl;
	(edxBits[2]) ? cout << "EDX bit 2: " << edxBits[2] << ": [SUPPORTED] Debugging extensions (CR4 bit 3) - (DE)" << endl : cout << "EDX bit 2: " << edxBits[2] << ": [UNSUPPORTED] Debugging extensions (CR4 bit 3) - (DE)" << endl;
	(edxBits[3]) ? cout << "EDX bit 3: " << edxBits[3] << ": [SUPPORTED] Page Size Extension (4 MB pages) - (PSE)" << endl : cout << "EDX bit 3: " << edxBits[3] << ": [UNSUPPORTED] Page Size Extension (4 MB pages) - (PSE)" << endl;
	(edxBits[4]) ? cout << "EDX bit 4: " << edxBits[4] << ": [SUPPORTED] Time Stamp Counter and RDTSC instruction - (TSC)" << endl : cout << "EDX bit 4: " << edxBits[4] << ": [UNSUPPORTED] Time Stamp Counter and RDTSC instruction - (TSC)" << endl;
	(edxBits[5]) ? cout << "EDX bit 5: " << edxBits[5] << ": [SUPPORTED] Model-specific registers and RDMSR/WRMSR instructions  - (MSR)" << endl : cout << "EDX bit 5: " << edxBits[5] << ": [UNSUPPORTED] Model-specific registers and RDMSR/WRMSR instructions  - (MSR)" << endl;
	(edxBits[6]) ? cout << "EDX bit 6: " << edxBits[6] << ": [SUPPORTED] Physical Address Extension - (PAE)" << endl : cout << "EDX bit 6: " << edxBits[6] << ": [UNSUPPORTED] Physical Address Extension - (PAE)" << endl;
	(edxBits[7]) ? cout << "EDX bit 7: " << edxBits[7] << ": [SUPPORTED] Machine Check Exception - (MCE)" << endl : cout << "EDX bit 7: " << edxBits[7] << ": [UNSUPPORTED] Machine Check Exception - (MCE)" << endl;
	(edxBits[8]) ? cout << "EDX bit 8: " << edxBits[8] << ": [SUPPORTED] CMPXCHG8B (compare-and-swap) instruction  - (CX8)" << endl : cout << "EDX bit 8: " << edxBits[8] << ": [UNSUPPORTED] CMPXCHG8B (compare-and-swap) instruction  - (CX8)" << endl;
	(edxBits[9]) ? cout << "EDX bit 9: " << edxBits[9] << ": [SUPPORTED] Onboard Advanced Programmable Interrupt Controller - (APIC)" << endl : cout << "EDX bit 9: " << edxBits[9] << ": [UNSUPPORTED] Onboard Advanced Programmable Interrupt Controller - (APIC)" << endl;
	(edxBits[10]) ? cout << "EDX bit 10: " << edxBits[10] << ": [SUPPORTED] Reserved" << endl : cout << "EDX bit 10: " << edxBits[10] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[11]) ? cout << "EDX bit 11: " << edxBits[11] << ": [SUPPORTED] SYSENTER and SYSEXIT fast system call instructions  - (SEP)" << endl : cout << "EDX bit 11: " << edxBits[11] << ": [UNSUPPORTED] SYSENTER and SYSEXIT fast system call instructions  - (SEP)" << endl;
	(edxBits[12]) ? cout << "EDX bit 12: " << edxBits[12] << ": [SUPPORTED] Memory Type Range Registers - (MTRR)" << endl : cout << "EDX bit 12: " << edxBits[12] << ": [UNSUPPORTED] Memory Type Range Registers - (MTRR)" << endl;
	(edxBits[13]) ? cout << "EDX bit 13: " << edxBits[13] << ": [SUPPORTED] Page Global Enable bit in CR4 - (PGE)" << endl : cout << "EDX bit 13: " << edxBits[13] << ": [UNSUPPORTED] Page Global Enable bit in CR4 - (PGE)" << endl;
	(edxBits[14]) ? cout << "EDX bit 14: " << edxBits[14] << ": [SUPPORTED] Machine Check Architecture - (MCA)" << endl : cout << "EDX bit 14: " << edxBits[14] << ": [UNSUPPORTED] Machine Check Architecture - (MCA)" << endl;
	(edxBits[15]) ? cout << "EDX bit 15: " << edxBits[15] << ": [SUPPORTED] Conditional move: CMOV, FCMOV and FCOMI instructions - (CMOV)" << endl : cout << "EDX bit 15: " << edxBits[15] << ": [UNSUPPORTED] Conditional move: CMOV, FCMOV and FCOMI instructions - (CMOV)" << endl;
	(edxBits[16]) ? cout << "EDX bit 16: " << edxBits[16] << ": [SUPPORTED] Page Attribute Table - (PAT)" << endl : cout << "EDX bit 16: " << edxBits[16] << ": [UNSUPPORTED] Page Attribute Table - (PAT)" << endl;
	(edxBits[17]) ? cout << "EDX bit 17: " << edxBits[17] << ": [SUPPORTED] 36-bit Page Size Extension - (PSE-36)" << endl : cout << "EDX bit 17: " << edxBits[17] << ": [UNSUPPORTED] 36-bit Page Size Extension - (PSE-36)" << endl;
	(edxBits[18]) ? cout << "EDX bit 18: " << edxBits[18] << ": [SUPPORTED] Processor Serial Number supported and enable - (PSN)" << endl : cout << "EDX bit 18: " << edxBits[18] << ": [UNSUPPORTED] Processor Serial Number supported and enable - (PSN)" << endl;
	(edxBits[19]) ? cout << "EDX bit 19: " << edxBits[19] << ": [SUPPORTED] CLFLUSH cache line flush instruction (SSE2)  - (CLFSH)" << endl : cout << "EDX bit 19: " << edxBits[19] << ": [UNSUPPORTED] CLFLUSH cache line flush instruction (SSE2)  - (CLFSH)" << endl;
	(edxBits[20]) ? cout << "EDX bit 20: " << edxBits[20] << ": [SUPPORTED] No-execute (NX) bit (Itanium only, reserved on other CPUs - (NX)" << endl : cout << "EDX bit 20: " << edxBits[20] << ": [UNSUPPORTED] No-execute (NX) bit (Itanium only, reserved on other CPUs - (NX)" << endl;
	(edxBits[21]) ? cout << "EDX bit 21: " << edxBits[21] << ": [SUPPORTED] Debug store: save trace of executed jumps - (DS)" << endl : cout << "EDX bit 21: " << edxBits[21] << ": [UNSUPPORTED] Debug store: save trace of executed jumps - (DS)" << endl;
	(edxBits[22]) ? cout << "EDX bit 22: " << edxBits[22] << ": [SUPPORTED] Onboard thermal control MSRs for ACPI - (ACPI)" << endl : cout << "EDX bit 22: " << edxBits[22] << ": [UNSUPPORTED] Onboard thermal control MSRs for ACPI - (ACPI)" << endl;
	(edxBits[23]) ? cout << "EDX bit 23: " << edxBits[23] << ": [SUPPORTED] MMX instructions (64-bit SIMD) - (MMX)" << endl : cout << "EDX bit 23: " << edxBits[23] << ": [UNSUPPORTED] MMX instructions (64-bit SIMD) - (MMX)" << endl;
	(edxBits[24]) ? cout << "EDX bit 24: " << edxBits[24] << ": [SUPPORTED] FXSAVE, FXRSTOR instructions, CR4 bit 9 - (FXSR)" << endl : cout << "EDX bit 24: " << edxBits[24] << ": [UNSUPPORTED] FXSAVE, FXRSTOR instructions, CR4 bit 9 - (FXSR)" << endl;
	(edxBits[25]) ? cout << "EDX bit 25: " << edxBits[25] << ": [SUPPORTED] Streaming SIMD Extensions (SSE) / Katmai New Instructions 128-bit SIMD - (SSE)" << endl : cout << "EDX bit 25: " << edxBits[25] << ": [UNSUPPORTED] Streaming SIMD Extensions (SSE) / Katmai New Instructions 128-bit SIMD - (SSE)" << endl;
	(edxBits[26]) ? cout << "EDX bit 26: " << edxBits[26] << ": [SUPPORTED] SSE2 instructions - (SSE2)" << endl : cout << "EDX bit 26: " << edxBits[26] << ": [UNSUPPORTED] SSE2 instructions - (SSE2)" << endl;
	(edxBits[27]) ? cout << "EDX bit 27: " << edxBits[27] << ": [SUPPORTED] CPU cache implements self-snoop - (SS)" << endl : cout << "EDX bit 27: " << edxBits[27] << ": [UNSUPPORTED] CPU cache implements self-snoop - (SS)" << endl;
	(edxBits[28]) ? cout << "EDX bit 28: " << edxBits[28] << ": [SUPPORTED] Max APIC IDs reserved field is Valid - (HTT)" << endl : cout << "EDX bit 28: " << edxBits[28] << ": [UNSUPPORTED] Max APIC IDs reserved field is Valid - (HTT)" << endl;
	(edxBits[29]) ? cout << "EDX bit 29: " << edxBits[29] << ": [SUPPORTED] Thermal monitor automatically limits temperature - (TM)" << endl : cout << "EDX bit 29: " << edxBits[29] << ": [UNSUPPORTED] Thermal monitor automatically limits temperature - (TM)" << endl;
	(edxBits[30]) ? cout << "EDX bit 30: " << edxBits[30] << ": [SUPPORTED] IA64 processor emulating x86 - (IA64)" << endl : cout << "EDX bit 30: " << edxBits[30] << ": [UNSUPPORTED] IA64 processor emulating x86 - (IA64)" << endl;
	(edxBits[31]) ? cout << "EDX bit 31: " << edxBits[31] << ": [SUPPORTED] Pending Break Enable (PBE# pin) wakeup capability - (PBE)" << endl : cout << "EDX bit 31: " << edxBits[31] << ": [UNSUPPORTED] Pending Break Enable (PBE# pin) wakeup capability - (PBE)" << endl;
	cout << endl;
	

	// EAX=0x2: Cache and TLB Descriptor Information
	CPUID cpuID2(0x2);
	eaxBits = bitset<32>(cpuID2.EAX());
	ebxBits = bitset<32>(cpuID2.EBX());
	ecxBits = bitset<32>(cpuID2.ECX());
	edxBits = bitset<32>(cpuID2.EDX());

	if (eaxBits[31])
	{
		cout << "EAX=0x2: [Cache and TLB Descriptor Information (EAX) = Invalid Descriptors / No valid information.]" << endl;
	}
	else
	{
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX) = " << std::hex << "0x" << cpuID2.EAX() << endl;
		cout << "EAX=0x2: [Cache and TLB Descriptor Information (EAX)] = " << eaxBits << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) - Number of times to query CPUID with 0x2 (should be 1) = " << eaxBits[7] << eaxBits[6] << eaxBits[5] << eaxBits[4] << eaxBits[3] << eaxBits[2] << eaxBits[1] << eaxBits[0] << endl;
		int descriptorEAX0 = extractBits(cpuID2.EAX(), 0, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) - Number of times to query CPUID with 0x2 (should be 1) = " << std::hex << "0x" << descriptorEAX0 << endl;
		//string descriptorEAX0String = getCacheAndTableDescriptor(descriptorEAX0);
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) = " << descriptorEAX0String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 1) = " << eaxBits[15] << eaxBits[14] << eaxBits[13] << eaxBits[12] << eaxBits[11] << eaxBits[10] << eaxBits[9] << eaxBits[8] << endl;
		int descriptorEAX1 = extractBits(cpuID2.EAX(), 8, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 1) = " << std::hex << "0x" << descriptorEAX1 << endl;
		string descriptorEAX1String = getCacheAndTableDescriptor(descriptorEAX1);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 1) = " << descriptorEAX1String << endl;
		
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 2) = " << eaxBits[23] << eaxBits[22] << eaxBits[21] << eaxBits[20] << eaxBits[19] << eaxBits[18] << eaxBits[17] << eaxBits[16] << endl;
		int descriptorEAX2 = extractBits(cpuID2.EAX(), 16, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 2) = " << std::hex << "0x" << descriptorEAX2 << endl;
		string descriptorEAX2String = getCacheAndTableDescriptor(descriptorEAX2);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 2) = " << descriptorEAX2String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 3) = " << eaxBits[31] << eaxBits[30] << eaxBits[29] << eaxBits[28] << eaxBits[27] << eaxBits[26] << eaxBits[25] << eaxBits[24] << endl;
		int descriptorEAX3 = extractBits(cpuID2.EAX(), 24, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 3) = " << std::hex << "0x" << descriptorEAX3 << endl;
		string descriptorEAX3String = getCacheAndTableDescriptor(descriptorEAX3);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 3) = " << descriptorEAX3String << endl;
	}
	cout << endl;
	
	if (ebxBits[31])
	{
		cout << "EAX=0x2: [Cache and TLB Descriptor Information (EBX) = Invalid Descriptors / No valid information.]" << endl;
	}
	else
	{
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX) = " << std::hex << "0x" << cpuID2.EBX() << endl;
		cout << "EAX=0x2: [Cache and TLB Descriptor Information (EBX)] = " << ebxBits << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 0) = " << ebxBits[7] << ebxBits[6] << ebxBits[5] << ebxBits[4] << ebxBits[3] << ebxBits[2] << ebxBits[1] << ebxBits[0] << endl;
		int descriptorEBX0 = extractBits(cpuID2.EBX(), 0, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 0) = " << std::hex << "0x" << descriptorEBX0 << endl;
		string descriptorEBX0String = getCacheAndTableDescriptor(descriptorEBX0);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 0) = " << descriptorEBX0String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 1) = " << ebxBits[15] << ebxBits[14] << ebxBits[13] << ebxBits[12] << ebxBits[11] << ebxBits[10] << ebxBits[9] << ebxBits[8] << endl;
		int descriptorEBX1 = extractBits(cpuID2.EBX(), 8, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 1) = " << std::hex << "0x" << descriptorEBX1 << endl;
		string descriptorEBX1String = getCacheAndTableDescriptor(descriptorEBX1);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 1) = " << descriptorEBX1String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 2) = " << ebxBits[23] << ebxBits[22] << ebxBits[21] << ebxBits[20] << ebxBits[19] << ebxBits[18] << ebxBits[17] << ebxBits[16] << endl;
		int descriptorEBX2 = extractBits(cpuID2.EBX(), 16, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 2) = " << std::hex << "0x" << descriptorEBX2 << endl;
		string descriptorEBX2String = getCacheAndTableDescriptor(descriptorEBX2);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 2) = " << descriptorEBX2String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 3) = " << ebxBits[31] << ebxBits[30] << ebxBits[29] << ebxBits[28] << ebxBits[27] << ebxBits[26] << ebxBits[25] << ebxBits[24] << endl;
		int descriptorEBX3 = extractBits(cpuID2.EBX(), 24, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 3) = " << std::hex << "0x" << descriptorEBX3 << endl;
		string descriptorEBX3String = getCacheAndTableDescriptor(descriptorEBX3);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX byte 3) = " << descriptorEBX3String << endl;
	}
	cout << endl;

	if (ecxBits[31])
	{
		cout << "EAX=0x2: [Cache and TLB Descriptor Information (ECX) = Invalid Descriptors / No valid information.]" << endl;
	}
	else
	{
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX) = " << std::hex << "0x" << cpuID2.ECX() << endl;
		cout << "EAX=0x2: [Cache and TLB Descriptor Information (ECX)] = " << ecxBits << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 0) = " << ecxBits[7] << ecxBits[6] << ecxBits[5] << ecxBits[4] << ecxBits[3] << ecxBits[2] << ecxBits[1] << ecxBits[0] << endl;
		int descriptorECX0 = extractBits(cpuID2.ECX(), 0, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 0) = " << std::hex << "0x" << descriptorECX0 << endl;
		string descriptorECX0String = getCacheAndTableDescriptor(descriptorECX0);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 0) = " << descriptorECX0String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 1) = " << ecxBits[15] << ecxBits[14] << ecxBits[13] << ecxBits[12] << ecxBits[11] << ecxBits[10] << ecxBits[9] << ecxBits[8] << endl;
		int descriptorECX1 = extractBits(cpuID2.ECX(), 8, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 1) = " << std::hex << "0x" << descriptorECX1 << endl;
		string descriptorECX1String = getCacheAndTableDescriptor(descriptorECX1);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 1) = " << descriptorECX1String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 2) = " << ecxBits[23] << ecxBits[22] << ecxBits[21] << ecxBits[20] << ecxBits[19] << ecxBits[18] << ecxBits[17] << ecxBits[16] << endl;
		int descriptorECX2 = extractBits(cpuID2.ECX(), 16, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 2) = " << std::hex << "0x" << descriptorECX2 << endl;
		string descriptorECX2String = getCacheAndTableDescriptor(descriptorECX2);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 2) = " << descriptorECX2String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 3) = " << ecxBits[31] << ecxBits[30] << ecxBits[29] << ecxBits[28] << ecxBits[27] << ecxBits[26] << ecxBits[25] << ecxBits[24] << endl;
		int descriptorECX3 = extractBits(cpuID2.ECX(), 24, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 3) = " << std::hex << "0x" << descriptorECX3 << endl;
		string descriptorECX3String = getCacheAndTableDescriptor(descriptorECX3);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX byte 3) = " << descriptorECX3String << endl;
	}
	cout << endl;

	if (edxBits[31])
	{
		cout << "EAX=0x2: [Cache and TLB Descriptor Information (EDX) = Invalid Descriptors / No valid information.]" << endl;
	}
	else
	{
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX) = " << std::hex << "0x" << cpuID2.EDX() << endl;
		cout << "EAX=0x2: [Cache and TLB Descriptor Information (EDX)] = " << edxBits << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 0) = " << edxBits[7] << edxBits[6] << edxBits[5] << edxBits[4] << edxBits[3] << edxBits[2] << edxBits[1] << edxBits[0] << endl;
		int descriptorEDX0 = extractBits(cpuID2.EDX(), 0, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 0) = " << std::hex << "0x" << descriptorEDX0 << endl;
		string descriptorEDX0String = getCacheAndTableDescriptor(descriptorEDX0);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 0) = " << descriptorEDX0String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 1) = " << edxBits[15] << edxBits[14] << edxBits[13] << edxBits[12] << edxBits[11] << edxBits[10] << edxBits[9] << edxBits[8] << endl;
		int descriptorEDX1 = extractBits(cpuID2.EDX(), 8, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 1) = " << std::hex << "0x" << descriptorEDX1 << endl;
		string descriptorEDX1String = getCacheAndTableDescriptor(descriptorEDX1);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 1) = " << descriptorEDX1String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 2) = " << edxBits[23] << edxBits[22] << edxBits[21] << edxBits[20] << edxBits[19] << edxBits[18] << edxBits[17] << edxBits[16] << endl;
		int descriptorEDX2 = extractBits(cpuID2.EDX(), 16, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 2) = " << std::hex << "0x" << descriptorEDX2 << endl;
		string descriptorEDX2String = getCacheAndTableDescriptor(descriptorEDX2);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 2) = " << descriptorEDX2String << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 3) = " << edxBits[31] << edxBits[30] << edxBits[29] << edxBits[28] << edxBits[27] << edxBits[26] << edxBits[25] << edxBits[24] << endl;
		int descriptorEDX3 = extractBits(cpuID2.EDX(), 24, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 3) = " << std::hex << "0x" << descriptorEDX3 << endl;
		string descriptorEDX3String = getCacheAndTableDescriptor(descriptorEDX3);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX byte 3) = " << descriptorEDX3String << endl;
	}
	cout << endl;

	// EAX=0x3: Processor Serial Number
	CPUID cpuID3(0x3);
	eaxBits = bitset<32>(cpuID3.EAX());
	ebxBits = bitset<32>(cpuID3.EBX());
	ecxBits = bitset<32>(cpuID3.ECX());
	edxBits = bitset<32>(cpuID3.EDX());

	cout << "EAX=0x3: Processor Serial Number (PSN) Information:" << endl;
	cout << "EAX=0x3: [EAX] = " << eaxBits << endl;
	cout << "EAX=0x3: [EBX] = " << ebxBits << endl;
	cout << "EAX=0x3: [ECX] = " << ecxBits << endl;
	cout << "EAX=0x3: [EDX] = " << edxBits << endl;
	cout << "EAX=0x3: PSN [EAX=0x1:EDX:ECX] (Pentium 3 CPUs - 96-bit) = " << std::hex << ZeroPadNumber(eaxBits1.to_ulong()) << ":" << std::hex << ZeroPadNumber(edxBits.to_ulong()) << ":" << std::hex << ZeroPadNumber(ecxBits.to_ulong()) << endl;
	cout << "EAX=0x3: PSN [EAX:EBX:ECX:EDX] (Transmeta Crusoe and Efficeon CPUs - 128-bit) = " << std::hex << ZeroPadNumber(eaxBits.to_ulong()) << ":" << std::hex << ZeroPadNumber(ebxBits.to_ulong()) << ":" << std::hex << ZeroPadNumber(ecxBits.to_ulong()) << ":" << std::hex << ZeroPadNumber(edxBits.to_ulong()) << endl;
	cout << endl;

	// EAX=4 and EAX=8000'001Dh: Cache Hierarchy and Topology
	CPUID cpuID4(0x4); // Intel
	eaxBits = bitset<32>(cpuID4.EAX());
	ebxBits = bitset<32>(cpuID4.EBX());
	ecxBits = bitset<32>(cpuID4.ECX());
	edxBits = bitset<32>(cpuID4.EDX());
	cout << "EAX=0x4: Cache Hierarchy and Topology Information (Intel):" << endl;
	cout << "EAX=0x4: [EAX] = " << eaxBits << endl;
	cout << "EAX=0x4: [EBX] = " << ebxBits << endl;
	cout << "EAX=0x4: [ECX] = " << ecxBits << endl;
	cout << "EAX=0x4: [EDX] = " << edxBits << endl;
	cout << endl;

	CPUID cpuID8000001D(0x8000001D); // AMD
	eaxBits = bitset<32>(cpuID8000001D.EAX());
	ebxBits = bitset<32>(cpuID8000001D.EBX());
	ecxBits = bitset<32>(cpuID8000001D.ECX());
	edxBits = bitset<32>(cpuID8000001D.EDX());
	cout << "EAX=0x8000001D: Cache Hierarchy and Topology Information (AMD):" << endl;
	cout << "EAX=0x8000001D: [EAX] = " << eaxBits << endl;
	cout << "EAX=0x8000001D: [EBX] = " << ebxBits << endl;
	cout << "EAX=0x8000001D: [ECX] = " << ecxBits << endl;
	cout << "EAX=0x8000001D: [EDX] = " << edxBits << endl;
	cout << endl;

	// EAX=4 and EAX=Bh: Intel Thread/Core and Cache Topology
	CPUID cpuIDB(0xB); // Intel
	eaxBits = bitset<32>(cpuIDB.EAX());
	ebxBits = bitset<32>(cpuIDB.EBX());
	ecxBits = bitset<32>(cpuIDB.ECX());
	edxBits = bitset<32>(cpuIDB.EDX());
	cout << "EAX=0xB: Intel Thread/Core and Cache Topology:" << endl;
	cout << "EAX=0xB: [EAX] = " << eaxBits << endl;
	cout << "EAX=0xB: [EBX] = " << ebxBits << endl;
	cout << "EAX=0xB: [ECX] = " << ecxBits << endl;
	cout << "EAX=0xB: [EDX] = " << edxBits << endl;
	cout << endl;

	// EAX=5: MONITOR/MWAIT Features
	CPUID cpuID5(0x5);
	eaxBits = bitset<32>(cpuID5.EAX());
	ebxBits = bitset<32>(cpuID5.EBX());
	ecxBits = bitset<32>(cpuID5.ECX());
	edxBits = bitset<32>(cpuID5.EDX());
	cout << "EAX=0x5: MONITOR/MWAIT Features:" << endl;
	cout << "EAX=0x5: [EAX] = " << eaxBits << endl;
	cout << "EAX=0x5: [EBX] = " << ebxBits << endl;
	cout << "EAX=0x5: [ECX] = " << ecxBits << endl;
	cout << "EAX=0x5: [EDX] = " << edxBits << endl;
	cout << endl;

	// EAX=6: Thermal and Power Management
	CPUID cpuID6(0x6);
	eaxBits = bitset<32>(cpuID6.EAX());
	ebxBits = bitset<32>(cpuID6.EBX());
	ecxBits = bitset<32>(cpuID6.ECX());
	edxBits = bitset<32>(cpuID6.EDX());
	cout << "EAX=0x6: Thermal and Power Management:" << endl;
	cout << "EAX=0x6: [EAX] = " << eaxBits << endl;
	cout << "EAX=0x6: [EBX] = " << ebxBits << endl;
	cout << "EAX=0x6: [ECX] = " << ecxBits << endl;
	cout << "EAX=0x6: [EDX] = " << edxBits << endl;
	cout << endl;

	// EAX=7, ECX=0: Extended Features
	// EAX=7, ECX=1: Extended Features
	// EAX=7, ECX=2: Extended Features
	CPUID cpuID7(0x7);
	eaxBits = bitset<32>(cpuID7.EAX());
	ebxBits = bitset<32>(cpuID7.EBX());
	ecxBits = bitset<32>(cpuID7.ECX());
	edxBits = bitset<32>(cpuID7.EDX());
	cout << "EAX=0x7: Extended Features:" << endl;
	cout << "EAX=0x7: [EAX] = " << eaxBits << endl;
	cout << "EAX=0x7: [EBX] = " << ebxBits << endl;
	cout << "EAX=0x7: [ECX] = " << ecxBits << endl;
	cout << "EAX=0x7: [EDX] = " << edxBits << endl;
	cout << endl;

	// EAX=0Dh: XSAVE Features and State Components
	CPUID cpuIDD(0xD);
	eaxBits = bitset<32>(cpuIDD.EAX());
	ebxBits = bitset<32>(cpuIDD.EBX());
	ecxBits = bitset<32>(cpuIDD.ECX());
	edxBits = bitset<32>(cpuIDD.EDX());
	cout << "EAX=0xD: XSAVE Features and State Components:" << endl;
	cout << "EAX=0xD: [EAX] = " << eaxBits << endl;
	cout << "EAX=0xD: [EBX] = " << ebxBits << endl;
	cout << "EAX=0xD: [ECX] = " << ecxBits << endl;
	cout << "EAX=0xD: [EDX] = " << edxBits << endl;
	cout << endl;

	// EAX=12h: SGX Capabilities
	CPUID cpuID12(0x12);
	eaxBits = bitset<32>(cpuID12.EAX());
	ebxBits = bitset<32>(cpuID12.EBX());
	ecxBits = bitset<32>(cpuID12.ECX());
	edxBits = bitset<32>(cpuID12.EDX());
	cout << "EAX=0x12: SGX Capabilities:" << endl;
	cout << "EAX=0x12: [EAX] = " << eaxBits << endl;
	cout << "EAX=0x12: [EBX] = " << ebxBits << endl;
	cout << "EAX=0x12: [ECX] = " << ecxBits << endl;
	cout << "EAX=0x12: [EDX] = " << edxBits << endl;
	cout << endl;

	// EAX=14h: Processor Trace
	CPUID cpuID14(0x14);
	eaxBits = bitset<32>(cpuID14.EAX());
	ebxBits = bitset<32>(cpuID14.EBX());
	ecxBits = bitset<32>(cpuID14.ECX());
	edxBits = bitset<32>(cpuID14.EDX());
	cout << "EAX=0x14: Processor Trace:" << endl;
	cout << "EAX=0x14: [EAX] = " << eaxBits << endl;
	cout << "EAX=0x14: [EBX] = " << ebxBits << endl;
	cout << "EAX=0x14: [ECX] = " << ecxBits << endl;
	cout << "EAX=0x14: [EDX] = " << edxBits << endl;
	cout << endl;

	// EAX = 15h and EAX = 16h: CPU, TSC, Bus and Core Crystal Clock Frequencies
	CPUID cpuID15(0x15);
	eaxBits = bitset<32>(cpuID15.EAX());
	ebxBits = bitset<32>(cpuID15.EBX());
	ecxBits = bitset<32>(cpuID15.ECX());
	edxBits = bitset<32>(cpuID15.EDX());

	cout << "EAX=0x15: TSC and Core Crystal frequency information :" << endl;
	cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator (EAX) = " << std::hex << "0x" << eaxBits << endl;
	cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator (EAX) = " << eaxBits << endl;
	cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator (EBX) = " << std::hex << "0x" << ebxBits << endl;
	cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator (EBX) = " << ebxBits << endl;
	cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz (ECX) = " << std::hex << "0x" << ecxBits << endl;
	cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz (ECX) = " << ecxBits << endl;
	cout << "EAX=0x15: TSC frequency, in units of Hz (EDX) = " << std::hex << "0x" << edxBits << endl;
	cout << "EAX=0x15: TSC frequency, in units of Hz (EDX) = " << edxBits << endl;
	cout << endl;

	CPUID cpuID16(0x16);
	eaxBits = bitset<32>(cpuID16.EAX());
	ebxBits = bitset<32>(cpuID16.EBX());
	ecxBits = bitset<32>(cpuID16.ECX());
	edxBits = bitset<32>(cpuID16.EDX());

	cout << "EAX=0x16: Processor and Bus specification frequencies:" << endl;
	cout << "EAX=0x16: Processor Base Frequency (in MHz): EAX Bits 15:0 = " << std::hex << "0x" << extractBits(cpuID16.EAX(), 15, 0) << endl;
	cout << "EAX=0x16: Processor Base Frequency (in MHz): EAX Bits 15:0 = " << eaxBits << endl;
	cout << "EAX=0x16: Processor Maximum Frequency (in MHz): EBX Bits 15:0 = " << std::hex << "0x" << extractBits(cpuID16.EBX(), 15, 0) << endl;
	cout << "EAX=0x16: Processor Maximum Frequency (in MHz): EBX Bits 15:0 = " << ebxBits << endl;
	cout << "EAX=0x16: Bus/Reference frequency (in MHz): ECX Bits 15:0 = " << std::hex << "0x" << extractBits(cpuID16.ECX(), 15, 0) << endl;
	cout << "EAX=0x16: Bus/Reference frequency (in MHz): ECX Bits 15:0 = " << ecxBits << endl;
	cout << "EAX=0x16: Reserved: EDX = " << std::hex << "0x" << cpuID16.EDX() << endl;
	cout << "EAX=0x16: Reserved: EDX = " << edxBits << endl;
	cout << endl;







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


