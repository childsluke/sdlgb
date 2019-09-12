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
		unsigned char* A, B, C, D, E, F, H, L;
		unsigned short* SP, PC; // Stack pointer & program counter

		// Flag registers
		bool Z, N, H, CY;

	public:
		GbCpu();
		void cycle();
		void reset();
	};

	class GbMem
	{
	private:
		unsigned char* ram[65536];
		unsigned char* rstInterrupts; // 256 bytes
		unsigned char* romArea;		// 80 bytes
		unsigned char* userProgram;	// Starts at 0x150...
		unsigned char* workRam; // Starts at 0xC000 (8K)

		bool sound1, sound2, sound3, sound4;

		// Defining memory ranges (to help our pointers later)
		const short END_OF_PROG_AREA = 0x7FF;
		const short END_OF_RST_AND_INTERRUPTS = 0x0FF;
		const short START_OF_ROM_DATA = 0x100;
		const short END_OF_ROM_DATA = 0x14F;
		const short START_OF_USER_PROG = 0x150;

		const short START_OF_VRAM = 0x8000;
		const short END_OF_VRAM = 0x9FFF;

		// External expansion RAM area
		const short START_OF_EE_RAM = 0xA000;
		const short END_OF_EE_RAM = 0xBFFF;

		const short START_OF_WORK_RAM = 0xC000;
		const short END_OF_WORK_RAM = 0xDFFF;

	public:
		
		GbMem();
		void clear();

	};

	class Gameboy
	{
	private:
		bool poweredOn_;
		char* keys;

		GbCpu gameboyCpu_;
		GbMem gameboyMem_;

	public:
		Gameboy();
		bool insertGame(const char* filePath);
		void ejectGame();
		void togglePower();
		void reset();
	};

}

#endif