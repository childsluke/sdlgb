// IMPLEMENTATION OF GAME BOY CPU, MEMORY, and PPU.
// ASSISTANCE VIA:
// https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf
// https://gbdev.github.io/list.html
// https://gekkio.fi/files/gb-docs/gbctr.pdf

#ifndef GAMEBOY_H
#define GAMEBOY_H

namespace gameboy
{

	class GbCpu
	{
	private:

		// Registers
		unsigned char* rA_, rB_, rC_, rD_, rE_, rF_, rH_, rL_;
		unsigned short* SP_, PC_; // Stack pointer & program counter

		// Flag registers
		bool fZ_, fN_, fH_, fCY_;

	public:
		GbCpu();
		void cycle();
		void reset();
	};

	class GbMem
	{
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
		char* keys;

		GbCpu* gameboyCpu_;
		GbMem* gameboyMem_;

	public:
		Gameboy();
		~Gameboy();
		bool insertGame(const char* filePath);
		void ejectGame();
		void togglePower();
		void reset();
	};

}

#endif