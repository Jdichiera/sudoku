#pragma once
#include "credit-screen.h"

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
	Tile tempTile;

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


GameScreen::GameScreen() {

	debug = true;
	direction = 1;
	rotation = 0;
	solved = false;
	mouseOverPlayAgainButton = false;
	backgroundImage = IMG_Load("assets/background.png");
	playAgainImage = IMG_Load("assets/button-play-again.png");
	if (backgroundImage == NULL) {
		std::cout << "\nCould not load background image : " << IMG_GetError();
	}
	else {
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImage);
	}
	if (playAgainImage == NULL) {
		std::cout << "\nCould not load play again button image : " << IMG_GetError();
	}
	else {
		playAgainTexture = SDL_CreateTextureFromSurface(renderer, playAgainImage);
	}
	if (backgroundTexture == NULL) {
		std::cout << "\nCould not create background texture : " << SDL_GetError();
	}
	if (playAgainTexture == NULL) {
		std::cout << "\nCould not create play again texture : " << SDL_GetError();
	}
	//FadeIn(backgroundTexture);
	int masterGameBoard[9][9] = { { 0 } };
	BoardGenerator boardGenerator;
	boardGenerator.FillCells();
	boardGenerator.PrintBoard();
	tempTile.SetPosition(999, 999);
	SetupBoard(boardGenerator.board/*, holes*/);
	DigHoles();
	//AddPadding();
}
