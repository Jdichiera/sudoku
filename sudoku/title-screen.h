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


TitleScreen::TitleScreen() {
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(soundMusic, -1);
	}
	titleImage = IMG_Load("assets/title.png");
	playButtonImage = IMG_Load("assets/button-play.png");
	creditsButtonImage = IMG_Load("assets/button-credits.png");

	if (titleImage == NULL) {
		std::cout << "\ntitle image issue";
	}
	if (playButtonImage == NULL) {
		std::cout << "\nPlay button image issue";
	}
	if (creditsButtonImage == NULL) {
		std::cout << "\nCredits button image issue";
	}
	else {
		titleTexture = SDL_CreateTextureFromSurface(renderer, titleImage);
		playButtonTexture = SDL_CreateTextureFromSurface(renderer, playButtonImage);
		creditsButtonTexture = SDL_CreateTextureFromSurface(renderer, creditsButtonImage);

		if (titleTexture == NULL) {
			std::cout << "\ntitle texture image issue: " << SDL_GetError() << std::endl;
		}
		if (playButtonTexture == NULL) {
			std::cout << "\nPlay button texture image issue: " << SDL_GetError() << std::endl;
		}
		if (creditsButtonTexture == NULL) {
			std::cout << "\nCredits button texture image issue: " << SDL_GetError() << std::endl;
		}

	}
}
TitleScreen::~TitleScreen() {
	SDL_FreeSurface(titleImage);
}
void TitleScreen::Render() {
	if (mouseOverPlayButton) {
		playButton.x = 264;
		playButton.y = 466;
		playButton.w = 194;
		playButton.h = 66;
	}
	else {
		playButton.x = 268;
		playButton.y = 470;
		playButton.w = 186;
		playButton.h = 59;
	}
	if (mouseOverCreditsButton) {
		creditsButton.x = 264;
		creditsButton.y = 530;
		creditsButton.w = 194;
		creditsButton.h = 66;
	}
	else {
		creditsButton.x = 268;
		creditsButton.y = 534;
		creditsButton.w = 186;
		creditsButton.h = 59;
	}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, titleTexture, NULL, NULL);
	SDL_RenderCopy(renderer, playButtonTexture, NULL, &playButton);
	SDL_RenderCopy(renderer, creditsButtonTexture, NULL, &creditsButton);
	SDL_RenderPresent(renderer);
}

void TitleScreen::Logic() {

}

void TitleScreen::HandleEvents() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SetState(STATE_EXIT);
		}
		if (event.type == SDL_MOUSEMOTION) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (event.button.x > playButton.x && event.button.x < playButton.x + playButton.w &&
				event.button.y > playButton.y && event.button.y < playButton.y + playButton.h) {
				mouseOverPlayButton = true;
				mouseOverCreditsButton = false;
			}
			else if (event.button.x > creditsButton.x && event.button.x < creditsButton.x + creditsButton.w &&
				event.button.y > creditsButton.y && event.button.y < creditsButton.y + creditsButton.h) {
				mouseOverCreditsButton = true;
				mouseOverPlayButton = false;
			}
			else {
				mouseOverPlayButton = false;
				mouseOverCreditsButton = false;
			}

		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.x > playButton.x && event.button.x < playButton.x + playButton.w &&
				event.button.y > playButton.y && event.button.y < playButton.y + playButton.h) {
				FadeOut(titleTexture);
				SetState(STATE_GAME);
			}
			if (event.button.x > creditsButton.x && event.button.x < creditsButton.x + creditsButton.w &&
				event.button.y > creditsButton.y && event.button.y < creditsButton.y + creditsButton.h) {
				FadeOut(titleTexture);
				SetState(STATE_CREDITS);
			}
		}
	}

}
