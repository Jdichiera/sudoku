#pragma once
#include "title-screen.h"

class GameScreen : public GameState {
private:
	SDL_Surface *backgroundImage;
	SDL_Texture *backgroundTexture;
	SDL_Surface *playAgainImage;
	SDL_Texture *playAgainTexture;
	SDL_Point tilePosition;
	SDL_Rect playAgainButton{ 268, 800, 186, 58 };
	int rotation;
	int direction;
	bool debug;
	bool draggingTile;
	bool solved;
	bool mouseOverPlayAgainButton;

public:
	bool playing = false;
	GameScreen();
	~GameScreen();

	void HandleEvents();
	void Logic();
	void Render();
	void CheckSolved();
	void DigHoles();
};
