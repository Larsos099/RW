#include <iostream>
#include "includes.h"
int main(int argc, char** argv[]) {
	const int width = 800, height = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("UwU you've been pwn'd by a gay, a furry, and a hacker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == NULL) {
		std::cout <<  "Window failure caused by: " << SDL_GetError() << std::endl;
	}
	std::cout << "?";
	return 0;
}