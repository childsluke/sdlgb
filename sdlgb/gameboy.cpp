#include "gameboy.h"

using namespace gameboy;


GbCpu::GbCpu()
	{

	}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

GbMem::GbMem()
	{
		sizeInBytes_ = 0;
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

Gameboy::Gameboy()
	{
		poweredOn_ = false;
		keys = nullptr;
	}

void Gameboy::togglePower()
	{
		poweredOn_ = !(poweredOn_);
	}
