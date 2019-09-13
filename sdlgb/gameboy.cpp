#include "gameboy.h"

using namespace gameboy;


GbCpu::GbCpu()
{
	reset();
}

GbCpu::Register::Register(unsigned short initValue)
{
	reg = initValue;
}
GbCpu::Register::Register()
{
	reg = 0;
}

void GbCpu::reset()
{
	// Init register pairs and singular register pointers
	rAF_ = Register();
	rBC_ = Register();
	rDE_ = Register();
	rHL_ = Register();

	rA_ = &rAF_.hi;
	rF_ = &rAF_.lo;

	rB_ = &rBC_.hi;
	rC_ = &rBC_.lo;

	rD_ = &rDE_.hi;
	rE_ = &rDE_.lo;

	rH_ = &rHL_.lo;
	rL_ = &rHL_.hi;

	imeFlag_ = 0;
}

void GbCpu::cycle()
{
	// Simulating the 'time' it takes for the CPU to complete an instruction
	if (waitCounter_ > 0)
	{
		waitCounter_--;
		return;
	}

	// TODO: Opcode fetch, decode, execute
	//char currentOpcode = *PC_;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

GbMem::GbMem()
	{
	ram_ = new unsigned char[65536];
	}

GbMem::~GbMem()
{
	delete ram_;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

Gameboy::Gameboy()
	{
		poweredOn_ = false;
		keys_ = nullptr;

		gameboyMem_ =  new GbMem();
		gameboyCpu_ = new GbCpu();
	}

Gameboy::~Gameboy()
{
	delete gameboyMem_;
	delete gameboyCpu_;
}

void Gameboy::togglePower()
	{
		poweredOn_ = !(poweredOn_);
	}

void Gameboy::cycleCpu()
{
	gameboyCpu_->cycle();
}
