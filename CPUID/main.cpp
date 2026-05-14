#include "CPUID.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

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
			description = "2 Data TLBs: 2 MByte/4 MByte pages, 4-way set associative, 4 entries and 1 GByte pages, fully associative, 32 entries";
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
			description = "Two Level-2 shared TLBs: 4 KByte / 2 MByte pages, 6-way set associative, 1536 entries and 1 GByte pages, 4-way set associative, 16 entries";
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

	// TODO: Add more cases for other cache descriptors
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

	/*
	switch (cpuID.EAX())
	{
		case 0x01:
		    cout << "Later Intel 486 and Pentium. Extended: Not Implemented" << endl;
		    break;
		case 0x02:
			cout << "Pentium Pro, Pentium II and Celeron. Extended: Not Implemented" << endl;
			break;
		case 0x03:
			cout << "Pentium III. Extended: Not Implemented" << endl;
			break;
		case 0x04:
			cout << "Pentium 4. Extended: Not Implemented" << endl;
			break;
	}
	*/




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
	

	//cout << "EAX=1: Feature Bits: EDX = " << std::hex << "0x" << cpuID1.EDX() << endl;
	cout << "EAX=0x1: Feature Bits: EDX = " << edxBits << endl;
	//cout << "EAX=1: Feature Bits: ECX = " << std::hex << "0x" << cpuID1.ECX() << endl;
	cout << "EAX=0x1: Feature Bits: ECX = " << ecxBits << endl;
	//cout << "EAX=1: Additional Information: EBX = " << std::hex << "0x" << cpuID1.EBX() << endl;
	cout << "EAX=0x1: Additional Information: EBX = " << bitset<32>(cpuID1.EBX()) << endl;
	//cout << "EAX=1: Processor Family IDs: EAX = " << std::hex << "0x" << cpuID1.EAX() << endl;
	cout << "EAX=0x1: Processor Family IDs: EAX = " << bitset<32>(cpuID1.EAX()) << endl;
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



	cout << "EAX=0x1: EBX Additional Information" << endl;
	cout << "EBX bits 7:0 Brand Index = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 0, 8) << endl;
	cout << "EBX bits 15:8 CLFLUSH line size (Value * 8 = cache line size in bytes) = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 8, 8) << endl;
	cout << "EBX bits 23:16 Maximum number of addressable IDs for logical processors in this physical package = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 16, 8) << endl;
	cout << "EBX bits 31:24 Local APIC ID: The initial APIC-ID is used to identify the executing logical processor = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 24, 8) << endl;
	cout << endl;



	cout << "EAX=0x1: ECX feature bits" << endl;
	(ecxBits[0]) ? cout << "ECX bit 0: " << ecxBits[0] << ": SSE3 (Prescott New Instructions - PNI) - (SSE3) is supported" << endl : cout << "ECX bit 0: " << ecxBits[0] << ": SSE3 (Prescott New Instructions - PNI) - (SSE3) is not supported" << endl;
	(ecxBits[1]) ? cout << "ECX bit 1: " << ecxBits[1] << ": PCLMULQDQ (carry-less multiply) instruction - (PCLMULQDQ) is supported" << endl : cout << "ECX bit 1: " << ecxBits[1] << ": PCLMULQDQ (carry-less multiply) instruction - (PCLMULQDQ) is not supported" << endl;
	(ecxBits[2]) ? cout << "ECX bit 2: " << ecxBits[2] << ": 64-bit debug store (edx bit 21) - (DTES64) is supported" << endl : cout << "ECX bit 2: " << ecxBits[2] << ": 64-bit debug store (edx bit 21) - (DTES64) is not supported" << endl;
	(ecxBits[3]) ? cout << "ECX bit 3: " << ecxBits[3] << ": MONITOR and MWAIT instructions (PNI) - (MONITOR) is supported" << endl : cout << "ECX bit 3: " << ecxBits[3] << ": MONITOR and MWAIT instructions (PNI) - (MONITOR) is not supported" << endl;
	(ecxBits[4]) ? cout << "ECX bit 4: " << ecxBits[4] << ": CPL qualified debug store - (DS-CPL) is supported" << endl : cout << "ECX bit 4: " << ecxBits[4] << ": CPL qualified debug store - (DS-CPL) is not supported" << endl;
	(ecxBits[5]) ? cout << "ECX bit 5: " << ecxBits[5] << ": Virtual Machine eXtensions - (VMX) is supported" << endl : cout << "ECX bit 5: " << ecxBits[5] << ": Virtual Machine eXtensions - (VMX) is not supported" << endl;
	(ecxBits[6]) ? cout << "ECX bit 6: " << ecxBits[6] << ": Safer Mode Extensions (LaGrande) (GETSEC instruction) - (SMX) is supported" << endl : cout << "ECX bit 6: " << ecxBits[6] << ": Safer Mode Extensions (LaGrande) (GETSEC instruction) - (SMX) is not supported" << endl;
	(ecxBits[7]) ? cout << "ECX bit 7: " << ecxBits[7] << ": Enhanced SpeedStep - (EST) is supported" << endl : cout << "ECX bit 7: " << ecxBits[7] << ": Enhanced SpeedStep - (EST) is not supported" << endl;
	(ecxBits[8]) ? cout << "ECX bit 8: " << ecxBits[8] << ": Thermal Monitor 2 - (TM2) is supported" << endl : cout << "ECX bit 8: " << ecxBits[8] << ": Thermal Monitor 2 - (TM2) is not supported" << endl;
	(ecxBits[9]) ? cout << "ECX bit 9: " << ecxBits[9] << ": Supplemental SSE3 instructions - (SSSE3) is supported" << endl : cout << "ECX bit 9: " << ecxBits[9] << ": Supplemental SSE3 instructions - (SSSE3) is not supported" << endl;
	(ecxBits[10]) ? cout << "ECX bit 10: " << ecxBits[10] << ": L1 Context ID - (CNXT-ID) is supported" << endl : cout << "ECX bit 10: " << ecxBits[10] << ": L1 Context ID - (CNXT-ID) is not supported" << endl;
	(ecxBits[11]) ? cout << "ECX bit 11: " << ecxBits[11] << ": Silicon Debug interface - (SDBG) is supported" << endl : cout << "ECX bit 11: " << ecxBits[11] << ": Silicon Debug interface - (SDBG) is not supported" << endl;
	(ecxBits[12]) ? cout << "ECX bit 12: " << ecxBits[12] << ": Fused multiply-add (FMA3) - (FMA) is supported" << endl : cout << "ECX bit 12: " << ecxBits[12] << ": Fused multiply-add (FMA3) - (FMA) is not supported" << endl;
	(ecxBits[13]) ? cout << "ECX bit 13: " << ecxBits[13] << ": CMPXCHG16B instruction - (CMPXCHG16B) is supported" << endl : cout << "ECX bit 13: " << ecxBits[13] << ": CMPXCHG16B instruction - (CMPXCHG16B) is not supported" << endl;
	(ecxBits[14]) ? cout << "ECX bit 14: " << ecxBits[14] << ": Can disable sending task priority messages - (xTPR Update Control) is supported" << endl : cout << "ECX bit 14: " << ecxBits[14] << ": Can disable sending task priority messages - (xTPR Update Control) is not supported" << endl;
	(ecxBits[15]) ? cout << "ECX bit 15: " << ecxBits[15] << ": Perfmon & debug capability - (PDCM) is supported" << endl : cout << "ECX bit 15: " << ecxBits[15] << ": Perfmon & debug capability - (PDCM) is not supported" << endl;
	(ecxBits[16]) ? cout << "ECX bit 16: " << ecxBits[16] << ": Reserved" << endl : cout << "ECX bit 16: " << ecxBits[16] << ": Reserved" << endl;
	(ecxBits[17]) ? cout << "ECX bit 17: " << ecxBits[17] << ": Process context identifiers (CR4 bit 17) - (PCID) is supported" << endl : cout << "ECX bit 17: " << ecxBits[17] << ": Process context identifiers (CR4 bit 17) - (PCID) is not supported" << endl;
	(ecxBits[18]) ? cout << "ECX bit 18: " << ecxBits[18] << ": Direct cache access for DMA writes - (DCA) is supported" << endl : cout << "ECX bit 18: " << ecxBits[18] << ": Direct cache access for DMA writes - (DCA) is not supported" << endl;
	(ecxBits[19]) ? cout << "ECX bit 19: " << ecxBits[19] << ": SSE4.1 instructions - (SSE4.1) is supported" << endl : cout << "ECX bit 19: " << ecxBits[19] << ": SSE4.1 instructions - (SSE4.1) is not supported" << endl;
	(ecxBits[20]) ? cout << "ECX bit 20: " << ecxBits[20] << ": SSE4.2 instructions - (SSE4.2) is supported" << endl : cout << "ECX bit 20: " << ecxBits[20] << ": SSE4.2 instructions - (SSE4.2) is not supported" << endl;
	(ecxBits[21]) ? cout << "ECX bit 21: " << ecxBits[21] << ": x2APIC (enhanced APIC) - (X2APIC) is supported" << endl : cout << "ECX bit 21: " << ecxBits[21] << ": x2APIC (enhanced APIC) - (X2APIC) is not supported" << endl;
	(ecxBits[22]) ? cout << "ECX bit 22: " << ecxBits[22] << ": MOVBE instruction (big-endian) - (MOVBE) is supported" << endl : cout << "ECX bit 22: " << ecxBits[22] << ": MOVBE instruction (big-endian) - (MOVBE) is not supported" << endl;
	(ecxBits[23]) ? cout << "ECX bit 23: " << ecxBits[23] << ": POPCNT instruction - (POPCNT) is supported" << endl : cout << "ECX bit 23: " << ecxBits[23] << ": POPCNT instruction - (POPCNT) is not supported" << endl;
	(ecxBits[24]) ? cout << "ECX bit 24: " << ecxBits[24] << ": APIC implements one-shot operation using a TSC deadline value - (TSC-Deadline) is supported" << endl : cout << "ECX bit 24: " << ecxBits[24] << ": APIC implements one-shot operation using a TSC deadline value - (TSC-Deadline) is not supported" << endl;
	(ecxBits[25]) ? cout << "ECX bit 25: " << ecxBits[25] << ": AES instruction set - (AES-NI) is supported" << endl : cout << "ECX bit 25: " << ecxBits[25] << ": AES instruction set - (AES-NI) is not supported" << endl;
	(ecxBits[26]) ? cout << "ECX bit 26: " << ecxBits[26] << ": Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions - (XSAVE) is supported" << endl : cout << "ECX bit 26: " << ecxBits[26] << ": Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions - (XSAVE) is not supported" << endl;
	(ecxBits[27]) ? cout << "ECX bit 27: " << ecxBits[27] << ": XSAVE enabled by OS - (OSXSAVE) is supported" << endl : cout << "ECX bit 27: " << ecxBits[27] << ": XSAVE enabled by OS - (OSXSAVE) is not supported" << endl;
	(ecxBits[28]) ? cout << "ECX bit 28: " << ecxBits[28] << ": Advanced Vector Extensions (256-bit SIMD) - (AVX) is supported" << endl : cout << "ECX bit 28: " << ecxBits[28] << ": Advanced Vector Extensions (256-bit SIMD) - (AVX) is not supported" << endl;
	(ecxBits[29]) ? cout << "ECX bit 29: " << ecxBits[29] << ": Floating-point conversion instructions to/from FP16 format - (F16C) is supported" << endl : cout << "ECX bit 29: " << ecxBits[29] << ": Floating-point conversion instructions to/from FP16 format - (F16C) is not supported" << endl;
	(ecxBits[30]) ? cout << "ECX bit 30: " << ecxBits[30] << ": RDRAND (on-chip random number generator) feature - (RDRAND) is supported" << endl : cout << "ECX bit 30: " << ecxBits[30] << ": RDRAND (on-chip random number generator) feature - (RDRAND) is not supported" << endl;
	(ecxBits[31]) ? cout << "ECX bit 31: " << ecxBits[31] << ": Hypervisor present (always zero on physical CPUs) - (Hypervisor) is supported" << endl : cout << "ECX bit 31: " << ecxBits[31] << ": Hypervisor present (always zero on physical CPUs) - (Hypervisor) is not supported" << endl;
	cout << endl;



	cout << "EAX=0x1: EDX feature bits" << endl;
	//cout << "EDX bit 0 = " << std::hex << "0x" << edxBits[0] << endl;
	(edxBits[0]) ? cout << "EDX bit 0: " << edxBits[0] << ": Onboard x87 FPU - (FPU) is supported" << endl : cout << "EDX bit 0: " << edxBits[0] << ": Onboard x87 FPU - (FPU) is not supported" << endl;
	(edxBits[1]) ? cout << "EDX bit 1: " << edxBits[1] << ": Virtual 8086 mode extensions (such as VIF, VIP, PVI) - (VME) is supported" << endl : cout << "EDX bit 1: " << edxBits[1] << ": Virtual 8086 mode extensions (such as VIF, VIP, PVI) - (VME) is not supported" << endl;
	(edxBits[2]) ? cout << "EDX bit 2: " << edxBits[2] << ": Debugging extensions (CR4 bit 3) - (DE) is supported" << endl : cout << "EDX bit 2: " << edxBits[2] << ": Debugging extensions (CR4 bit 3) - (DE) is not supported" << endl;
	(edxBits[3]) ? cout << "EDX bit 3: " << edxBits[3] << ": Page Size Extension (4 MB pages) - (PSE) is supported" << endl : cout << "EDX bit 3: " << edxBits[3] << ": Page Size Extension (4 MB pages) - (PSE) is not supported" << endl;
	(edxBits[4]) ? cout << "EDX bit 4: " << edxBits[4] << ": Time Stamp Counter and RDTSC instruction - (TSC) is supported" << endl : cout << "EDX bit 4: " << edxBits[4] << ": Time Stamp Counter and RDTSC instruction - (TSC) is not supported" << endl;
	(edxBits[5]) ? cout << "EDX bit 5: " << edxBits[5] << ": Model-specific registers and RDMSR/WRMSR instructions  - (MSR) is supported" << endl : cout << "EDX bit 5: " << edxBits[5] << ": Model-specific registers and RDMSR/WRMSR instructions  - (MSR) is not supported" << endl;
	(edxBits[6]) ? cout << "EDX bit 6: " << edxBits[6] << ": Physical Address Extension - (PAE) is supported" << endl : cout << "EDX bit 6: " << edxBits[6] << ": Physical Address Extension - (PAE) is not supported" << endl;
	(edxBits[7]) ? cout << "EDX bit 7: " << edxBits[7] << ": Machine Check Exception - (MCE) is supported" << endl : cout << "EDX bit 7: " << edxBits[7] << ": Machine Check Exception - (MCE) is not supported" << endl;
	(edxBits[8]) ? cout << "EDX bit 8: " << edxBits[8] << ": CMPXCHG8B (compare-and-swap) instruction  - (CX8) is supported" << endl : cout << "EDX bit 8: " << edxBits[8] << ": CMPXCHG8B (compare-and-swap) instruction  - (CX8) is not supported" << endl;
	(edxBits[9]) ? cout << "EDX bit 9: " << edxBits[9] << ": Onboard Advanced Programmable Interrupt Controller - (APIC) is supported" << endl : cout << "EDX bit 9: " << edxBits[9] << ": Onboard Advanced Programmable Interrupt Controller - (APIC) is not supported" << endl;
	(edxBits[10]) ? cout << "EDX bit 10: " << edxBits[10] << ": Reserved" << endl : cout << "EDX bit 10: " << edxBits[10] << ": Reserved" << endl;
	(edxBits[11]) ? cout << "EDX bit 11: " << edxBits[11] << ": SYSENTER and SYSEXIT fast system call instructions  - (SEP) is supported" << endl : cout << "EDX bit 11: " << edxBits[11] << ": SYSENTER and SYSEXIT fast system call instructions  - (SEP) is not supported" << endl;
	(edxBits[12]) ? cout << "EDX bit 12: " << edxBits[12] << ": Memory Type Range Registers - (MTRR) is supported" << endl : cout << "EDX bit 12: " << edxBits[12] << ": Memory Type Range Registers - (MTRR) is not supported" << endl;
	(edxBits[13]) ? cout << "EDX bit 13: " << edxBits[13] << ": Page Global Enable bit in CR4 - (PGE) is supported" << endl : cout << "EDX bit 13: " << edxBits[13] << ": Page Global Enable bit in CR4 - (PGE) is not supported" << endl;
	(edxBits[14]) ? cout << "EDX bit 14: " << edxBits[14] << ": Machine Check Architecture - (MCA) is supported" << endl : cout << "EDX bit 14: " << edxBits[14] << ": Machine Check Architecture - (MCA) is not supported" << endl;
	(edxBits[15]) ? cout << "EDX bit 15: " << edxBits[15] << ": Conditional move: CMOV, FCMOV and FCOMI instructions - (CMOV) is supported" << endl : cout << "EDX bit 15: " << edxBits[15] << ": Conditional move: CMOV, FCMOV and FCOMI instructions - (CMOV) is not supported" << endl;
	(edxBits[16]) ? cout << "EDX bit 16: " << edxBits[16] << ": Page Attribute Table - (PAT) is supported" << endl : cout << "EDX bit 16: " << edxBits[16] << ": Page Attribute Table - (PAT) is not supported" << endl;
	(edxBits[17]) ? cout << "EDX bit 17: " << edxBits[17] << ": 36-bit Page Size Extension - (PSE-36) is supported" << endl : cout << "EDX bit 17: " << edxBits[17] << ": 36-bit Page Size Extension - (PSE-36) is not supported" << endl;
	(edxBits[18]) ? cout << "EDX bit 18: " << edxBits[18] << ": Processor Serial Number supported and enable - (PSN) is supported" << endl : cout << "EDX bit 18: " << edxBits[18] << ": Processor Serial Number supported and enable - (PSN) is not supported" << endl;
	(edxBits[19]) ? cout << "EDX bit 19: " << edxBits[19] << ": CLFLUSH cache line flush instruction (SSE2)  - (CLFSH) is supported" << endl : cout << "EDX bit 19: " << edxBits[19] << ": CLFLUSH cache line flush instruction (SSE2)  - (CLFSH) is not supported" << endl;
	(edxBits[20]) ? cout << "EDX bit 20: " << edxBits[20] << ": No-execute (NX) bit (Itanium only, reserved on other CPUs - (NX) is supported" << endl : cout << "EDX bit 20: " << edxBits[20] << ": No-execute (NX) bit (Itanium only, reserved on other CPUs - (NX) is not supported" << endl;
	(edxBits[21]) ? cout << "EDX bit 21: " << edxBits[21] << ": Debug store: save trace of executed jumps - (DS) is supported" << endl : cout << "EDX bit 21: " << edxBits[21] << ": Debug store: save trace of executed jumps - (DS) is not supported" << endl;
	(edxBits[22]) ? cout << "EDX bit 22: " << edxBits[22] << ": Onboard thermal control MSRs for ACPI - (ACPI) is supported" << endl : cout << "EDX bit 22: " << edxBits[22] << ": Onboard thermal control MSRs for ACPI - (ACPI) is not supported" << endl;
	(edxBits[23]) ? cout << "EDX bit 23: " << edxBits[23] << ": MMX instructions (64-bit SIMD) - (MMX) is supported" << endl : cout << "EDX bit 23: " << edxBits[23] << ": MMX instructions (64-bit SIMD) - (MMX) is not supported" << endl;
	(edxBits[24]) ? cout << "EDX bit 24: " << edxBits[24] << ": FXSAVE, FXRSTOR instructions, CR4 bit 9 - (FXSR) is supported" << endl : cout << "EDX bit 24: " << edxBits[24] << ": FXSAVE, FXRSTOR instructions, CR4 bit 9 - (FXSR) is not supported" << endl;
	(edxBits[25]) ? cout << "EDX bit 25: " << edxBits[25] << ": Streaming SIMD Extensions (SSE) / Katmai New Instructions 128-bit SIMD - (SSE) is supported" << endl : cout << "EDX bit 25: " << edxBits[25] << ": Streaming SIMD Extensions (SSE) / Katmai New Instructions 128-bit SIMD - (SSE) is not supported" << endl;
	(edxBits[26]) ? cout << "EDX bit 26: " << edxBits[26] << ": SSE2 instructions - (SSE2) is supported" << endl : cout << "EDX bit 26: " << edxBits[26] << ": SSE2 instructions - (SSE2) is not supported" << endl;
	(edxBits[27]) ? cout << "EDX bit 27: " << edxBits[27] << ": CPU cache implements self-snoop - (SS) is supported" << endl : cout << "EDX bit 27: " << edxBits[27] << ": CPU cache implements self-snoop - (SS) is not supported" << endl;
	(edxBits[28]) ? cout << "EDX bit 28: " << edxBits[28] << ": Max APIC IDs reserved field is Valid - (HTT) is supported" << endl : cout << "EDX bit 28: " << edxBits[28] << ": Max APIC IDs reserved field is Valid - (HTT) is not supported" << endl;
	(edxBits[29]) ? cout << "EDX bit 29: " << edxBits[29] << ": Thermal monitor automatically limits temperature - (TM) is supported" << endl : cout << "EDX bit 29: " << edxBits[29] << ": Thermal monitor automatically limits temperature - (TM) is not supported" << endl;
	(edxBits[30]) ? cout << "EDX bit 30: " << edxBits[30] << ": IA64 processor emulating x86 - (IA64) is supported" << endl : cout << "EDX bit 30: " << edxBits[30] << ": IA64 processor emulating x86 - (IA64) is not supported" << endl;
	(edxBits[31]) ? cout << "EDX bit 31: " << edxBits[31] << ": Pending Break Enable (PBE# pin) wakeup capability - (PBE) is supported" << endl : cout << "EDX bit 31: " << edxBits[31] << ": Pending Break Enable (PBE# pin) wakeup capability - (PBE) is not supported" << endl;
	cout << endl;

	cout << endl;
	

	// EAX=0x2: Cache and TLB Descriptor Information
	CPUID cpuID2(0x2);
	eaxBits = bitset<32>(cpuID2.EAX());
	ebxBits = bitset<32>(cpuID2.EBX());
	ecxBits = bitset<32>(cpuID2.ECX());
	edxBits = bitset<32>(cpuID2.EDX());

	if (eaxBits[31])
	{
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX) = Invalid Descriptors / No valid information." << endl;
	}
	else
	{
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX) = " << std::hex << "0x" << cpuID2.EAX() << endl;
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX) = " << eaxBits << endl;

		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) = " << eaxBits[7] << eaxBits[6] << eaxBits[5] << eaxBits[4] << eaxBits[3] << eaxBits[2] << eaxBits[1] << eaxBits[0] << endl;
		int descriptorEAX0 = extractBits(cpuID2.EAX(), 0, 8);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) = " << std::hex << "0x" << descriptorEAX0 << endl;
		string descriptorEAX0String = getCacheAndTableDescriptor(descriptorEAX0);
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EAX byte 0) = " << descriptorEAX0String << endl;

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
	
	if (ebxBits[31])
	{
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX) = Invalid Descriptors / No valid information." << endl;
	}
	else
	{
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX) = " << std::hex << "0x" << cpuID2.EBX() << endl;
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EBX) = " << ebxBits << endl;

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

	if (ecxBits[31])
	{
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX) = Invalid Descriptors / No valid information." << endl;
	}
	else
	{
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX) = " << std::hex << "0x" << cpuID2.ECX() << endl;
		cout << "EAX=0x2: Cache and TLB Descriptor Information (ECX) = " << ecxBits << endl;

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

	if (edxBits[31])
	{
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX) = Invalid Descriptors / No valid information." << endl;
	}
	else
	{
		//cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX) = " << std::hex << "0x" << cpuID2.EDX() << endl;
		cout << "EAX=0x2: Cache and TLB Descriptor Information (EDX) = " << edxBits << endl;

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

	// EAX = 15h and EAX = 16h: CPU, TSC, Bus and Core Crystal Clock Frequencies
	CPUID cpuID15(0x15);
	eaxBits = bitset<32>(cpuID15.EAX());
	ebxBits = bitset<32>(cpuID15.EBX());
	ecxBits = bitset<32>(cpuID15.ECX());
	edxBits = bitset<32>(cpuID15.EDX());

	cout << "EAX=0x15: TSC and Core Crystal frequency information :" << endl;
	cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator (EAX) = " << std::hex << "0x" << cpuID15.EAX() << endl;
	cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator (EAX) = " << eaxBits << endl;
	cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator (EBX) = " << std::hex << "0x" << cpuID15.EBX() << endl;
	cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator (EBX) = " << ebxBits << endl;
	cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz (ECX) = " << std::hex << "0x" << cpuID15.ECX() << endl;
	cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz (ECX) = " << ecxBits << endl;
	cout << "EAX=0x15: TSC frequency, in units of Hz (EDX) = " << std::hex << "0x" << cpuID15.EDX() << endl;
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





	return 0;
}


