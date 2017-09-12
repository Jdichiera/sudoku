#pragma once
#include "game-state.h"
class CreditsScreen : public GameState {
private:
	SDL_Surface *creditsImage;
	SDL_Texture *creditsTexture;
	SDL_Surface *returnButtonImage;
	SDL_Texture *returnButtonTexture;
	SDL_Rect returnButton{ 268, 598, 186, 58 };
	bool mouseOverReturnButton = false;
public:
	CreditsScreen();
	~CreditsScreen();

	void HandleEvents();
	void Logic();
	void Render();
};
