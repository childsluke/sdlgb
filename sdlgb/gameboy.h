// IMPLEMENTATION OF GAME BOY CPU, MEMORY, and PPU.
// ASSISTANCE VIA:
// https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf
// https://gbdev.github.io/list.html
// https://gekkio.fi/files/gb-docs/gbctr.pdf

#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <vector>

namespace gameboy
{

	class GbCpu
	{
		friend class Gameboy;
		friend class GbMem;

	private:

		// Registers	

		// Per programming manual codes, registers are referenced via 0-7 3 bits in opcodes
		const char REGISTER_A = 0b111;
		const char REGISTER_B = 0b000;
		const char REGISTER_C = 0b001;
		const char REGISTER_D = 0b010;
		const char REGISTER_E = 0b011;
		const char REGISTER_H = 0b100;
		const char REGISTER_L = 0b101;
		
		
		union Register
		{
			Register();
			Register(unsigned short initValue);
			unsigned short reg;
			struct
			{
				unsigned char lo;
				unsigned char hi;
			};
		};

		Register rAF_, rBC_, rDE_, rHL_;
		unsigned char* rA_, * rF_, * rB_, * rC_, * rD_, * rE_, * rH_, * rL_;
		
		unsigned short *SP_, *PC_; // Stack pointer & program counter

		// Flag registers
		// (We will read in the upper 4 bits of the F register into these bools as our flags on each cycle)
		bool fC4_, fH5_, fN6_, fZ7_;
		// Bit 4 C, Bit 5, H, Bit 6 N, Bit 7 Z;

		bool imeFlag_;

		// Stack functions - stack grows from TOP TO BOTTOM on the Game Boy!
		const unsigned short END_STACK_LOCATION = 0xFF80;
		const unsigned short START_STACK_LOCATION = 0xFFFE;
		void push(unsigned char byteToPush);
		void pop();

		// To 'simulate' CPU cycles needed to complete operation
		int waitCounter_ = 0;

		// Opcode processes (Chapter 4, Page 94 of GB Prog Manual)
		// REMEMBER THAT THE GAMEBOY CPU IS LITTLE-ENDIAN! (ie LSB first when bytes are side-by-side in memory)
		
		// Loads
		inline void LDrr(char regNoIn, char regNoOut);
		
		// Jumps
		inline void JPnn(unsigned short nn);
		inline void JPHL();
		inline void JPccnn(unsigned char LSBnn, unsigned char MSBnn, unsigned char cc);
		
		// Relative jumps
		inline void JRr(unsigned char offset);
		inline void JRccr(unsigned char offset, unsigned char cc);

		// Function calls
		inline void callnn(unsigned char LSBnn, unsigned char MSBnn);
		inline void callccnn(unsigned char LSBnn, unsigned char MSBnn, unsigned char cc);

		// Returns
		inline void ret();
		inline void retcc(unsigned char cc);
		inline void reti();

		inline void rstn(unsigned char n);

		// Miscellaneous
		inline void halt();
		inline void stop();
		inline void di();
		inline void ei();
		inline void ccf();
		inline void scf();
		inline void nop();
		inline void daa();
		inline void cpl();

		// Load in the bootstrap code
		void loadBootstrap(const char* filePath);

		// Load in cartridge data
		void loadCartridgeData(const char* filePath);

	public:
		GbCpu();
		void cycle();
		void reset();
	};

	class GbMem
	{
		friend class GpCpu;
		friend class Gameboy;

	private:
		unsigned char* ram_;				// 64K
		unsigned char* rstInterrupts_; // 256 bytes
		unsigned char* romArea_;		// 80 bytes
		unsigned char* userProgram_;	// Starts at 0x150...
		unsigned char* workRam_; // Starts at 0xC000 (8K)

		bool sound1_, sound2_, sound3_, sound4_;

		// Defining memory ranges (to help our pointers later)
		const unsigned short END_OF_PROG_AREA = 0x7FF;
		const unsigned short END_OF_RST_AND_INTERRUPTS = 0x0FF;
		const unsigned short START_OF_ROM_DATA = 0x100;
		const unsigned short END_OF_ROM_DATA = 0x14F;
		const unsigned short START_OF_USER_PROG = 0x150;

		const unsigned short START_OF_VRAM = 0x8000;
		const unsigned short END_OF_VRAM = 0x9FFF;

		// External expansion RAM area
		const unsigned short START_OF_EE_RAM = 0xA000;
		const unsigned short END_OF_EE_RAM = 0xBFFF;

		const unsigned short START_OF_WORK_RAM = 0xC000;
		const unsigned short END_OF_WORK_RAM = 0xDFFF;

	public:
		
		~GbMem();
		GbMem();
		void clear();

	};

	class Gameboy
	{
	private:
		bool poweredOn_;
		char* keys_;

		GbCpu* gameboyCpu_;
		GbMem* gameboyMem_;

	public:
		Gameboy();
		~Gameboy();
		bool insertGame(const char* filePath);
		void ejectGame();
		void togglePower();
		void cycleCpu();
		void reset();
	};

}

#endif