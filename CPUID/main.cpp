#include "CPUID.h"

#include <iostream>
#include <string>
#include <bitset>

using namespace std;

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
	cout << "EAX=1: Feature Bits: EDX = " << edxBits << endl;
	//cout << "EAX=1: Feature Bits: ECX = " << std::hex << "0x" << cpuID1.ECX() << endl;
	cout << "EAX=1: Feature Bits: ECX = " << ecxBits << endl;
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



	cout << "EAX=1: EBX Additional Information" << endl;
	cout << "EBX bits 7:0 Brand Index = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 0, 8) << endl;
	cout << "EBX bits 15:8 CLFLUSH line size (Value * 8 = cache line size in bytes) = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 8, 8) << endl;
	cout << "EBX bits 23:16 Maximum number of addressable IDs for logical processors in this physical package = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 16, 8) << endl;
	cout << "EBX bits 31:24 Local APIC ID: The initial APIC-ID is used to identify the executing logical processor = " << std::hex << "0x" << extractBits(cpuID1.EAX(), 24, 8) << endl;
	cout << endl;



	cout << "EAX=1: ECX feature bits" << endl;
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



	cout << "EAX=1: EDX feature bits" << endl;
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
	

	// EAX=2: Cache and TLB Descriptor Information
	CPUID cpuID2(0x2);
	eaxBits = bitset<32>(cpuID2.EAX());
	ebxBits = bitset<32>(cpuID2.EBX());
	ecxBits = bitset<32>(cpuID2.ECX());
	edxBits = bitset<32>(cpuID2.EDX());


	cout << "EAX=0x2: Cache and TLB Descriptor Information = " << std::hex << "0x" << cpuID2.EAX() << endl;
	cout << "EAX=0x2: Cache and TLB Descriptor Information = " << std::hex << "0x" << cpuID2.EBX() << endl;
	cout << "EAX=0x2: Cache and TLB Descriptor Information = " << std::hex << "0x" << cpuID2.ECX() << endl;
	cout << "EAX=0x2: Cache and TLB Descriptor Information = " << std::hex << "0x" << cpuID2.EDX() << endl;
	cout << endl;

	// EAX = 15h and EAX = 16h: CPU, TSC, Bus and Core Crystal Clock Frequencies
	CPUID cpuID15(0x15);
	eaxBits = bitset<32>(cpuID15.EAX());
	ebxBits = bitset<32>(cpuID15.EBX());
	ecxBits = bitset<32>(cpuID15.ECX());
	edxBits = bitset<32>(cpuID15.EDX());

	cout << "EAX=0x15: TSC and Core Crystal frequency information :" << endl;
	if (eaxBits[31]) // Check if EAX bit 31 is set
	{
		cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator = " << std::hex << "0x" << cpuID15.EAX() << endl;
		cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, denominator = " << eaxBits << endl;
	}
	else
	{
		cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency is not enumerated" << endl;
	}
	
	if (ebxBits[31]) // Check if EBX bit 31 is set
	{
		cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator = " << std::hex << "0x" << cpuID15.EBX() << endl;
		cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency, numerator = " << ebxBits << endl;
	}
	else
	{
		cout << "EAX=0x15: Ratio of TSC frequency to Core Crystal Clock frequency is not enumerated" << endl;
	}

	if (ecxBits[31]) // Check if ECX bit 31 is set
	{
		 cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz = " << std::hex << "0x" << cpuID15.ECX() << endl;
		 cout << "EAX=0x15: Core Crystal Clock frequency, in units of Hz = " << ecxBits << endl;
	}
	else
	{
		cout << "EAX=0x15: Core Crystal Clock frequency is not enumerated" << endl;
	}

	if (edxBits[31]) // Check if EDX bit 31 is set
	{
		cout << "EAX=0x15: TSC frequency, in units of Hz = " << std::hex << "0x" << cpuID15.EDX() << endl;
		cout << "EAX=0x15: TSC frequency, in units of Hz = " << edxBits << endl;
	}
	else
	{
		cout << "EAX=0x15: TSC frequency is not enumerated" << endl;
	}
	
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


