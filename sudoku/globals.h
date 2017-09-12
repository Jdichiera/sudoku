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

bool CheckWin();
bool BoardFull();
void SetState(int newState);
void ChangeState();
void FadeOut(SDL_Texture *texture);
void SetupBoard(int masterGameBoard[][9]);



#endif // !GLOBALS_H

