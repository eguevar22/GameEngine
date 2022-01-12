#pragma once
#include <iostream>
#include <SDL.h>

class Clock
{
private:
	uint32_t initTIme = SDL_GetTicks();
	uint32_t currentTime = 0;
	double delta = 0;
	
public:
	Clock() {};

	double GetDeltaTime()
	{
		currentTime = SDL_GetTicks();
		delta = (double)(currentTime - initTIme)/1000 ;

		return delta;
	}

	
	
};
