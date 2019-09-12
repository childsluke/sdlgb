#include "gameboy.h"

using namespace gameboy;


GbCpu::GbCpu()
	{

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
		keys = nullptr;

		gameboyMem_ =  new GbMem();
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
