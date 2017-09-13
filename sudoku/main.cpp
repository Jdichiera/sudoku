//#include "globals.h"
#include "board-generator.h"
#include <chrono>
#include <thread>
#include <random>
#include "game-screen.h"

Texture lockedSpriteTextures;
Texture unlockedSpriteTextures;
GameState *currentState = NULL;

void ChangeState() {
	if (nextState != STATE_NULL) {
		if (nextState != STATE_EXIT) {
			delete currentState;
		}
		switch (nextState) {
		case STATE_TITLE:
			currentState = new TitleScreen();
			break;
		case STATE_CREDITS:
			currentState = new CreditsScreen();
			break;
		case STATE_GAME:
			currentState = new GameScreen();
			break;
		}
		stateID = nextState;
		nextState = STATE_NULL;
	}
}

void Close() {
	delete currentState;

	// Free the sound effects
	Mix_FreeMusic(soundMusic);
	Mix_FreeChunk(soundPickUp);
	Mix_FreeChunk(soundSet);

	//Destroy the window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	// Quit the subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {

	if (!Init()) {
		std::cout << "\nFailed to initialize ... ";
	}
	else {
		if (!LoadMedia()) {
			std::cout << "\nFailed to load media ... ";
		}
		else {
			stateID = STATE_TITLE;
			currentState = new TitleScreen();

			while (stateID != STATE_EXIT) {
				currentState->HandleEvents();
				currentState->Logic();
				ChangeState();
				currentState->Render();
			}
		}
	}

	Close();
	return 0;
}