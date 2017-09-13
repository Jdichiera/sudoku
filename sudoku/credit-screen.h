//#pragma once
#ifndef CREDIT_SCREEN_H
#define CREDIT_SCREEN_H
#include "title-screen.h"
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


CreditsScreen::CreditsScreen() {
	creditsImage = IMG_Load("assets/credits.png");
	returnButtonImage = IMG_Load("assets/button-return.png");
	if (creditsImage == NULL) {
		std::cout << "\nIssue loading credits image";
	}
	if (returnButtonImage == NULL) {
		std::cout << "\nIssue loading return button image";
	}
	else {
		creditsTexture = SDL_CreateTextureFromSurface(renderer, creditsImage);
		returnButtonTexture = SDL_CreateTextureFromSurface(renderer, returnButtonImage);
	}
	if (creditsTexture == NULL) {
		std::cout << "\nIssue creating credits texture";
	}
	if (returnButtonTexture == NULL) {
		std::cout << "\nIssue creating return button texture";
	}
}
CreditsScreen::~CreditsScreen() {
	SDL_FreeSurface(creditsImage);
}
void CreditsScreen::HandleEvents() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SetState(STATE_EXIT);
		}
		if (event.type == SDL_MOUSEMOTION) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (event.button.x > returnButton.x && event.button.x < returnButton.x + returnButton.w &&
				event.button.y > returnButton.y && event.button.y < returnButton.y + returnButton.h) {
				mouseOverReturnButton = true;
			}
			else {
				mouseOverReturnButton = false;
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.x > returnButton.x && event.button.x < returnButton.x + returnButton.w &&
				event.button.y > returnButton.y && event.button.y < returnButton.y + returnButton.h) {
				FadeOut(creditsTexture);
				SetState(STATE_TITLE);
			}
		}
	}
}
void CreditsScreen::Logic() {

}
void CreditsScreen::Render() {

	if (mouseOverReturnButton) {
		returnButton.x = 264;
		returnButton.y = 595;
		returnButton.w = 194;
		returnButton.h = 66;
	}
	else {
		returnButton.x = 268;
		returnButton.y = 598;
		returnButton.w = 186;
		returnButton.h = 59;
	}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, creditsTexture, NULL, NULL);

	SDL_RenderCopy(renderer, returnButtonTexture, NULL, &returnButton);
	SDL_RenderPresent(renderer);
}
#endif // !credit-screen_h


