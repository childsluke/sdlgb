#ifndef GAMEBOY_H
#define GAMEBOY_H

namespace gameboy
{

	class GbCpu
	{
	private:

	public:
		GbCpu();
		void reset();
	};

	class GbMem
	{
	private:
		int sizeInBytes_;

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

		void togglePower();
		void reset();
	};

}

#endif