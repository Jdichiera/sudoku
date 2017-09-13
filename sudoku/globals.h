//#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "enums.h"
#include "constants.h"


SDL_Event event;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect spriteSet[TILE_SPRITE_TOTAL];
Mix_Music *soundMusic = NULL;
Mix_Chunk *soundPickUp = NULL;
Mix_Chunk *soundSet = NULL;

int stateID = STATE_NULL;
int nextState = STATE_NULL;

void SetState(int newState);
void ChangeState();
void FadeOut(SDL_Texture *texture);

void FadeOut(SDL_Texture *texture) {

	int alpha = 255;
	while (alpha > 0) {
		alpha -= 8;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_SetTextureAlphaMod(texture, alpha);
		SDL_RenderPresent(renderer);
	}
}

void SetState(int newState) {
	std::cout << "\nSetstate";
	if (nextState != STATE_EXIT) {
		nextState = newState;
	}
}

bool Init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "\nCould not initialize: " << SDL_GetError();
		success = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			std::cout << "\nWarning: Linear texture filtering not enabled!";
		}

		window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SWIDTH, SHEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "\nWindow could not be created: " << SDL_GetError();
			success = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) {
				std::cout << "\nCould not create renderer: " << SDL_GetError();
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "\nSDL_Image could not initialize: " << IMG_GetError();
					success = false;
				}

				// Init mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					std::cout << "\nSDL_Mixer could not initialize: " << Mix_GetError();
					success = false;
				}
			}
		}
	}
	return success;
}

bool LoadMedia() {
	bool success = true;
	soundMusic = Mix_LoadMUS("assets/sound-music.mp3");
	if (soundMusic == NULL) {
		std::cout << "\nFailed to load background music ... " << Mix_GetError();
		success = false;
	}
	soundPickUp = Mix_LoadWAV("assets/sound-pickup.wav");
	if (soundPickUp == NULL) {
		std::cout << "\nFailed to load pickup sound ... " << Mix_GetError();
		success = false;
	}
	soundSet = Mix_LoadWAV("assets/sound-set.wav");
	if (soundPickUp == NULL) {
		std::cout << "\nFailed to load set sound ... " << Mix_GetError();
		success = false;
	}
	return success;
}


#endif // !GLOBALS_H

