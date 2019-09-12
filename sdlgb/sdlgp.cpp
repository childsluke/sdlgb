
// A GAMEBOY EMULATOR USING SDL2
// Renders a Gameboy on-screen and emulates graphics via the onscreen 'screen'
// BY LUKE CHILDS, 2019
// github.com/childsluke


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "gameboy.h"

using namespace std;

bool init(SDL_Window** sdlWindow, SDL_Renderer** sdlRenderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL Error! " << SDL_GetError();
		return false;
	}

	if (!IMG_Init(IMG_INIT_JPG))
	{
		cout << "SDL image initialization failure - " << SDL_GetError() << endl;
		return false;
	}

	*sdlWindow = SDL_CreateWindow("GBSDL", 50, 50, 640, 480, SDL_WINDOW_SHOWN);
	if (*sdlWindow == nullptr)
	{
		cout << "Error initiazling window! " << SDL_GetError();
		return false;
	}

	*sdlRenderer = SDL_CreateRenderer(*sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (*sdlRenderer == nullptr)
	{
		cout << "Error initializing renderer! - " << SDL_GetError();
		return false;
	}
	SDL_SetRenderDrawColor(*sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
;
	return true;
}

bool loadMedia(const char* filePath, SDL_Renderer** sdlRenderer, SDL_Texture** sdlTexture)
{
	SDL_Surface* surface = IMG_Load(filePath);
	*sdlTexture = SDL_CreateTextureFromSurface(*sdlRenderer, surface);
	
	if ((*sdlTexture == nullptr) || (surface == nullptr))
	{
		cout << "Image loading error - " << SDL_GetError() << endl;
		return false;
	}
	
	SDL_FreeSurface(surface);
	return true;
}

int main(int argc, char* argv[])
{
	gameboy::Gameboy gameboy = gameboy::Gameboy();

	SDL_Window* gameWindow = nullptr;
	SDL_Renderer* gameRenderer = nullptr;

	SDL_Texture* gameboyBackground = nullptr;
	SDL_Rect gameboyScreenArea = SDL_Rect();

	if ( !init(&gameWindow, &gameRenderer) ) return 0;

	cout << "SDL Initialization Successful!" << endl;

	if ( loadMedia("gameboyBackground.jpg", &gameRenderer, &gameboyBackground) ) cout << "Image loaded!" << endl;

	if (gameboyBackground == nullptr) cout << "Background is NULL!" << endl;

	// Defines where the emulator graphics will be drawn onscreen
	// (ie inside the Game Boy texture screen =) )
	gameboyScreenArea.x = 215; gameboyScreenArea.y = 20; 
	gameboyScreenArea.w = 180; gameboyScreenArea.h = 180;

	bool gameRunning = true;
	while (gameRunning)
	{
		// Draw our Game Boy and the Game Boy screen area
		SDL_RenderClear(gameRenderer);
		SDL_SetRenderDrawColor(gameRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderCopy(gameRenderer, gameboyBackground, nullptr, nullptr);
		SDL_SetRenderDrawColor(gameRenderer, 0x9b, 0xbc, 0x0f, 0xff);
		SDL_RenderFillRect(gameRenderer, &gameboyScreenArea);
		
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT: gameRunning = false; break;
				
				default: break;
			}
		}

		SDL_RenderPresent(gameRenderer);
	}

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyTexture(gameboyBackground);
	SDL_DestroyWindow(gameWindow);
	IMG_Quit();
	SDL_Quit();

	return 0;
}