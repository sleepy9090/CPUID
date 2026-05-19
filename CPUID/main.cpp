#include "CPUID.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <intrin.h>

using namespace std;

/* Manufacturer IDs */
/* AMD:     "AuthenticAMD" */
#define MANUFACTURER_ID_AMD_EBX 0x68747541
#define MANUFACTURER_ID_AMD_ECX 0x444d4163
#define MANUFACTURER_ID_AMD_EDX 0x69746e65

/* CENTAUR: "CentaurHauls" */
#define MANUFACTURER_ID_CENTAUR_EBX 0x746e6543
#define MANUFACTURER_ID_CENTAUR_ECX 0x736c7561
#define MANUFACTURER_ID_CENTAUR_EDX 0x48727561

/* CYRIX:   "CyrixInstead" */
#define MANUFACTURER_ID_CYRIX_EBX 0x69727943
#define MANUFACTURER_ID_CYRIX_ECX 0x64616574
#define MANUFACTURER_ID_CYRIX_EDX 0x736e4978

/* HYGON:   "HygonGenuine" */
#define MANUFACTURER_ID_HYGON_EBX 0x6f677948
#define MANUFACTURER_ID_HYGON_ECX 0x656e6975
#define MANUFACTURER_ID_HYGON_EDX 0x6e65476e

/* INTEL:   "GenuineIntel" */
#define MANUFACTURER_ID_INTEL_EBX 0x756e6547
#define MANUFACTURER_ID_INTEL_ECX 0x6c65746e
#define MANUFACTURER_ID_INTEL_EDX 0x49656e69

/* TM1:     "TransmetaCPU" */
#define MANUFACTURER_ID_TM1_EBX 0x6e617254
#define MANUFACTURER_ID_TM1_ECX 0x55504361
#define MANUFACTURER_ID_TM1_EDX 0x74656d73

/* TM2:     "GenuineTMx86" */
#define MANUFACTURER_ID_TM2_EBX 0x756e6547
#define MANUFACTURER_ID_TM2_ECX 0x3638784d
#define MANUFACTURER_ID_TM2_EDX 0x54656e69

/* NSC:     "Geode by NSC" */
#define MANUFACTURER_ID_NSC_EBX 0x646f6547
#define MANUFACTURER_ID_NSC_ECX 0x43534e20
#define MANUFACTURER_ID_NSC_EDX 0x79622065

/* NEXGEN:  "NexGenDriven" */
#define MANUFACTURER_ID_NEXGEN_EBX 0x4778654e
#define MANUFACTURER_ID_NEXGEN_ECX 0x6e657669
#define MANUFACTURER_ID_NEXGEN_EDX 0x72446e65

/* RISE:    "RiseRiseRise" */
#define MANUFACTURER_ID_RISE_EBX 0x65736952
#define MANUFACTURER_ID_RISE_ECX 0x65736952
#define MANUFACTURER_ID_RISE_EDX 0x65736952

/* SIS:     "SiS SiS SiS " */
#define MANUFACTURER_ID_SIS_EBX 0x20536953
#define MANUFACTURER_ID_SIS_ECX 0x20536953
#define MANUFACTURER_ID_SIS_EDX 0x20536953

/* UMC:     "UMC UMC UMC " */
#define MANUFACTURER_ID_UMC_EBX 0x20434d55
#define MANUFACTURER_ID_UMC_ECX 0x20434d55
#define MANUFACTURER_ID_UMC_EDX 0x20434d55

/* VIA:     "VIA VIA VIA " */
#define MANUFACTURER_ID_VIA_EBX 0x20414956
#define MANUFACTURER_ID_VIA_ECX 0x20414956
#define MANUFACTURER_ID_VIA_EDX 0x20414956

/* VORTEX:  "Vortex86 SoC" */
#define MANUFACTURER_ID_VORTEX_EBX 0x74726f56
#define MANUFACTURER_ID_VORTEX_ECX 0x436f5320
#define MANUFACTURER_ID_VORTEX_EDX 0x36387865


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

	// EAX=0: Highest Function Parameter and Manufacturer ID
	__cpuidex(cpuInfo, 0x0, 0); // Get CPU vendor
	bitset<32> eaxBits = bitset<32>(cpuInfo[0]);
	bitset<32> ebxBits = bitset<32>(cpuInfo[1]);
	bitset<32> ecxBits = bitset<32>(cpuInfo[2]);
	bitset<32> edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x0: [EAX=0: Highest Function Parameter and Manufacturer ID] = " << eaxBits << endl;
	std::cout << "EAX=0x0: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x0: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x0: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x0: [EDX] = " << edxBits << endl;
	std::cout << endl;

	string vendor;
	vendor += string((const char*)&cpuInfo[1], 4);
	vendor += string((const char*)&cpuInfo[3], 4);
	vendor += string((const char*)&cpuInfo[2], 4);

	int manufacturerIdEbx = cpuInfo[1];
	int manufacturerIdEcx = cpuInfo[2];
	int manufacturerIdEdx = cpuInfo[3];
	
	std::cout << "EAX=0: Manufacturer ID: EBX = " << std::hex << "0x" << manufacturerIdEbx << " " << string((const char*)&manufacturerIdEbx, 4) << endl;
	std::cout << "EAX=0: Manufacturer ID: EDX = " << std::hex << "0x" << manufacturerIdEdx << " " << string((const char*)&manufacturerIdEdx, 4) << endl;
	std::cout << "EAX=0: Manufacturer ID: ECX = " << std::hex << "0x" << manufacturerIdEcx << " " << string((const char*)&manufacturerIdEcx, 4) << endl;
	std::cout << "EAX=0: Highest Function Parameter: EAX = " << std::hex << "0x" << cpuInfo[0] << endl;
	std::cout << "CPU vendor = " << vendor << endl;
	std::cout << endl;

	// EAX=1: Processor Info and Feature Bits
	__cpuidex(cpuInfo, 0x1, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x1: [EAX=1: Processor Info and Feature Bits] = " << eaxBits << endl;
	std::cout << "EAX=0x1: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x1: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x1: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x1: [EDX] = " << edxBits << endl;
	std::cout << endl;

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
	std::cout << "EAX=0x2: [Cache and TLB Descriptor Information] = " << eaxBits << endl;
	std::cout << "EAX=0x2: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x2: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x2: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x2: [EDX] = " << edxBits << endl;
	std::cout << endl;

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
	std::cout << endl;

	std::cout << "EAX=0x3: PSN [EAX=0x1:EDX:ECX] (Pentium 3 CPUs - 96-bit) = " << std::hex << ZeroPadNumber(eaxBits1.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(edxBits.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(ecxBits.to_ulong(), 8) << endl;
	std::cout << "EAX=0x3: PSN [EAX:EBX:ECX:EDX] (Transmeta Crusoe and Efficeon CPUs - 128-bit) = " << std::hex << ZeroPadNumber(eaxBits.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(ebxBits.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(ecxBits.to_ulong(), 8) << ":" << std::hex << ZeroPadNumber(edxBits.to_ulong(), 8) << endl;
	std::cout << endl;

	// EAX=4 and EAX=8000'001Dh: Cache Hierarchy and Topology
	std::cout << "EAX=0x4 and EAX=8000001Dh: [Cache Hierarchy and Topology Information]: " << endl;

	// Intel
	if ((manufacturerIdEbx == MANUFACTURER_ID_INTEL_EBX) && (manufacturerIdEcx == MANUFACTURER_ID_INTEL_ECX) && (manufacturerIdEdx == MANUFACTURER_ID_INTEL_EDX))
	{
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
	}

	// AMD 
	if ((manufacturerIdEbx == MANUFACTURER_ID_AMD_EBX) && (manufacturerIdEcx == MANUFACTURER_ID_AMD_ECX) && (manufacturerIdEdx == MANUFACTURER_ID_AMD_EDX))
	{
		eaxBits = -1;
		int i = 0;
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
	}

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
	std::cout << endl;

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
	std::cout << endl;

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
	std::cout << endl;

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
	std::cout << endl;

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

	std::cout << endl;
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

	std::cout << "EAX: " << std::hex << "0x" << ZeroPadNumber(eaxBits.to_ulong(), 8) << endl;
	std::cout << "EBX: " << std::hex << "0x" << ZeroPadNumber(ebxBits.to_ulong(), 8) << endl;
	std::cout << "ECX: " << std::hex << "0x" << ZeroPadNumber(ecxBits.to_ulong(), 8) << endl;
	std::cout << "EDX: " << std::hex << "0x" << ZeroPadNumber(edxBits.to_ulong(), 8) << endl;
	std::cout << "EAX=0x7: Maximum ECX Value = " << std::hex << "0x" << ZeroPadNumber(eaxBits.to_ulong(), 8) << endl;
	std::cout << endl;

	(ebxBits[0]) ? std::cout << "EBX bit 0: " << ebxBits[0] << ": [SUPPORTED] Access to base of %fs and %gs - (fsgsbase)" << endl : std::cout << "EBX bit 0: " << ebxBits[0] << ": [UNSUPPORTED] Access to base of %fs and %gs - (fsgsbase)" << endl;
	(ebxBits[1]) ? std::cout << "EBX bit 1: " << ebxBits[1] << ": [SUPPORTED] IA32_TSC_ADJUST MSR - (tsc_adjust)" << endl : std::cout << "EBX bit 1: " << ebxBits[1] << ": [UNSUPPORTED] IA32_TSC_ADJUST MSR - (tsc_adjust)" << endl;
	(ebxBits[2]) ? std::cout << "EBX bit 2: " << ebxBits[2] << ": [SUPPORTED] Software Guard Extensions - (sgx)" << endl : std::cout << "EBX bit 2: " << ebxBits[2] << ": [UNSUPPORTED] Software Guard Extensions - (sgx)" << endl;
	(ebxBits[3]) ? std::cout << "EBX bit 3: " << ebxBits[3] << ": [SUPPORTED] Bit Manipulation Instruction Set 1 - (bmi1)" << endl : std::cout << "EBX bit 3: " << ebxBits[3] << ": [UNSUPPORTED] Bit Manipulation Instruction Set 1 - (bmi1)" << endl;
	(ebxBits[4]) ? std::cout << "EBX bit 4: " << ebxBits[4] << ": [SUPPORTED] TSX Hardware Lock Elision - (hle)" << endl : std::cout << "EBX bit 4: " << ebxBits[4] << ": [UNSUPPORTED] TSX Hardware Lock Elision - (hle)" << endl;
	(ebxBits[5]) ? std::cout << "EBX bit 5: " << ebxBits[5] << ": [SUPPORTED] Advanced Vector Extensions 2 - (avx2)" << endl : std::cout << "EBX bit 5: " << ebxBits[5] << ": [UNSUPPORTED] Advanced Vector Extensions 2 - (avx2)" << endl;
	(ebxBits[6]) ? std::cout << "EBX bit 6: " << ebxBits[6] << ": [SUPPORTED] x87 FPU data pointer register updated on exceptions only - (fdp-excptn-only)" << endl : std::cout << "EBX bit 6: " << ebxBits[6] << ": [UNSUPPORTED] x87 FPU data pointer register updated on exceptions only - (fdp-excptn-only)" << endl;
	(ebxBits[7]) ? std::cout << "EBX bit 7: " << ebxBits[7] << ": [SUPPORTED] Supervisor Mode Execution Prevention - (smep)" << endl : std::cout << "EBX bit 7: " << ebxBits[7] << ": [UNSUPPORTED] Supervisor Mode Execution Prevention - (smep)" << endl;
	(ebxBits[8]) ? std::cout << "EBX bit 8: " << ebxBits[8] << ": [SUPPORTED] Bit Manipulation Instruction Set 2 - (bmi2)" << endl : std::cout << "EBX bit 8: " << ebxBits[8] << ": [UNSUPPORTED] Bit Manipulation Instruction Set 2 - (bmi2)" << endl;
	(ebxBits[9]) ? std::cout << "EBX bit 9: " << ebxBits[9] << ": [SUPPORTED] Enhanced REP MOVSB/STOSB - (erms)" << endl : std::cout << "EBX bit 9: " << ebxBits[9] << ": [UNSUPPORTED] Enhanced REP MOVSB/STOSB - (erms)" << endl;
	(ebxBits[10]) ? std::cout << "EBX bit 10: " << ebxBits[10] << ": [SUPPORTED] INVPCID instruction - (invpcid)" << endl : std::cout << "EBX bit 10: " << ebxBits[10] << ": [UNSUPPORTED] INVPCID instruction - (invpcid)" << endl;
	(ebxBits[11]) ? std::cout << "EBX bit 11: " << ebxBits[11] << ": [SUPPORTED] TSX Restricted Transactional Memory - (rtm)" << endl : std::cout << "EBX bit 11: " << ebxBits[11] << ": [UNSUPPORTED] TSX Restricted Transactional Memory - (rtm)" << endl;
	(ebxBits[12]) ? std::cout << "EBX bit 12: " << ebxBits[12] << ": [SUPPORTED] Intel Resource Director (RDT) Monitoring or AMD Platform QOS Monitoring - (rdt-m/pqm)" << endl : std::cout << "EBX bit 12: " << ebxBits[12] << ": [UNSUPPORTED] Intel Resource Director (RDT) Monitoring or AMD Platform QOS Monitoring - (rdt-m/pqm)" << endl;
	(ebxBits[13]) ? std::cout << "EBX bit 13: " << ebxBits[13] << ": [SUPPORTED] x87 FPU CS and DS deprecated - (fcs_fds_­deprecation)" << endl : std::cout << "EBX bit 13: " << ebxBits[13] << ": [UNSUPPORTED] x87 FPU CS and DS deprecated - (fcs_fds_­deprecation)" << endl;
	(ebxBits[14]) ? std::cout << "EBX bit 14: " << ebxBits[14] << ": [SUPPORTED] Intel MPX (Memory Protection Extensions) - (mpx)" << endl : std::cout << "EBX bit 14: " << ebxBits[14] << ": [UNSUPPORTED] Intel MPX (Memory Protection Extensions) - (mpx)" << endl;
	(ebxBits[15]) ? std::cout << "EBX bit 15: " << ebxBits[15] << ": [SUPPORTED] Intel Resource Director (RDT) Allocation or AMD Platform QOS Enforcement - (rdt-a/pqe)" << endl : std::cout << "EBX bit 15: " << ebxBits[15] << ": [UNSUPPORTED] Intel Resource Director (RDT) Allocation or AMD Platform QOS Enforcement - (rdt-a/pqe)" << endl;
	(ebxBits[16]) ? std::cout << "EBX bit 16: " << ebxBits[16] << ": [SUPPORTED] AVX-512 Foundation - (avx512-f)" << endl : std::cout << "EBX bit 16: " << ebxBits[16] << ": [UNSUPPORTED] AVX-512 Foundation - (avx512-f)" << endl;
	(ebxBits[17]) ? std::cout << "EBX bit 17: " << ebxBits[17] << ": [SUPPORTED] AVX-512 Doubleword and Quadword Instructions - (avx512-dq)" << endl : std::cout << "EBX bit 17: " << ebxBits[17] << ": [UNSUPPORTED] AVX-512 Doubleword and Quadword Instructions - (avx512-dq)" << endl;
	(ebxBits[18]) ? std::cout << "EBX bit 18: " << ebxBits[18] << ": [SUPPORTED] RDSEED instruction - (rdseed)" << endl : std::cout << "EBX bit 18: " << ebxBits[18] << ": [UNSUPPORTED] RDSEED instruction - (rdseed)" << endl;
	(ebxBits[19]) ? std::cout << "EBX bit 19: " << ebxBits[19] << ": [SUPPORTED] Intel ADX (Multi-Precision Add-Carry Instruction Extensions) - (adx)" << endl : std::cout << "EBX bit 19: " << ebxBits[19] << ": [UNSUPPORTED] Intel ADX (Multi-Precision Add-Carry Instruction Extensions) - (adx)" << endl;
	(ebxBits[20]) ? std::cout << "EBX bit 20: " << ebxBits[20] << ": [SUPPORTED] Supervisor Mode Access Prevention - (smap)" << endl : std::cout << "EBX bit 20: " << ebxBits[20] << ": [UNSUPPORTED] Supervisor Mode Access Prevention - (smap)" << endl;
	(ebxBits[21]) ? std::cout << "EBX bit 21: " << ebxBits[21] << ": [SUPPORTED] AVX-512 Integer Fused Multiply-Add Instructions - (avx512-ifma)" << endl : std::cout << "EBX bit 21: " << ebxBits[21] << ": [UNSUPPORTED] AVX-512 Integer Fused Multiply-Add Instructions - (avx512-ifma)" << endl;
	(ebxBits[22]) ? std::cout << "EBX bit 22: " << ebxBits[22] << ": [SUPPORTED] (PCOMMIT instruction, deprecated) - (pcommit)" << endl : std::cout << "EBX bit 22: " << ebxBits[22] << ": [UNSUPPORTED] (PCOMMIT instruction, deprecated) - (pcommit)" << endl;
	(ebxBits[23]) ? std::cout << "EBX bit 23: " << ebxBits[23] << ": [SUPPORTED] CLFLUSHOPT instruction - (clflushopt)" << endl : std::cout << "EBX bit 23: " << ebxBits[23] << ": [UNSUPPORTED] CLFLUSHOPT instruction - (clflushopt)" << endl;
	(ebxBits[24]) ? std::cout << "EBX bit 24: " << ebxBits[24] << ": [SUPPORTED] CLWB (Cache line writeback) instruction - (clwb)" << endl : std::cout << "EBX bit 24: " << ebxBits[24] << ": [UNSUPPORTED] CLWB (Cache line writeback) instruction - (clwb)" << endl;
	(ebxBits[25]) ? std::cout << "EBX bit 25: " << ebxBits[25] << ": [SUPPORTED] Intel Processor Trace - (pt)" << endl : std::cout << "EBX bit 25: " << ebxBits[25] << ": [UNSUPPORTED] Intel Processor Trace - (pt)" << endl;
	(ebxBits[26]) ? std::cout << "EBX bit 26: " << ebxBits[26] << ": [SUPPORTED] AVX-512 Prefetch Instructions - (avx512-pf)" << endl : std::cout << "EBX bit 26: " << ebxBits[26] << ": [UNSUPPORTED] AVX-512 Prefetch Instructions - (avx512-pf)" << endl;
	(ebxBits[27]) ? std::cout << "EBX bit 27: " << ebxBits[27] << ": [SUPPORTED] AVX-512 Exponential and Reciprocal Instructions - (avx512-er)" << endl : std::cout << "EBX bit 27: " << ebxBits[27] << ": [UNSUPPORTED] AVX-512 Exponential and Reciprocal Instructions - (avx512-er)" << endl;
	(ebxBits[28]) ? std::cout << "EBX bit 28: " << ebxBits[28] << ": [SUPPORTED] AVX-512 Conflict Detection Instructions - (avx512-cd)" << endl : std::cout << "EBX bit 28: " << ebxBits[28] << ": [UNSUPPORTED] AVX-512 Conflict Detection Instructions - (avx512-cd)" << endl;
	(ebxBits[29]) ? std::cout << "EBX bit 29: " << ebxBits[29] << ": [SUPPORTED] SHA-1 and SHA-256 extensions - (sha)" << endl : std::cout << "EBX bit 29: " << ebxBits[29] << ": [UNSUPPORTED] SHA-1 and SHA-256 extensions - (sha)" << endl;
	(ebxBits[30]) ? std::cout << "EBX bit 30: " << ebxBits[30] << ": [SUPPORTED] AVX-512 Byte and Word Instructions - (avx512-bw)" << endl : std::cout << "EBX bit 30: " << ebxBits[30] << ": [UNSUPPORTED] AVX-512 Byte and Word Instructions - (avx512-bw)" << endl;
	(ebxBits[31]) ? std::cout << "EBX bit 31: " << ebxBits[31] << ": [SUPPORTED] AVX-512 Vector Length Extensions - (avx512-vl)" << endl : std::cout << "EBX bit 31: " << ebxBits[31] << ": [UNSUPPORTED] AVX-512 Vector Length Extensions - (avx512-vl)" << endl;
	std::cout << endl;

	(ecxBits[0]) ? std::cout << "ECX bit 0: " << ecxBits[0] << ": [SUPPORTED] PREFETCHWT1 instruction - (prefetchwt1)" << endl : std::cout << "ECX bit 0: " << ecxBits[0] << ": [UNSUPPORTED] PREFETCHWT1 instruction - (prefetchwt1)" << endl;
	(ecxBits[1]) ? std::cout << "ECX bit 1: " << ecxBits[1] << ": [SUPPORTED] AVX-512 Vector Bit Manipulation Instructions - (avx512-vbmi)" << endl : std::cout << "ECX bit 1: " << ecxBits[1] << ": [UNSUPPORTED] AVX-512 Vector Bit Manipulation Instructions - (avx512-vbmi)" << endl;
	(ecxBits[2]) ? std::cout << "ECX bit 2: " << ecxBits[2] << ": [SUPPORTED] User-mode Instruction Prevention - (umip)" << endl : std::cout << "ECX bit 2: " << ecxBits[2] << ": [UNSUPPORTED] User-mode Instruction Prevention - (umip)" << endl;
	(ecxBits[3]) ? std::cout << "ECX bit 3: " << ecxBits[3] << ": [SUPPORTED] Memory Protection Keys for User-mode pages - (pku)" << endl : std::cout << "ECX bit 3: " << ecxBits[3] << ": [UNSUPPORTED] Memory Protection Keys for User-mode pages - (pku)" << endl;
	(ecxBits[4]) ? std::cout << "ECX bit 4: " << ecxBits[4] << ": [SUPPORTED] PKU enabled by OS - (ospke)" << endl : std::cout << "ECX bit 4: " << ecxBits[4] << ": [UNSUPPORTED] PKU enabled by OS - (ospke)" << endl;
	(ecxBits[5]) ? std::cout << "ECX bit 5: " << ecxBits[5] << ": [SUPPORTED] Timed pause and user-level monitor/wait instructions (TPAUSE, UMONITOR, UMWAIT) - (waitpkg)" << endl : std::cout << "ECX bit 5: " << ecxBits[5] << ": [UNSUPPORTED] Timed pause and user-level monitor/wait instructions (TPAUSE, UMONITOR, UMWAIT) - (waitpkg)" << endl;
	(ecxBits[6]) ? std::cout << "ECX bit 6: " << ecxBits[6] << ": [SUPPORTED] AVX-512 Vector Bit Manipulation Instructions 2 - (avx512-vbmi2)" << endl : std::cout << "ECX bit 6: " << ecxBits[6] << ": [UNSUPPORTED] AVX-512 Vector Bit Manipulation Instructions 2 - (avx512-vbmi2)" << endl;
	(ecxBits[7]) ? std::cout << "ECX bit 7: " << ecxBits[7] << ": [SUPPORTED] Control flow enforcement (CET): shadow stack (SHSTK alternative name) - (cet_ss/shstk)" << endl : std::cout << "ECX bit 7: " << ecxBits[7] << ": [UNSUPPORTED] Control flow enforcement (CET): shadow stack (SHSTK alternative name) - (cet_ss/shstk)" << endl;
	(ecxBits[8]) ? std::cout << "ECX bit 8: " << ecxBits[8] << ": [SUPPORTED] Galois Field instructions - (gfni)" << endl : std::cout << "ECX bit 8: " << ecxBits[8] << ": [UNSUPPORTED] Galois Field instructions - (gfni)" << endl;
	(ecxBits[9]) ? std::cout << "ECX bit 9: " << ecxBits[9] << ": [SUPPORTED] Vector AES instruction set (VEX-256/EVEX) - (vaes)" << endl : std::cout << "ECX bit 9: " << ecxBits[9] << ": [UNSUPPORTED] Vector AES instruction set (VEX-256/EVEX) - (vaes)" << endl;
	(ecxBits[10]) ? std::cout << "ECX bit 10: " << ecxBits[10] << ": [SUPPORTED] CLMUL instruction set (VEX-256/EVEX) - (vpclmulqdq)" << endl : std::cout << "ECX bit 10: " << ecxBits[10] << ": [UNSUPPORTED] CLMUL instruction set (VEX-256/EVEX) - (vpclmulqdq)" << endl;
	(ecxBits[11]) ? std::cout << "ECX bit 11: " << ecxBits[11] << ": [SUPPORTED] AVX-512 Vector Neural Network Instructions - (avx512-vnni)" << endl : std::cout << "ECX bit 11: " << ecxBits[11] << ": [UNSUPPORTED] AVX-512 Vector Neural Network Instructions - (avx512-vnni)" << endl;
	(ecxBits[12]) ? std::cout << "ECX bit 12: " << ecxBits[12] << ": [SUPPORTED] AVX-512 BITALG instructions - (avx512-bitalg)" << endl : std::cout << "ECX bit 12: " << ecxBits[12] << ": [UNSUPPORTED] AVX-512 BITALG instructions - (avx512-bitalg)" << endl;
	(ecxBits[13]) ? std::cout << "ECX bit 13: " << ecxBits[13] << ": [SUPPORTED] Total Memory Encryption MSRs available - (tme_en)" << endl : std::cout << "ECX bit 13: " << ecxBits[13] << ": [UNSUPPORTED] Total Memory Encryption MSRs available - (tme_en)" << endl;
	(ecxBits[14]) ? std::cout << "ECX bit 14: " << ecxBits[14] << ": [SUPPORTED] AVX-512 Vector Population Count Double and Quad-word - (avx512-vpopcntdq)" << endl : std::cout << "ECX bit 14: " << ecxBits[14] << ": [UNSUPPORTED] AVX-512 Vector Population Count Double and Quad-word - (avx512-vpopcntdq)" << endl;
	(ecxBits[15]) ? std::cout << "ECX bit 15: " << ecxBits[15] << ": [SUPPORTED] ? - (fzm)" << endl : std::cout << "ECX bit 15: " << ecxBits[15] << ": [UNSUPPORTED] ? - (fzm)" << endl;
	(ecxBits[16]) ? std::cout << "ECX bit 16: " << ecxBits[16] << ": [SUPPORTED] 5-level paging (57 address bits) - (la57)" << endl : std::cout << "ECX bit 16: " << ecxBits[16] << ": [UNSUPPORTED] 5-level paging (57 address bits) - (la57)" << endl;
	(ecxBits[17]) ? std::cout << "ECX bit 17: " << ecxBits[17] << ": [SUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl : std::cout << "ECX bit 17: " << ecxBits[17] << ": [UNSUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl;
	(ecxBits[18]) ? std::cout << "ECX bit 18: " << ecxBits[18] << ": [SUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl : std::cout << "ECX bit 18: " << ecxBits[18] << ": [UNSUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl;
	(ecxBits[19]) ? std::cout << "ECX bit 19: " << ecxBits[19] << ": [SUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl : std::cout << "ECX bit 19: " << ecxBits[19] << ": [UNSUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl;
	(ecxBits[20]) ? std::cout << "ECX bit 20: " << ecxBits[20] << ": [SUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl : std::cout << "ECX bit 20: " << ecxBits[20] << ": [UNSUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl;
	(ecxBits[21]) ? std::cout << "ECX bit 21: " << ecxBits[21] << ": [SUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl : std::cout << "ECX bit 21: " << ecxBits[21] << ": [UNSUPPORTED] The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau)" << endl;
	(ecxBits[22]) ? std::cout << "ECX bit 22: " << ecxBits[22] << ": [SUPPORTED] RDPID (Read Processor ID) instruction and IA32_TSC_AUX MSR - (rdpid)" << endl : std::cout << "ECX bit 22: " << ecxBits[22] << ": [UNSUPPORTED] RDPID (Read Processor ID) instruction and IA32_TSC_AUX MSR - (rdpid)" << endl;
	(ecxBits[23]) ? std::cout << "ECX bit 23: " << ecxBits[23] << ": [SUPPORTED] AES Key Locker - (kl)" << endl : std::cout << "ECX bit 23: " << ecxBits[23] << ": [UNSUPPORTED] AES Key Locker - (kl)" << endl;
	(ecxBits[24]) ? std::cout << "ECX bit 24: " << ecxBits[24] << ": [SUPPORTED] Bus lock debug exceptions - (bus-lock-detect)" << endl : std::cout << "ECX bit 24: " << ecxBits[24] << ": [UNSUPPORTED] Bus lock debug exceptions - (bus-lock-detect)" << endl;
	(ecxBits[25]) ? std::cout << "ECX bit 25: " << ecxBits[25] << ": [SUPPORTED] CLDEMOTE (Cache line demote) instruction - (cldemote)" << endl : std::cout << "ECX bit 25: " << ecxBits[25] << ": [UNSUPPORTED] CLDEMOTE (Cache line demote) instruction - (cldemote)" << endl;
	(ecxBits[26]) ? std::cout << "ECX bit 26: " << ecxBits[26] << ": [SUPPORTED] ? - (mprr)" << endl : std::cout << "ECX bit 26: " << ecxBits[26] << ": [UNSUPPORTED] ? - (mprr)" << endl;
	(ecxBits[27]) ? std::cout << "ECX bit 27: " << ecxBits[27] << ": [SUPPORTED] MOVDIRI instruction - (movdiri)" << endl : std::cout << "ECX bit 27: " << ecxBits[27] << ": [UNSUPPORTED] MOVDIRI instruction - (movdiri)" << endl;
	(ecxBits[28]) ? std::cout << "ECX bit 28: " << ecxBits[28] << ": [SUPPORTED] MOVDIR64B (64-byte direct store) instruction - (movdir64b)" << endl : std::cout << "ECX bit 28: " << ecxBits[28] << ": [UNSUPPORTED] MOVDIR64B (64-byte direct store) instruction - (movdir64b)" << endl;
	(ecxBits[29]) ? std::cout << "ECX bit 29: " << ecxBits[29] << ": [SUPPORTED] Enqueue Stores and EMQCMD/EMQCMDS instructions - (enqcmd)" << endl : std::cout << "ECX bit 29: " << ecxBits[29] << ": [UNSUPPORTED] Enqueue Stores and EMQCMD/EMQCMDS instructions - (enqcmd)" << endl;
	(ecxBits[30]) ? std::cout << "ECX bit 30: " << ecxBits[30] << ": [SUPPORTED] SGX Launch Configuration - (sgx-lc)" << endl : std::cout << "ECX bit 30: " << ecxBits[30] << ": [UNSUPPORTED] SGX Launch Configuration - (sgx-lc)" << endl;
	(ecxBits[31]) ? std::cout << "ECX bit 31: " << ecxBits[31] << ": [SUPPORTED] Protection keys for supervisor-mode pages - (pks)" << endl : std::cout << "ECX bit 31: " << ecxBits[31] << ": [UNSUPPORTED] Protection keys for supervisor-mode pages - (pks)" << endl;
	std::cout << endl;

	(edxBits[0]) ? std::cout << "EDX bit 0: " << edxBits[0] << ": [SUPPORTED] ? - (sgx-tem)" << endl : std::cout << "EDX bit 0: " << edxBits[0] << ": [UNSUPPORTED] ? - (sgx-tem)" << endl;
	(edxBits[1]) ? std::cout << "EDX bit 1: " << edxBits[1] << ": [SUPPORTED] Attestation Services for Intel SGX - (sgx-keys)" << endl : std::cout << "EDX bit 1: " << edxBits[1] << ": [UNSUPPORTED] Attestation Services for Intel SGX - (sgx-keys)" << endl;
	(edxBits[2]) ? std::cout << "EDX bit 2: " << edxBits[2] << ": [SUPPORTED] AVX-512 4-register Neural Network Instructions - (avx512-4vnniw)" << endl : std::cout << "EDX bit 2: " << edxBits[2] << ": [UNSUPPORTED] AVX-512 4-register Neural Network Instructions - (avx512-4vnniw)" << endl;
	(edxBits[3]) ? std::cout << "EDX bit 3: " << edxBits[3] << ": [SUPPORTED] AVX-512 4-register Multiply Accumulation Single precision - (avx512-4fmaps)" << endl : std::cout << "EDX bit 3: " << edxBits[3] << ": [UNSUPPORTED] AVX-512 4-register Multiply Accumulation Single precision - (avx512-4fmaps)" << endl;
	(edxBits[4]) ? std::cout << "EDX bit 4: " << edxBits[4] << ": [SUPPORTED] Fast Short REP MOVSB - (fsrm)" << endl : std::cout << "EDX bit 4: " << edxBits[4] << ": [UNSUPPORTED] Fast Short REP MOVSB - (fsrm)" << endl;
	(edxBits[5]) ? std::cout << "EDX bit 5: " << edxBits[5] << ": [SUPPORTED] User Inter-processor Interrupts - (uintr)" << endl : std::cout << "EDX bit 5: " << edxBits[5] << ": [UNSUPPORTED] User Inter-processor Interrupts - (uintr)" << endl;
	(edxBits[6]) ? std::cout << "EDX bit 6: " << edxBits[6] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 6: " << edxBits[6] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[7]) ? std::cout << "EDX bit 7: " << edxBits[7] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 7: " << edxBits[7] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[8]) ? std::cout << "EDX bit 8: " << edxBits[8] << ": [SUPPORTED] AVX-512 vector intersection instructions on 32/64-bit integers - (avx512-vp2intersect)" << endl : std::cout << "EDX bit 8: " << edxBits[8] << ": [UNSUPPORTED] AVX-512 vector intersection instructions on 32/64-bit integers - (avx512-vp2intersect)" << endl;
	(edxBits[9]) ? std::cout << "EDX bit 9: " << edxBits[9] << ": [SUPPORTED] Special Register Buffer Data Sampling Mitigations - (srbds-ctrl)" << endl : std::cout << "EDX bit 9: " << edxBits[9] << ": [UNSUPPORTED] Special Register Buffer Data Sampling Mitigations - (srbds-ctrl)" << endl;
	(edxBits[10]) ? std::cout << "EDX bit 10: " << edxBits[10] << ": [SUPPORTED] VERW instruction clears CPU buffers - (md-clear)" << endl : std::cout << "EDX bit 10: " << edxBits[10] << ": [UNSUPPORTED] VERW instruction clears CPU buffers - (md-clear)" << endl;
	(edxBits[11]) ? std::cout << "EDX bit 11: " << edxBits[11] << ": [SUPPORTED] All TSX transactions are aborted - (rtm-always-abort)" << endl : std::cout << "EDX bit 11: " << edxBits[11] << ": [UNSUPPORTED] All TSX transactions are aborted - (rtm-always-abort)" << endl;
	(edxBits[12]) ? std::cout << "EDX bit 12: " << edxBits[12] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 12: " << edxBits[12] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[13]) ? std::cout << "EDX bit 13: " << edxBits[13] << ": [SUPPORTED] TSX_FORCE_ABORT (MSR 0x10f) is available - (rtm-force-abort)" << endl : std::cout << "EDX bit 13: " << edxBits[13] << ": [UNSUPPORTED] TSX_FORCE_ABORT (MSR 0x10f) is available - (rtm-force-abort)" << endl;
	(edxBits[14]) ? std::cout << "EDX bit 14: " << edxBits[14] << ": [SUPPORTED] SERIALIZE instruction - (serialize)" << endl : std::cout << "EDX bit 14: " << edxBits[14] << ": [UNSUPPORTED] SERIALIZE instruction - (serialize)" << endl;
	(edxBits[15]) ? std::cout << "EDX bit 15: " << edxBits[15] << ": [SUPPORTED] Mixture of CPU types in processor topology (e.g. Alder Lake) - (hybrid)" << endl : std::cout << "EDX bit 15: " << edxBits[15] << ": [UNSUPPORTED] Mixture of CPU types in processor topology (e.g. Alder Lake) - (hybrid)" << endl;
	(edxBits[16]) ? std::cout << "EDX bit 16: " << edxBits[16] << ": [SUPPORTED] TSX load address tracking suspend/resume instructions (TSUSLDTRK and TRESLDTRK) - (tsxldtrk)" << endl : std::cout << "EDX bit 16: " << edxBits[16] << ": [UNSUPPORTED] TSX load address tracking suspend/resume instructions (TSUSLDTRK and TRESLDTRK) - (tsxldtrk)" << endl;
	(edxBits[17]) ? std::cout << "EDX bit 17: " << edxBits[17] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 17: " << edxBits[17] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[18]) ? std::cout << "EDX bit 18: " << edxBits[18] << ": [SUPPORTED] Platform configuration (Memory Encryption Technologies Instructions) - (pconfig)" << endl : std::cout << "EDX bit 18: " << edxBits[18] << ": [UNSUPPORTED] Platform configuration (Memory Encryption Technologies Instructions) - (pconfig)" << endl;
	(edxBits[19]) ? std::cout << "EDX bit 19: " << edxBits[19] << ": [SUPPORTED] Architectural Last Branch Records - (lbr)" << endl : std::cout << "EDX bit 19: " << edxBits[19] << ": [UNSUPPORTED] Architectural Last Branch Records - (lbr)" << endl;
	(edxBits[20]) ? std::cout << "EDX bit 20: " << edxBits[20] << ": [SUPPORTED] Control flow enforcement (CET): indirect branch tracking - (cet-ibt)" << endl : std::cout << "EDX bit 20: " << edxBits[20] << ": [UNSUPPORTED] Control flow enforcement (CET): indirect branch tracking - (cet-ibt)" << endl;
	(edxBits[21]) ? std::cout << "EDX bit 21: " << edxBits[21] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 21: " << edxBits[21] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[22]) ? std::cout << "EDX bit 22: " << edxBits[22] << ": [SUPPORTED] AMX tile computation on bfloat16 numbers - (amx-bf16)" << endl : std::cout << "EDX bit 22: " << edxBits[22] << ": [UNSUPPORTED] AMX tile computation on bfloat16 numbers - (amx-bf16)" << endl;
	(edxBits[23]) ? std::cout << "EDX bit 23: " << edxBits[23] << ": [SUPPORTED] AVX-512 half-precision floating-point arithmetic instructions - (avx512-fp16)" << endl : std::cout << "EDX bit 23: " << edxBits[23] << ": [UNSUPPORTED] AVX-512 half-precision floating-point arithmetic instructions - (avx512-fp16)" << endl;
	(edxBits[24]) ? std::cout << "EDX bit 24: " << edxBits[24] << ": [SUPPORTED] AMX tile load/store instructions - (amx-tile)" << endl : std::cout << "EDX bit 24: " << edxBits[24] << ": [UNSUPPORTED] AMX tile load/store instructions - (amx-tile)" << endl;
	(edxBits[25]) ? std::cout << "EDX bit 25: " << edxBits[25] << ": [SUPPORTED] AMX tile computation on 8-bit integers - (amx-int8)" << endl : std::cout << "EDX bit 25: " << edxBits[25] << ": [UNSUPPORTED] AMX tile computation on 8-bit integers - (amx-int8)" << endl;
	(edxBits[26]) ? std::cout << "EDX bit 26: " << edxBits[26] << ": [SUPPORTED] Speculation Control, part of Indirect Branch Control (IBC): Indirect Branch Restricted Speculation (IBRS) and Indirect Branch Prediction Barrier (IBPB) - (ibrs / spec_ctrl)" << endl : std::cout << "EDX bit 26: " << edxBits[26] << ": [UNSUPPORTED] Speculation Control, part of Indirect Branch Control (IBC): Indirect Branch Restricted Speculation (IBRS) and Indirect Branch Prediction Barrier (IBPB) - (ibrs / spec_ctrl)" << endl;
	(edxBits[27]) ? std::cout << "EDX bit 27: " << edxBits[27] << ": [SUPPORTED] Single Thread Indirect Branch Predictor, part of IBC - (stibp)" << endl : std::cout << "EDX bit 27: " << edxBits[27] << ": [UNSUPPORTED] Single Thread Indirect Branch Predictor, part of IBC - (stibp)" << endl;
	(edxBits[28]) ? std::cout << "EDX bit 28: " << edxBits[28] << ": [SUPPORTED] IA32_FLUSH_CMD MSR - L1D_FLUSH" << endl : std::cout << "EDX bit 28: " << edxBits[28] << ": [UNSUPPORTED] IA32_FLUSH_CMD MSR - L1D_FLUSH" << endl;
	(edxBits[29]) ? std::cout << "EDX bit 29: " << edxBits[29] << ": [SUPPORTED] IA32_ARCH_CAPABILITIES MSR (lists speculative side channel mitigations) - (arch_­capabilities)" << endl : std::cout << "EDX bit 29: " << edxBits[29] << ": [UNSUPPORTED] IA32_ARCH_CAPABILITIES MSR (lists speculative side channel mitigations) - (arch_­capabilities)" << endl;
	(edxBits[30]) ? std::cout << "EDX bit 30: " << edxBits[30] << ": [SUPPORTED] IA32_CORE_CAPABILITIES MSR (lists model-specific core capabilities) - (core_­capabilities)" << endl : std::cout << "EDX bit 30: " << edxBits[30] << ": [UNSUPPORTED] IA32_CORE_CAPABILITIES MSR (lists model-specific core capabilities) - (core_­capabilities)" << endl;
	(edxBits[31]) ? std::cout << "EDX bit 31: " << edxBits[31] << ": [SUPPORTED] Speculative Store Bypass Disable, as mitigation for Speculative Store Bypass (IA32_SPEC_CTRL) - (ssbd)" << endl : std::cout << "EDX bit 31: " << edxBits[31] << ": [UNSUPPORTED] Speculative Store Bypass Disable, as mitigation for Speculative Store Bypass (IA32_SPEC_CTRL) - (ssbd)" << endl;
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

	(eaxBits[0]) ? std::cout << "EAX bit 0: " << eaxBits[0] << ": [SUPPORTED] SHA-512 extensions - (sha512)" << endl : std::cout << "EAX bit 0: " << eaxBits[0] << ": [UNSUPPORTED] SHA-512 extensions - (sha512)" << endl;
	(eaxBits[1]) ? std::cout << "EAX bit 1: " << eaxBits[1] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 1: " << eaxBits[1] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[2]) ? std::cout << "EAX bit 2: " << eaxBits[2] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 2: " << eaxBits[2] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[3]) ? std::cout << "EAX bit 3: " << eaxBits[3] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 3: " << eaxBits[3] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[4]) ? std::cout << "EAX bit 4: " << eaxBits[4] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 4: " << eaxBits[4] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[5]) ? std::cout << "EAX bit 5: " << eaxBits[5] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 5: " << eaxBits[5] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[6]) ? std::cout << "EAX bit 6: " << eaxBits[6] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 6: " << eaxBits[6] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[7]) ? std::cout << "EAX bit 7: " << eaxBits[7] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 7: " << eaxBits[7] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[8]) ? std::cout << "EAX bit 8: " << eaxBits[8] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 8: " << eaxBits[8] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[9]) ? std::cout << "EAX bit 9: " << eaxBits[9] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 9: " << eaxBits[9] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[10]) ? std::cout << "EAX bit 10: " << eaxBits[10] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 10: " << eaxBits[10] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[11]) ? std::cout << "EAX bit 11: " << eaxBits[11] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 11: " << eaxBits[11] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[14]) ? std::cout << "EAX bit 14: " << eaxBits[14] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 14: " << eaxBits[14] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[15]) ? std::cout << "EAX bit 15: " << eaxBits[15] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 15: " << eaxBits[15] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[16]) ? std::cout << "EAX bit 16: " << eaxBits[16] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 16: " << eaxBits[16] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[17]) ? std::cout << "EAX bit 17: " << eaxBits[17] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 17: " << eaxBits[17] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[18]) ? std::cout << "EAX bit 18: " << eaxBits[18] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 18: " << eaxBits[18] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[19]) ? std::cout << "EAX bit 19: " << eaxBits[19] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 19: " << eaxBits[19] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[20]) ? std::cout << "EAX bit 20: " << eaxBits[20] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 20: " << eaxBits[20] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[21]) ? std::cout << "EAX bit 21: " << eaxBits[21] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 21: " << eaxBits[21] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[22]) ? std::cout << "EAX bit 22: " << eaxBits[22] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 22: " << eaxBits[22] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[23]) ? std::cout << "EAX bit 23: " << eaxBits[23] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 23: " << eaxBits[23] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[24]) ? std::cout << "EAX bit 24: " << eaxBits[24] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 24: " << eaxBits[24] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[25]) ? std::cout << "EAX bit 25: " << eaxBits[25] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 25: " << eaxBits[25] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[27]) ? std::cout << "EAX bit 27: " << eaxBits[27] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 27: " << eaxBits[27] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[28]) ? std::cout << "EAX bit 28: " << eaxBits[28] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 28: " << eaxBits[28] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[29]) ? std::cout << "EAX bit 29: " << eaxBits[29] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 29: " << eaxBits[29] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[30]) ? std::cout << "EAX bit 30: " << eaxBits[30] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 30: " << eaxBits[30] << ": [UNSUPPORTED] Reserved" << endl;
	(eaxBits[31]) ? std::cout << "EAX bit 31: " << eaxBits[31] << ": [SUPPORTED] Reserved" << endl : std::cout << "EAX bit 31: " << eaxBits[31] << ": [UNSUPPORTED] Reserved" << endl;
	std::cout << endl;

	(ebxBits[0]) ? std::cout << "EBX bit 0: " << ebxBits[0] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 0: " << ebxBits[0] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[1]) ? std::cout << "EBX bit 1: " << ebxBits[1] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 1: " << ebxBits[1] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[2]) ? std::cout << "EBX bit 2: " << ebxBits[2] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 2: " << ebxBits[2] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[3]) ? std::cout << "EBX bit 3: " << ebxBits[3] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 3: " << ebxBits[3] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[4]) ? std::cout << "EBX bit 4: " << ebxBits[4] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 4: " << ebxBits[4] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[5]) ? std::cout << "EBX bit 5: " << ebxBits[5] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 5: " << ebxBits[5] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[6]) ? std::cout << "EBX bit 6: " << ebxBits[6] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 6: " << ebxBits[6] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[7]) ? std::cout << "EBX bit 7: " << ebxBits[7] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 7: " << ebxBits[7] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[8]) ? std::cout << "EBX bit 8: " << ebxBits[8] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 8: " << ebxBits[8] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[9]) ? std::cout << "EBX bit 9: " << ebxBits[9] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 9: " << ebxBits[9] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[10]) ? std::cout << "EBX bit 10: " << ebxBits[10] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 10: " << ebxBits[10] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[11]) ? std::cout << "EBX bit 11: " << ebxBits[11] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 11: " << ebxBits[11] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[12]) ? std::cout << "EBX bit 12: " << ebxBits[12] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 12: " << ebxBits[12] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[13]) ? std::cout << "EBX bit 13: " << ebxBits[13] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 13: " << ebxBits[13] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[14]) ? std::cout << "EBX bit 14: " << ebxBits[14] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 14: " << ebxBits[14] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[15]) ? std::cout << "EBX bit 15: " << ebxBits[15] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 15: " << ebxBits[15] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[16]) ? std::cout << "EBX bit 16: " << ebxBits[16] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 16: " << ebxBits[16] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[17]) ? std::cout << "EBX bit 17: " << ebxBits[17] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 17: " << ebxBits[17] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[18]) ? std::cout << "EBX bit 18: " << ebxBits[18] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 18: " << ebxBits[18] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[19]) ? std::cout << "EBX bit 19: " << ebxBits[19] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 19: " << ebxBits[19] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[20]) ? std::cout << "EBX bit 20: " << ebxBits[20] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 20: " << ebxBits[20] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[21]) ? std::cout << "EBX bit 21: " << ebxBits[21] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 21: " << ebxBits[21] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[22]) ? std::cout << "EBX bit 22: " << ebxBits[22] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 22: " << ebxBits[22] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[23]) ? std::cout << "EBX bit 23: " << ebxBits[23] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 23: " << ebxBits[23] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[24]) ? std::cout << "EBX bit 24: " << ebxBits[24] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 24: " << ebxBits[24] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[25]) ? std::cout << "EBX bit 25: " << ebxBits[25] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 25: " << ebxBits[25] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[26]) ? std::cout << "EBX bit 26: " << ebxBits[26] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 26: " << ebxBits[26] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[27]) ? std::cout << "EBX bit 27: " << ebxBits[27] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 27: " << ebxBits[27] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[28]) ? std::cout << "EBX bit 28: " << ebxBits[28] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 28: " << ebxBits[28] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[29]) ? std::cout << "EBX bit 29: " << ebxBits[29] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 29: " << ebxBits[29] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[30]) ? std::cout << "EBX bit 30: " << ebxBits[30] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 30: " << ebxBits[30] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[31]) ? std::cout << "EBX bit 31: " << ebxBits[31] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 31: " << ebxBits[31] << ": [UNSUPPORTED] Reserved" << endl;
	std::cout << endl;

	(ecxBits[0]) ? std::cout << "ECX bit 0: " << ecxBits[0] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 0: " << ecxBits[0] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[1]) ? std::cout << "ECX bit 1: " << ecxBits[1] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 1: " << ecxBits[1] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[2]) ? std::cout << "ECX bit 2: " << ecxBits[2] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 2: " << ecxBits[2] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[3]) ? std::cout << "ECX bit 3: " << ecxBits[3] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 3: " << ecxBits[3] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[4]) ? std::cout << "ECX bit 4: " << ecxBits[4] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 4: " << ecxBits[4] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[5]) ? std::cout << "ECX bit 5: " << ecxBits[5] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 5: " << ecxBits[5] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[6]) ? std::cout << "ECX bit 6: " << ecxBits[6] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 6: " << ecxBits[6] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[7]) ? std::cout << "ECX bit 7: " << ecxBits[7] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 7: " << ecxBits[7] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[8]) ? std::cout << "ECX bit 8: " << ecxBits[8] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 8: " << ecxBits[8] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[9]) ? std::cout << "ECX bit 9: " << ecxBits[9] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 9: " << ecxBits[9] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[10]) ? std::cout << "ECX bit 10: " << ecxBits[10] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 10: " << ecxBits[10] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[11]) ? std::cout << "ECX bit 11: " << ecxBits[11] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 11: " << ecxBits[11] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[12]) ? std::cout << "ECX bit 12: " << ecxBits[12] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 12: " << ecxBits[12] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[13]) ? std::cout << "ECX bit 13: " << ecxBits[13] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 13: " << ecxBits[13] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[14]) ? std::cout << "ECX bit 14: " << ecxBits[14] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 14: " << ecxBits[14] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[15]) ? std::cout << "ECX bit 15: " << ecxBits[15] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 15: " << ecxBits[15] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[16]) ? std::cout << "ECX bit 16: " << ecxBits[16] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 16: " << ecxBits[16] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[17]) ? std::cout << "ECX bit 17: " << ecxBits[17] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 17: " << ecxBits[17] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[18]) ? std::cout << "ECX bit 18: " << ecxBits[18] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 18: " << ecxBits[18] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[19]) ? std::cout << "ECX bit 19: " << ecxBits[19] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 19: " << ecxBits[19] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[22]) ? std::cout << "ECX bit 22: " << ecxBits[22] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 22: " << ecxBits[22] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[23]) ? std::cout << "ECX bit 23: " << ecxBits[23] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 23: " << ecxBits[23] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[24]) ? std::cout << "ECX bit 24: " << ecxBits[24] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 24: " << ecxBits[24] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[25]) ? std::cout << "ECX bit 25: " << ecxBits[25] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 25: " << ecxBits[25] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[26]) ? std::cout << "ECX bit 26: " << ecxBits[26] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 26: " << ecxBits[26] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[27]) ? std::cout << "ECX bit 27: " << ecxBits[27] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 27: " << ecxBits[27] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[28]) ? std::cout << "ECX bit 28: " << ecxBits[28] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 28: " << ecxBits[28] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[29]) ? std::cout << "ECX bit 29: " << ecxBits[29] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 29: " << ecxBits[29] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[30]) ? std::cout << "ECX bit 30: " << ecxBits[30] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 30: " << ecxBits[30] << ": [UNSUPPORTED] Reserved" << endl;
	(ecxBits[31]) ? std::cout << "ECX bit 31: " << ecxBits[31] << ": [SUPPORTED] Reserved" << endl : std::cout << "ECX bit 31: " << ecxBits[31] << ": [UNSUPPORTED] Reserved" << endl;
	std::cout << endl;

	(edxBits[0]) ? std::cout << "EDX bit 0: " << edxBits[0] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 0: " << edxBits[0] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[1]) ? std::cout << "EDX bit 1: " << edxBits[1] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 1: " << edxBits[1] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[2]) ? std::cout << "EDX bit 2: " << edxBits[2] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 2: " << edxBits[2] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[3]) ? std::cout << "EDX bit 3: " << edxBits[3] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 3: " << edxBits[3] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[4]) ? std::cout << "EDX bit 4: " << edxBits[4] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 4: " << edxBits[4] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[5]) ? std::cout << "EDX bit 5: " << edxBits[5] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 5: " << edxBits[5] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[6]) ? std::cout << "EDX bit 6: " << edxBits[6] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 6: " << edxBits[6] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[7]) ? std::cout << "EDX bit 7: " << edxBits[7] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 7: " << edxBits[7] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[8]) ? std::cout << "EDX bit 8: " << edxBits[8] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 8: " << edxBits[8] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[9]) ? std::cout << "EDX bit 9: " << edxBits[9] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 9: " << edxBits[9] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[10]) ? std::cout << "EDX bit 10: " << edxBits[10] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 10: " << edxBits[10] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[11]) ? std::cout << "EDX bit 11: " << edxBits[11] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 11: " << edxBits[11] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[12]) ? std::cout << "EDX bit 12: " << edxBits[12] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 12: " << edxBits[12] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[13]) ? std::cout << "EDX bit 13: " << edxBits[13] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 13: " << edxBits[13] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[14]) ? std::cout << "EDX bit 14: " << edxBits[14] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 14: " << edxBits[14] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[15]) ? std::cout << "EDX bit 15: " << edxBits[15] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 15: " << edxBits[15] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[16]) ? std::cout << "EDX bit 16: " << edxBits[16] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 16: " << edxBits[16] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[18]) ? std::cout << "EDX bit 18: " << edxBits[18] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 18: " << edxBits[18] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[19]) ? std::cout << "EDX bit 19: " << edxBits[19] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 19: " << edxBits[19] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[22]) ? std::cout << "EDX bit 22: " << edxBits[22] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 22: " << edxBits[22] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[23]) ? std::cout << "EDX bit 23: " << edxBits[23] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 23: " << edxBits[23] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[24]) ? std::cout << "EDX bit 24: " << edxBits[24] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 24: " << edxBits[24] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[25]) ? std::cout << "EDX bit 25: " << edxBits[25] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 25: " << edxBits[25] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[26]) ? std::cout << "EDX bit 26: " << edxBits[26] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 26: " << edxBits[26] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[27]) ? std::cout << "EDX bit 27: " << edxBits[27] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 27: " << edxBits[27] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[28]) ? std::cout << "EDX bit 28: " << edxBits[28] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 28: " << edxBits[28] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[29]) ? std::cout << "EDX bit 29: " << edxBits[29] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 29: " << edxBits[29] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[30]) ? std::cout << "EDX bit 30: " << edxBits[30] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 30: " << edxBits[30] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[31]) ? std::cout << "EDX bit 31: " << edxBits[31] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 31: " << edxBits[31] << ": [UNSUPPORTED] Reserved" << endl;
	std::cout << endl;

	__cpuidex(cpuInfo, 0x7, 0x2);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x7: ECX=0x2 [Extended Features]:" << endl;
	std::cout << "EAX=0x7: [EAX] = " << eaxBits << endl; //Reserved
	std::cout << "EAX=0x7: [EBX] = " << ebxBits << endl; //Reserved
	std::cout << "EAX=0x7: [ECX] = " << ecxBits << endl; //Reserved
	std::cout << "EAX=0x7: [EDX] = " << edxBits << endl;
	std::cout << endl;

	(edxBits[0]) ? std::cout << "EDX bit 0: " << edxBits[0] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 0: " << edxBits[0] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[1]) ? std::cout << "EDX bit 1: " << edxBits[1] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 1: " << edxBits[1] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[2]) ? std::cout << "EDX bit 2: " << edxBits[2] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 2: " << edxBits[2] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[3]) ? std::cout << "EDX bit 3: " << edxBits[3] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 3: " << edxBits[3] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[4]) ? std::cout << "EDX bit 4: " << edxBits[4] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 4: " << edxBits[4] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[5]) ? std::cout << "EDX bit 5: " << edxBits[5] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 5: " << edxBits[5] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[6]) ? std::cout << "EDX bit 6: " << edxBits[6] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 6: " << edxBits[6] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[7]) ? std::cout << "EDX bit 7: " << edxBits[7] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 7: " << edxBits[7] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[8]) ? std::cout << "EDX bit 8: " << edxBits[8] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 8: " << edxBits[8] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[9]) ? std::cout << "EDX bit 9: " << edxBits[9] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 9: " << edxBits[9] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[10]) ? std::cout << "EDX bit 10: " << edxBits[10] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 10: " << edxBits[10] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[11]) ? std::cout << "EDX bit 11: " << edxBits[11] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 11: " << edxBits[11] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[12]) ? std::cout << "EDX bit 12: " << edxBits[12] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 12: " << edxBits[12] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[13]) ? std::cout << "EDX bit 13: " << edxBits[13] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 13: " << edxBits[13] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[14]) ? std::cout << "EDX bit 14: " << edxBits[14] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 14: " << edxBits[14] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[15]) ? std::cout << "EDX bit 15: " << edxBits[15] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 15: " << edxBits[15] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[16]) ? std::cout << "EDX bit 16: " << edxBits[16] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 16: " << edxBits[16] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[18]) ? std::cout << "EDX bit 18: " << edxBits[18] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 18: " << edxBits[18] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[19]) ? std::cout << "EDX bit 19: " << edxBits[19] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 19: " << edxBits[19] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[22]) ? std::cout << "EDX bit 22: " << edxBits[22] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 22: " << edxBits[22] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[23]) ? std::cout << "EDX bit 23: " << edxBits[23] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 23: " << edxBits[23] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[24]) ? std::cout << "EDX bit 24: " << edxBits[24] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 24: " << edxBits[24] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[25]) ? std::cout << "EDX bit 25: " << edxBits[25] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 25: " << edxBits[25] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[26]) ? std::cout << "EDX bit 26: " << edxBits[26] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 26: " << edxBits[26] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[27]) ? std::cout << "EDX bit 27: " << edxBits[27] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 27: " << edxBits[27] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[28]) ? std::cout << "EDX bit 28: " << edxBits[28] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 28: " << edxBits[28] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[29]) ? std::cout << "EDX bit 29: " << edxBits[29] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 29: " << edxBits[29] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[30]) ? std::cout << "EDX bit 30: " << edxBits[30] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 30: " << edxBits[30] << ": [UNSUPPORTED] Reserved" << endl;
	(edxBits[31]) ? std::cout << "EDX bit 31: " << edxBits[31] << ": [SUPPORTED] Reserved" << endl : std::cout << "EDX bit 31: " << edxBits[31] << ": [UNSUPPORTED] Reserved" << endl;
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
	std::cout << "EAX=0x15: [TSC and Core Crystal frequency information]:" << endl;
	std::cout << "EAX=0x15: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x15: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x15: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x15: [EDX] = " << edxBits << endl;
	std::cout << endl;

	std::cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator (EAX) = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[0], 8) << endl;
	//std::cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator (EAX) = " << eaxBits << endl;
	std::cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator (EBX) = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[1], 8) << endl;
	//std::cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator (EBX) = " << ebxBits << endl;
	std::cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz (ECX) = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[2], 8) << endl;
	//std::cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz (ECX) = " << ecxBits << endl;
	std::cout << "EAX=0x15: TSC frequency, in units of Hz (EDX) = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[3], 8) << endl;
	//std::cout << "EAX=0x15: TSC frequency, in units of Hz (EDX) = " << edxBits << endl;
	std::cout << endl;

	__cpuidex(cpuInfo, 0x16, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x16: [Processor and Bus specification frequencies]:" << endl;
	std::cout << "EAX=0x16: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x16: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x16: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x16: [EDX] = " << edxBits << endl;
	std::cout << endl;

	
	std::cout << "EAX=0x16: Processor Base Frequency (in MHz): EAX Bits 15:0 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[0], 0, 16), 8) << endl;
	//std::cout << "EAX=0x16: Processor Base Frequency (in MHz): EAX Bits 15:0 = " << extractBits(eaxBits[0], 0, 16) << endl;
	std::cout << "EAX=0x16: Reserved: EAX Bits 31:16 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[0], 16, 16), 8) << endl;
	//std::cout << "EAX=0x16: Reserved: EAX Bits 31:16 = " << extractBits(eaxBits[0], 16, 16) << endl;

	std::cout << "EAX=0x16: Processor Maximum Frequency (in MHz): EBX Bits 15:0 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[1], 0, 16), 8) << endl;
	//std::cout << "EAX=0x16: Processor Maximum Frequency (in MHz): EBX Bits 15:0 = " << extractBits(ebxBits[0], 0, 16) << endl;
	std::cout << "EAX=0x16: Reserved: EBX Bits 31:16 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[1], 16, 16), 8) << endl;
	//std::cout << "EAX=0x16: Reserved: EBX Bits 31:16 = " << extractBits(ebxBits[0], 16, 16) << endl;

	std::cout << "EAX=0x16: Bus/Reference frequency (in MHz): ECX Bits 15:0 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[2], 0, 16), 8) << endl;
	//std::cout << "EAX=0x16: Bus/Reference frequency (in MHz): ECX Bits 15:0 = " << extractBits(ecxBits[0], 0, 16) << endl;
	std::cout << "EAX=0x16: Reserved: ECX Bits 31:16 = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[2], 16, 16), 8) << endl;
	//std::cout << "EAX=0x16: Reserved: ECX Bits 31:16 = " << extractBits(ecxBits[0], 16, 16) << endl;

	std::cout << "EAX=0x16: Reserved: EDX = " << std::hex << "0x" << ZeroPadNumber(cpuInfo[3], 8) << endl;
	//std::cout << "EAX=0x16: Reserved: EDX = " << edxBits << endl;
	std::cout << endl;







	// EAX=17h: SoC Vendor Attribute Enumeration
	__cpuidex(cpuInfo, 0x17, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x17: [SoC Vendor Attribute Enumeration]:" << endl;
	std::cout << "EAX=0x17: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x17: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x17: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x17: [EDX] = " << edxBits << endl;
	std::cout << endl;

	// EAX=18h: TLB Hierarchy and Topology
	__cpuidex(cpuInfo, 0x18, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x18: [TLB Hierarchy and Topology]:" << endl;
	std::cout << "EAX=0x18: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x18: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x18: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x18: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=19h: Intel Key Locker Features
	__cpuidex(cpuInfo, 0x19, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x19: [Intel Key Locker Features]:" << endl;
	std::cout << "EAX=0x19: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x19: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x19: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x19: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=1Dh: Intel AMX Tile Information
	__cpuidex(cpuInfo, 0x1D, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x1D: [Intel AMX Tile Information]:" << endl;
	std::cout << "EAX=0x1D: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x1D: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x1D: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x1D: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=1Eh: Intel AMX Tile Multiplier (TMUL) Information
	__cpuidex(cpuInfo, 0x1E, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x1E: [Intel AMX Tile Multiplier (TMUL) Information]:" << endl;
	std::cout << "EAX=0x1E: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x1E: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x1E: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x1E: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=21h: Reserved for TDX enumeration
	__cpuidex(cpuInfo, 0x21, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x21: [Reserved for TDX enumeration]:" << endl;
	std::cout << "EAX=0x21: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x21: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x21: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x21: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=24h, ECX=0: AVX10 Converged Vector ISA
	__cpuidex(cpuInfo, 0x24, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x24: [AVX10 Converged Vector ISA]:" << endl;
	std::cout << "EAX=0x24: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x24: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x24: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x24: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=24h, ECX=1: Discrete AVX10 Features
	__cpuidex(cpuInfo, 0x24, 1);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x24, ECX=1: [Discrete AVX10 Features]:" << endl;
	std::cout << "EAX=0x24, ECX=1: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x24, ECX=1: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x24, ECX=1: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x24, ECX=1: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=2000'0000h: Highest Xeon Phi Function Implemented
	__cpuidex(cpuInfo, 0x20000000, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x20000000: [Highest Xeon Phi Function Implemented]:" << endl;
	std::cout << "EAX=0x20000000: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x20000000: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x20000000: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x20000000: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=2000'0001h: Xeon Phi Feature Bits
	__cpuidex(cpuInfo, 0x20000001, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x20000001: [Xeon Phi Feature Bits]:" << endl;
	std::cout << "EAX=0x20000001: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x20000001: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x20000001: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x20000001: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=4000'0000h-4FFFF'FFFh: Reserved for Hypervisors
	__cpuidex(cpuInfo, 0x40000000, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x40000000: [Reserved for Hypervisors]:" << endl;
	std::cout << "EAX=0x40000000: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x40000000: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x40000000: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x40000000: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'0000h: Highest Extended Function Implemented
	__cpuidex(cpuInfo, 0x80000000, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	int pbsFeatureAvailable = cpuInfo[0];
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000000: [Highest Extended Function Implemented]:" << endl;
	std::cout << "EAX=0x80000000: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000000: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000000: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000000: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'0001h: Extended Processor Info and Feature Bits
	__cpuidex(cpuInfo, 0x80000001, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000001: [Extended Processor Info and Feature Bits]:" << endl;
	std::cout << "EAX=0x80000001: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000001: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000001: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000001: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'0002h,8000'0003h,8000'0004h: Processor Brand String
	__cpuidex(cpuInfo, 0x80000002, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000002: [Processor Brand String]:" << endl;
	std::cout << "EAX=0x80000002: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000002: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000002: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000002: [EDX] = " << edxBits << endl;
	std::cout << endl;

	unsigned int regs[12];
	char str[sizeof(regs) + 1];
	regs[0] = cpuInfo[0];
	regs[1] = cpuInfo[1];
	regs[2] = cpuInfo[2];
	regs[3] = cpuInfo[3];

	__cpuidex(cpuInfo, 0x80000003, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000003: [Processor Brand String]:" << endl;
	std::cout << "EAX=0x80000003: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000003: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000003: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000003: [EDX] = " << edxBits << endl;
	std::cout << endl;

	regs[4] = cpuInfo[0];
	regs[5] = cpuInfo[1];
	regs[6] = cpuInfo[2];
	regs[7] = cpuInfo[3];

	__cpuidex(cpuInfo, 0x80000004, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000004: [Processor Brand String]:" << endl;
	std::cout << "EAX=0x80000004: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000004: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000004: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000004: [EDX] = " << edxBits << endl;
	std::cout << endl;

	regs[8] = cpuInfo[0];
	regs[9] = cpuInfo[1];
	regs[10] = cpuInfo[2];
	regs[11] = cpuInfo[3];

	if (pbsFeatureAvailable >= 0x80000004)
	{
		memcpy(str, regs, sizeof(regs));
		str[sizeof(regs)] = '\0';
		std::cout << "Processor Brand String: " << str << endl;
	}
	else
	{
		std::cout << "Processor Brand String: Not available (not supported)" << endl;
	}
	std::cout << endl;
	
	// EAX=8000'0005h: L1 Cache and TLB Identifiers
	__cpuidex(cpuInfo, 0x80000005, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000005: [L1 Cache and TLB Identifiers]:" << endl;
	std::cout << "EAX=0x80000005: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000005: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000005: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000005: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'0006h: Extended L2 Cache Features
	__cpuidex(cpuInfo, 0x80000006, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000006: [Extended L2 Cache Features]:" << endl;
	std::cout << "EAX=0x80000006: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000006: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000006: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000006: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'0007h: Processor Power Management Information and RAS Capabilities
	__cpuidex(cpuInfo, 0x80000007, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000007: [Processor Power Management Information and RAS Capabilities]:" << endl;
	std::cout << "EAX=0x80000007: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000007: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000007: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000007: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'0008h: Virtual and Physical Address Sizes
	__cpuidex(cpuInfo, 0x80000008, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000008: [Virtual and Physical Address Sizes]:" << endl;
	std::cout << "EAX=0x80000008: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000008: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000008: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000008: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	std::cout << "EAX=0x80000008: [Size and range fields in EAX]:" << endl;
	std::cout << "EAX=0x80000008: EAX Bits 7:0: Number of Physical Address Bits = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[0], 0, 8), 8) << endl;
	//std::cout << "EAX=0x80000008: EAX Bits 7:0: Number of Physical Address Bits = " << extractBits(cpuInfo[0], 0, 8) << endl;
	std::cout << "EAX=0x80000008: EAX Bits 15:8: Number of Linear Address Bits = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[0], 8, 8), 8) << endl;
	//std::cout << "EAX=0x80000008: EAX Bits 15:8: Number of Linear Address Bits = " << extractBits(cpuInfo[0], 8, 8) << endl;
	std::cout << "EAX=0x80000008: EAX Bits 23:16: Guest Physical Address Size = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[0], 16, 8), 8) << endl;
	//std::cout << "EAX=0x80000008: EAX Bits 23:16: Guest Physical Address Size = " << extractBits(cpuInfo[0], 16, 8) << endl;
	std::cout << "EAX=0x80000008: EAX Bits 31:24:Reserved = " << std::hex << "0x" << ZeroPadNumber(extractBits(cpuInfo[0], 24, 8), 8) << endl;
	//std::cout << "EAX=0x80000008: EAX Bits 31:24:Reserved = " << extractBits(cpuInfo[0], 24, 8) << endl;
	std::cout << endl;

	std::cout << "EAX=0x80000008: [Feature bits in EBX ]:" << endl;
	(ebxBits[0]) ? std::cout << "EBX bit 0: " << ebxBits[0] << ": [SUPPORTED] CLZERO instruction - (clzero)" << endl : std::cout << "EBX bit 0: " << ebxBits[0] << ": [UNSUPPORTED] CLZERO instruction - (clzero)" << endl;
	(ebxBits[1]) ? std::cout << "EBX bit 1: " << ebxBits[1] << ": [SUPPORTED] Retired instruction count MSR (C000_00E9h) supported - (retired_instr)" << endl : std::cout << "EBX bit 1: " << ebxBits[1] << ": [UNSUPPORTED] Retired instruction count MSR (C000_00E9h) supported - (retired_instr)" << endl;
	(ebxBits[2]) ? std::cout << "EBX bit 2: " << ebxBits[2] << ": [SUPPORTED] XRSTOR restores FP errors - (xrstor_fp_err)" << endl : std::cout << "EBX bit 2: " << ebxBits[2] << ": [UNSUPPORTED] XRSTOR restores FP errors - (xrstor_fp_err)" << endl;
	(ebxBits[3]) ? std::cout << "EBX bit 3: " << ebxBits[3] << ": [SUPPORTED] INVLPGB and TLBSYNC instructions - (invlpgb)" << endl : std::cout << "EBX bit 3: " << ebxBits[3] << ": [UNSUPPORTED] INVLPGB and TLBSYNC instructions - (invlpgb)" << endl;
	(ebxBits[4]) ? std::cout << "EBX bit 4: " << ebxBits[4] << ": [SUPPORTED] RDPRU instruction - (rdpru)" << endl : std::cout << "EBX bit 4: " << ebxBits[4] << ": [UNSUPPORTED] RDPRU instruction - (rdpru)" << endl;
	(ebxBits[5]) ? std::cout << "EBX bit 5: " << ebxBits[5] << ": [SUPPORTED] (PlayStation 5: Execute-Only Memory) - (xotext)" << endl : std::cout << "EBX bit 5: " << ebxBits[5] << ": [UNSUPPORTED] (PlayStation 5: Execute-Only Memory) - (xotext)" << endl;
	(ebxBits[6]) ? std::cout << "EBX bit 6: " << ebxBits[6] << ": [SUPPORTED] Memory Bandwidth Enforcement - (mbe)" << endl : std::cout << "EBX bit 6: " << ebxBits[6] << ": [UNSUPPORTED] Memory Bandwidth Enforcement - (mbe)" << endl;
	(ebxBits[7]) ? std::cout << "EBX bit 7: " << ebxBits[7] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 7: " << ebxBits[7] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[8]) ? std::cout << "EBX bit 8: " << ebxBits[8] << ": [SUPPORTED] MCOMMIT instruction - (mcommit)" << endl : std::cout << "EBX bit 8: " << ebxBits[8] << ": [UNSUPPORTED] MCOMMIT instruction - (mcommit)" << endl;
	(ebxBits[9]) ? std::cout << "EBX bit 9: " << ebxBits[9] << ": [SUPPORTED] WBNOINVD instruction - (wbnoinvd)" << endl : std::cout << "EBX bit 9: " << ebxBits[9] << ": [UNSUPPORTED] WBNOINVD instruction - (wbnoinvd)" << endl;
	(ebxBits[10]) ? std::cout << "EBX bit 10: " << ebxBits[10] << ": [SUPPORTED] LBR extensions v1 - (LBR_EXT_V1)" << endl : std::cout << "EBX bit 10: " << ebxBits[10] << ": [UNSUPPORTED] LBR extensions v1 - (LBR_EXT_V1)" << endl;
	(ebxBits[11]) ? std::cout << "EBX bit 11: " << ebxBits[11] << ": [SUPPORTED] Reserved" << endl : std::cout << "EBX bit 11: " << ebxBits[11] << ": [UNSUPPORTED] Reserved" << endl;
	(ebxBits[12]) ? std::cout << "EBX bit 12: " << ebxBits[12] << ": [SUPPORTED] Indirect Branch Prediction Barrier (performed by writing 1 to bit 0 of PRED_CMD (MSR 049h)) - (IBPB)" << endl : std::cout << "EBX bit 12: " << ebxBits[12] << ": [UNSUPPORTED] Indirect Branch Prediction Barrier (performed by writing 1 to bit 0 of PRED_CMD (MSR 049h)) - (IBPB)" << endl;
	(ebxBits[13]) ? std::cout << "EBX bit 13: " << ebxBits[13] << ": [SUPPORTED] WBINVD and WBNOINVD are interruptible - (wbinvd_int)" << endl : std::cout << "EBX bit 13: " << ebxBits[13] << ": [UNSUPPORTED] WBINVD and WBNOINVD are interruptible - (wbinvd_int)" << endl;
	(ebxBits[14]) ? std::cout << "EBX bit 14: " << ebxBits[14] << ": [SUPPORTED] Indirect Branch Restricted Speculation - (IBRS)" << endl : std::cout << "EBX bit 14: " << ebxBits[14] << ": [UNSUPPORTED] Indirect Branch Restricted Speculation - (IBRS)" << endl;
	(ebxBits[15]) ? std::cout << "EBX bit 15: " << ebxBits[15] << ": [SUPPORTED] Single Thread Indirect Branch Prediction mode - (STIBP)" << endl : std::cout << "EBX bit 15: " << ebxBits[15] << ": [UNSUPPORTED] Single Thread Indirect Branch Prediction mode - (STIBP)" << endl;
	(ebxBits[16]) ? std::cout << "EBX bit 16: " << ebxBits[16] << ": [SUPPORTED] IBRS mode has enhanced performance and should be left always on - (IbrsAlwaysOn)" << endl : std::cout << "EBX bit 16: " << ebxBits[16] << ": [UNSUPPORTED] IBRS mode has enhanced performance and should be left always on - (IbrsAlwaysOn)" << endl;
	(ebxBits[17]) ? std::cout << "EBX bit 17: " << ebxBits[17] << ": [SUPPORTED] STIBP mode has enhanced performance and should be left always on - (STIBPAlwaysOn)" << endl : std::cout << "EBX bit 17: " << ebxBits[17] << ": [UNSUPPORTED] STIBP mode has enhanced performance and should be left always on - (STIBPAlwaysOn)" << endl;
	(ebxBits[18]) ? std::cout << "EBX bit 18: " << ebxBits[18] << ": [SUPPORTED] IBRS preferred over software - (ibrs_preferred)" << endl : std::cout << "EBX bit 18: " << ebxBits[18] << ": [UNSUPPORTED] IBRS preferred over software - (ibrs_preferred)" << endl;
	(ebxBits[19]) ? std::cout << "EBX bit 19: " << ebxBits[19] << ": [SUPPORTED] IBRS provides Same Mode Protection - (ibrs_same_mode_protection)" << endl : std::cout << "EBX bit 19: " << ebxBits[19] << ": [UNSUPPORTED] IBRS provides Same Mode Protection - (ibrs_same_mode_protection)" << endl;
	(ebxBits[20]) ? std::cout << "EBX bit 20: " << ebxBits[20] << ": [SUPPORTED] EFER.LMSLE is unsupported - (no_efer_lmsle)" << endl : std::cout << "EBX bit 20: " << ebxBits[20] << ": [UNSUPPORTED] EFER.LMSLE is unsupported - (no_efer_lmsle)" << endl;
	(ebxBits[21]) ? std::cout << "EBX bit 21: " << ebxBits[21] << ": [SUPPORTED] INVLPGB support for nested pages - (invlpgb_nested)" << endl : std::cout << "EBX bit 21: " << ebxBits[21] << ": [UNSUPPORTED] INVLPGB support for nested pages - (invlpgb_nested)" << endl;
	(ebxBits[22]) ? std::cout << "EBX bit 22: " << ebxBits[22] << ": [SUPPORTED] (LBR TSX info) - (LBR_TSX)" << endl : std::cout << "EBX bit 22: " << ebxBits[22] << ": [UNSUPPORTED] (LBR TSX info) - (LBR_TSX)" << endl;
	(ebxBits[23]) ? std::cout << "EBX bit 23: " << ebxBits[23] << ": [SUPPORTED] Protected Processor Inventory Number - PPIN_CTL(C001_02F0) and PPIN(C001_02F1) MSRs are present - (ppin)" << endl : std::cout << "EBX bit 23: " << ebxBits[23] << ": [UNSUPPORTED] Protected Processor Inventory Number - PPIN_CTL(C001_02F0) and PPIN(C001_02F1) MSRs are present - (ppin)" << endl;
	(ebxBits[24]) ? std::cout << "EBX bit 24: " << ebxBits[24] << ": [SUPPORTED] Speculative Store Bypass Disable - (ssbd)" << endl : std::cout << "EBX bit 24: " << ebxBits[24] << ": [UNSUPPORTED] Speculative Store Bypass Disable - (ssbd)" << endl;
	(ebxBits[25]) ? std::cout << "EBX bit 25: " << ebxBits[25] << ": [SUPPORTED] Speculative Store Bypass Disable Legacy - (ssbd_legacy)" << endl : std::cout << "EBX bit 25: " << ebxBits[25] << ": [UNSUPPORTED] Speculative Store Bypass Disable Legacy - (ssbd_legacy)" << endl;
	(ebxBits[26]) ? std::cout << "EBX bit 26: " << ebxBits[26] << ": [SUPPORTED] Speculative Store Bypass Disable Not Required - (ssbd_no)" << endl : std::cout << "EBX bit 26: " << ebxBits[26] << ": [UNSUPPORTED] Speculative Store Bypass Disable Not Required - (ssbd_no)" << endl;
	(ebxBits[27]) ? std::cout << "EBX bit 27: " << ebxBits[27] << ": [SUPPORTED] Collaborative Processor Performance Control - (cppc)" << endl : std::cout << "EBX bit 27: " << ebxBits[27] << ": [UNSUPPORTED] Collaborative Processor Performance Control - (cppc)" << endl;
	(ebxBits[28]) ? std::cout << "EBX bit 28: " << ebxBits[28] << ": [SUPPORTED] Predictive Store Forward Disable - (psfd)" << endl : std::cout << "EBX bit 28: " << ebxBits[28] << ": [UNSUPPORTED] Predictive Store Forward Disable - (psfd)" << endl;
	(ebxBits[29]) ? std::cout << "EBX bit 29: " << ebxBits[29] << ": [SUPPORTED] Branch Type Confusion: Processor not affected - (btc_no)" << endl : std::cout << "EBX bit 29: " << ebxBits[29] << ": [UNSUPPORTED] Branch Type Confusion: Processor not affected - (btc_no)" << endl;
	(ebxBits[30]) ? std::cout << "EBX bit 30: " << ebxBits[30] << ": [SUPPORTED] IBPB (see bit 12) also clears return address predictor - (IBPB_RET)" << endl : std::cout << "EBX bit 30: " << ebxBits[30] << ": [UNSUPPORTED] IBPB (see bit 12) also clears return address predictor - (IBPB_RET)" << endl;
	(ebxBits[31]) ? std::cout << "EBX bit 31: " << ebxBits[31] << ": [SUPPORTED] Branch Sampling Support - (branch_sampling)" << endl : std::cout << "EBX bit 31: " << ebxBits[31] << ": [UNSUPPORTED] Branch Sampling Support - (branch_sampling)" << endl;
	std::cout << endl;











	// EAX=8000'000Ah: SVM features
	__cpuidex(cpuInfo, 0x8000000A, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x8000000A: [SVM features]:" << endl;
	std::cout << "EAX=0x8000000A: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x8000000A: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x8000000A: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x8000000A: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'001Fh: Encrypted Memory Capabilities
	__cpuidex(cpuInfo, 0x8000001F, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x8000001F: [Encrypted Memory Capabilities]:" << endl;
	std::cout << "EAX=0x8000001F: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x8000001F: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x8000001F: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x8000001F: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'0021h: Extended Feature Identification
	__cpuidex(cpuInfo, 0x80000021, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000021: [Extended Feature Identification]:" << endl;
	std::cout << "EAX=0x80000021: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000021: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000021: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000021: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8000'0025h: Encrypted Memory Capabilities 2
	__cpuidex(cpuInfo, 0x80000025, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x80000025: [Encrypted Memory Capabilities 2]:" << endl;
	std::cout << "EAX=0x80000025: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x80000025: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x80000025: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x80000025: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8C86'0000h: Hygon Extended Feature Flags
	__cpuidex(cpuInfo, 0x8C860000, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x8C860000: [Hygon Extended Feature Flags]:" << endl;
	std::cout << "EAX=0x8C860000: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x8C860000: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x8C860000: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x8C860000: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=8FFF'FFFEh and EAX=8FFF'FFFFh: AMD Easter Eggs
	__cpuidex(cpuInfo, 0x8FFFFFFE, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x8FFFFFFE: [AMD Easter Eggs]:" << endl;
	std::cout << "EAX=0x8FFFFFFE: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x8FFFFFFE: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x8FFFFFFE: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x8FFFFFFE: [EDX] = " << edxBits << endl;
	std::cout << endl;

	unsigned int regsEaster[4];
	char strEaster[sizeof(regsEaster) + 1];
	regsEaster[0] = cpuInfo[0];
	regsEaster[1] = cpuInfo[1];
	regsEaster[2] = cpuInfo[2];
	regsEaster[3] = cpuInfo[3];
	memcpy(strEaster, regsEaster, sizeof(regsEaster));
	strEaster[sizeof(regsEaster)] = '\0';

	std::cout << "Easter Egg String 0x8FFFFFFE: " << strEaster << endl;
	std::cout << "Easter Egg String 0x8FFFFFFE EAX: " << regsEaster[0] << " " << strEaster[0] << endl;
	std::cout << "Easter Egg String 0x8FFFFFFE EBX: " << regsEaster[1] << " " << strEaster[1] << endl;
	std::cout << "Easter Egg String 0x8FFFFFFE ECX: " << regsEaster[2] << " " << strEaster[2] << endl;
	std::cout << "Easter Egg String 0x8FFFFFFE EDX: " << regsEaster[3] << " " << strEaster[3] << endl;
	std::cout << endl;

	__cpuidex(cpuInfo, 0x8FFFFFFF, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0x8FFFFFFF: [AMD Easter Eggs]:" << endl;
	std::cout << "EAX=0x8FFFFFFF: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0x8FFFFFFF: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0x8FFFFFFF: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0x8FFFFFFF: [EDX] = " << edxBits << endl;
	std::cout << endl;

	unsigned int regsEaster2[4];
	char strEaster2[sizeof(regsEaster2) + 1];
	regsEaster2[0] = cpuInfo[0];
	regsEaster2[1] = cpuInfo[1];
	regsEaster2[2] = cpuInfo[2];
	regsEaster2[3] = cpuInfo[3];
	memcpy(strEaster2, regsEaster2, sizeof(regsEaster2));
	strEaster2[sizeof(regsEaster2)] = '\0';

	std::cout << "Easter Egg String 0x8FFFFFFF: " << strEaster2 << endl;
	std::cout << "Easter Egg String 0x8FFFFFFF EAX: " << regsEaster2[0] << " " << strEaster2[0] << endl;
	std::cout << "Easter Egg String 0x8FFFFFFF EBX: " << regsEaster2[1] << " " << strEaster2[1] << endl;
	std::cout << "Easter Egg String 0x8FFFFFFF ECX: " << regsEaster2[2] << " " << strEaster2[2] << endl;
	std::cout << "Easter Egg String 0x8FFFFFFF EDX: " << regsEaster2[3] << " " << strEaster2[3] << endl;
	std::cout << endl;
	
	// EAX=C000'0000h: Highest Centaur Extended Function
	__cpuidex(cpuInfo, 0xC0000000, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0xC0000000: [Highest Centaur Extended Function]:" << endl;
	std::cout << "EAX=0xC0000000: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0xC0000000: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0xC0000000: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0xC0000000: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=C000'0001h: Centaur Feature Information
	__cpuidex(cpuInfo, 0xC0000001, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0xC0000001: [Centaur Feature Information]:" << endl;
	std::cout << "EAX=0xC0000001: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0xC0000001: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0xC0000001: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0xC0000001: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=C000'0002h: Centaur Extended CPUID Performance Data
	__cpuidex(cpuInfo, 0xC0000002, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0xC0000002: [Centaur Extended CPUID Performance Data]:" << endl;
	std::cout << "EAX=0xC0000002: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0xC0000002: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0xC0000002: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0xC0000002: [EDX] = " << edxBits << endl;
	std::cout << endl;
	
	// EAX=C000'0006h, ECX=0: Zhaoxin Feature Information
	__cpuidex(cpuInfo, 0xC0000006, 0);
	eaxBits = bitset<32>(cpuInfo[0]);
	ebxBits = bitset<32>(cpuInfo[1]);
	ecxBits = bitset<32>(cpuInfo[2]);
	edxBits = bitset<32>(cpuInfo[3]);
	std::cout << "EAX=0xC0000006: [Zhaoxin Feature Information]:" << endl;
	std::cout << "EAX=0xC0000006: [EAX] = " << eaxBits << endl;
	std::cout << "EAX=0xC0000006: [EBX] = " << ebxBits << endl;
	std::cout << "EAX=0xC0000006: [ECX] = " << ecxBits << endl;
	std::cout << "EAX=0xC0000006: [EDX] = " << edxBits << endl;
	std::cout << endl;






	return 0;
}


