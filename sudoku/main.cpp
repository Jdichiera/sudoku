//#include "globals.h"
#include "board-generator.h"


#include <chrono>
#include <thread>
#include <random>
#include "game-screen.h"


//===--- Class & Function Def ---===








//===--- Globals ---===

Texture lockedSpriteTextures;
Texture unlockedSpriteTextures;

GameState *currentState = NULL;



//===--- Class & Function Imp ---===






void ChangeState() {
	//std::cout << "\nChangeState - Current :" << nextState << " Next: " << nextState;
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

	// Free loaded images

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
	auto time1 = std::chrono::high_resolution_clock::now();
	std::srand(unsigned(time(NULL)));

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

			auto time2 = std::chrono::high_resolution_clock::now();
			auto runTimeMS = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count();
			double runTimeS = runTimeMS / 1000.0;
			std::cout << "\n==-- RunTime : " << runTimeS << " seconds ( " << runTimeMS << " milliseconds)\n";

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