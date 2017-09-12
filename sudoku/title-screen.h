#pragma once
#include "game-state.h"
class TitleScreen : public GameState {
private:
	SDL_Surface *titleImage;
	SDL_Texture *titleTexture;
	SDL_Surface *playButtonImage;
	SDL_Texture *playButtonTexture;
	SDL_Surface *creditsButtonImage;
	SDL_Texture *creditsButtonTexture;
	// If I have text
	SDL_Surface *message;
	SDL_Rect playButton{ 268, 470, 186, 58 };
	SDL_Rect creditsButton{ 268, 534, 186, 58 };
	bool mouseOverPlayButton = false;
	bool mouseOverCreditsButton = false;

public:
	TitleScreen();
	~TitleScreen();

	void HandleEvents();
	void Logic();
	void Render();
};
