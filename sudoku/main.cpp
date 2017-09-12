//#include "globals.h"
#include "board-generator.h"


#include <chrono>
#include <thread>
#include <random>
#include "game-screen.h"


//===--- Class & Function Def ---===




bool Init();
bool LoadMedia();
void Close();



//===--- Globals ---===

Texture lockedSpriteTextures;
Texture unlockedSpriteTextures;







int stateID = STATE_NULL;
int nextState = STATE_NULL;
GameState *currentState = NULL;
// Music and sound pointers



//===--- Class & Function Imp ---===




//void FadeIn(SDL_Texture *texture);
void SetState(int newState) {
	std::cout << "\nSetstate";
	if (nextState != STATE_EXIT) {
		nextState = newState;
	}
}
void FadeOut(SDL_Texture *texture) {
	/*SDL_Rect overlay;
	overlay.x = 0;
	overlay.y = 0;
	overlay.h = SHEIGHT;
	overlay.w = SWIDTH;*/
	int alpha = 255;
	while (alpha > 0) {
		//SDL_Delay(10);
		alpha -= 8;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_SetTextureAlphaMod(texture, alpha);
	//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
	//	SDL_RenderFillRect(renderer, &overlay);
		SDL_RenderPresent(renderer);
	}
}
void FadeIn(SDL_Texture *texture) {
	/*SDL_Rect overlay;
	overlay.x = 0;
	overlay.y = 0;
	overlay.h = SHEIGHT;
	overlay.w = SWIDTH;*/
	int alpha = 0;
	while (alpha < 255) {
		//SDL_Delay(10);
		std::cout << "\n" << alpha;
		alpha += 8;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_SetTextureAlphaMod(texture, alpha);
		//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
		//	SDL_RenderFillRect(renderer, &overlay);
		SDL_RenderPresent(renderer);
	}
}
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
				//FadeOut(titleTexture);
				SetState(STATE_GAME);
			}
			if (event.button.x > creditsButton.x && event.button.x < creditsButton.x + creditsButton.w &&
				event.button.y > creditsButton.y && event.button.y < creditsButton.y + creditsButton.h) {
				 //FadeOut(titleTexture);
				 SetState(STATE_CREDITS);
			}
		}
	}

}
TileSprite Tile::GetSprite() {
	return currentSprite;
}
bool Tile::Locked() {
	return locked;
}
void Tile::LockTile() {
	this->locked = true;
}
void Tile::UnlockTile() {
	this->locked = false;
}
void Tile::SetValue(int newValue) {
	value = newValue;
}
void Tile::SetWinValue(int newValue) {
	winValue = newValue;
}
Tile::Tile() {
	position.x = 0;
	position.y = 0;
	currentSprite = UNLOCKED_TILE_BLANK;
	value = 0;
	locked = true;
	if (!tileSpriteSheetTexture.LoadFromFile("assets/all-tiles.png")) {
		std::cout << "\nFailed to load texture ... " << IMG_GetError();
		//success = false;
	}
	else {
		// Load the sprite images from the tile sprite sheet
		for (int i = 0; i < TILE_SPRITE_TOTAL; i++) {
			spriteSet[i].x = 0;
			spriteSet[i].y = i * 64;
			spriteSet[i].w = TILE_WIDTH;
			spriteSet[i].h = TILE_HEIGHT;
		}
	}
}
Tile::~Tile() {
	tileSpriteSheetTexture.Free();
}
SDL_Point Tile::GetPosition() {
	return position;
}
int Tile::GetX() {
	return position.x;
}
int Tile::GetY() {
	return position.y;
}
int Tile::GetValue() {
	return value;
}
int Tile::GetWinValue() {
	return winValue;
}
void Tile::SetSprite(TileSprite newSprite) {
	this->currentSprite = newSprite;
}
void Tile::SetPosition(int x, int y) {
	position.x = x;
	position.y = y;
}
bool Tile::MouseOver() {
	bool mouseOver = true;
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	SDL_Point tilePosition = position;

	if (x < tilePosition.x) {
		mouseOver = false;
	}
	else if (x > tilePosition.x + TILE_WIDTH) {
		mouseOver = false;
	}
	else if (y < tilePosition.y) {
		mouseOver = false;
	}
	else if (y > tilePosition.y + TILE_HEIGHT) {
		mouseOver = false;
	}

	return mouseOver;
}
Texture::Texture() {
	texture = NULL;
	width = 0;
	height = 0;
}
Texture::~Texture() {
	Free();
}
bool Texture::LoadFromFile(std::string path) {
	Free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		std::cout << "Unable to load image from file @ " << path.c_str() << " : " << IMG_GetError();
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			std::cout << "Unable to create texture from file @ " << path.c_str() << " : " << IMG_GetError();
		}
		else {
			this->width = loadedSurface->w;
			this->height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	this->texture = newTexture;
	return this->texture != NULL;
}
#ifdef _SDL_TTF_H
bool Texture::LoadFromRenderedText(std::string textureText, SDL_Color textColor) {
	Free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL) {
		std::cout << "err";
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL) {
			std::cout << "err";
		}
		else {
			width = textSurface->w;
			height = textSurface_.h;
		}
		SDL_FreeSurface(textSurface);
	}
	return texture != NULL;
}
#endif
void Texture::Free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}
void Texture::SetColor(int red, int green, int blue) {
	SDL_SetTextureColorMod(texture, red, green, blue);
}
void Texture::SetBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(texture, blending);
}
void Texture::SetAlpha(int alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}
void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center,
	SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, width, height };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}
int Texture::GetWidth() {
	return width;
}
int Texture::GetHeight() {
	return height;
}
void Tile::Render() {
	tileSpriteSheetTexture.Render(position.x, position.y, &spriteSet[currentSprite]);
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

				// Initi mixer
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
	/*if (!tileSpriteSheetTexture.LoadFromFile("assets/all-tiles.png")) {
		std::cout << "\nFailed to load texture ... " << IMG_GetError();
		success = false;
	}
	else {*/
		// Load music

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
		


		
	//}
	return success;
}
//bool CheckSolved(Tile gameBoard[][9]) {
//	bool solved = false;
//	return solved;
//}
void Close() {
	delete currentState;

	// Free loaded images
	//tileSpriteSheetTexture.Free();

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
//void AddPadding() {
//	for (int i = 0; i < COL_COUNT; ++i) {
//		for (int j = 0; j < ROW_COUNT; ++j) {
//			if (i > 2) {
//				gameBoard[i][j].SetPosition(gameBoard[i][j].GetX(), gameBoard[i][j].GetY() + 10);
//				if (i > 5) {
//					gameBoard[i][j].SetPosition(gameBoard[i][j].GetX(), gameBoard[i][j].GetY() + 10);
//				}
//			}
//			if (j > 2) {
//				gameBoard[i][j].SetPosition(gameBoard[i][j].GetX() + 10, gameBoard[i][j].GetY());
//				if (j > 5) {
//					gameBoard[i][j].SetPosition(gameBoard[i][j].GetX() + 10, gameBoard[i][j].GetY());
//				}
//			}
//		}
//	}
//}
//void ClearCells(int pattern[][9]) {
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (pattern[i][j] == 0) {
//				gameBoard[i][j].SetValue(0);
//				gameBoard[i][j].SetSprite(UNLOCKED_TILE_BLANK);
//
//			}
//		}
//	}
//}



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
			//std::cout << "\nmat height: " << BOARD_MAT_HEIGHT << " mat width: " << BOARD_MAT_WIDTH;
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