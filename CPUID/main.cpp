#include "CPUID.h"

#include <iostream>
#include <string>
#include <bitset>

using namespace std;

unsigned int extractBits(unsigned int num, unsigned int pos,
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

	//cout << "EAX=1: Feature Bits: EDX = " << std::hex << "0x" << cpuID1.EDX() << endl;
	cout << "EAX=1: Feature Bits: EDX = " << bitset<32>(cpuID1.EDX()) << endl;
	//cout << "EAX=1: Feature Bits: ECX = " << std::hex << "0x" << cpuID1.ECX() << endl;
	cout << "EAX=1: Feature Bits: ECX = " << bitset<32>(cpuID1.ECX()) << endl;
	//cout << "EAX=1: Additional Information: EBX = " << std::hex << "0x" << cpuID1.EBX() << endl;
	cout << "EAX=1: Additional Information: EBX = " << bitset<32>(cpuID1.EBX()) << endl;
	//cout << "EAX=1: Processor Family IDs: EAX = " << std::hex << "0x" << cpuID1.EAX() << endl;
	cout << "EAX=1: Processor Family IDs: EAX = " << bitset<32>(cpuID1.EAX()) << endl;
	cout << "EAX=1: Stepping ID: EAX Bits 3:0 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 0, 4) << endl;

	unsigned int modelId = extractBits(cpuID1.EAX(), 4, 4);
	unsigned int familyId = extractBits(cpuID1.EAX(), 8, 4);
	unsigned int extendedModelId = extractBits(cpuID1.EAX(), 16, 4);

	cout << "EAX=1: Family ID: EAX Bits 8:11 = " << std::hex << "0x" << familyId << endl;
	cout << "EAX=1: Model: EAX Bits 4:7 = " << std::hex << "0x" << modelId << endl;
	if (familyId == 0x6 || familyId == 0xF)
	{
		unsigned int extendedModelIdLeftShifted = extendedModelId << 4;
		unsigned int processorModel = modelId + extendedModelIdLeftShifted;
		cout << "Extended Model ID left-shifted by 4 bits: " << std::hex << "0x" << extendedModelIdLeftShifted << endl;
		cout << "EAX=1: Actual Model: Model (EAX Bits 4:7) + (Extended Model Id (EAX Bits 16:19) << 4)  = " << std::hex << "0x" << processorModel << endl;
	}

	cout << "EAX=1: Processor Type: EAX Bits 12:13 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 12, 2) << endl;
	cout << "EAX=1: Reserved: EAX Bits 14:15 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 14, 2) << endl;
	cout << "EAX=1: Extended Model ID: EAX Bits 16:19 = " << std::hex << "0x" << extendedModelId << endl;
	cout << "EAX=1: Extended Family ID: EAX Bits 20:27 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 20, 8) << endl;
	cout << "EAX=1: Reserved: EAX Bits 28:31 = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 28, 4) << endl;

	cout << endl;

	CPUID cpuID16(0x16);

	cout << "EAX=0x16: Processor and Bus specification frequencies:";
	cout << "EAX=0x16: Reserved: EDX = " << std::hex << "0x" << cpuID16.EDX() << endl;
	cout << "EAX=0x16: Processor Base Frequency (in MHz): EAX Bits 15:0 = " << std::hex << "0x" << cpuID16.EAX() << endl;
	cout << "EAX=0x16: Processor Maximum Frequency (in MHz: EBX Bits 15:0 = " << std::hex << "0x" << cpuID16.EBX() << endl;
	cout << "EAX=0x16: Bus/Reference frequency (in MHz: ECX Bits 15:0 = " << std::hex << "0x" << cpuID16.ECX() << endl;
	cout << endl;

	return 0;
}


