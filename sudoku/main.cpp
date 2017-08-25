#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "board-generator.h"
#include "enums.h"
#include "constants.h"
#include <chrono>
#include <thread>


//===--- Class & Function Def ---===
class GameState {
public:
	virtual void HandleEvents() = 0;
	virtual void Logic() = 0;
	virtual void Render() = 0;
	virtual ~GameState() {};
};

class WinScreen : public GameState {
private:
	SDL_Surface *winImage;
	SDL_Texture *winTexture;
	// If I have text
	SDL_Surface *message;
public:
	WinScreen();
	~WinScreen();
	void HandleEvents();
	void Logic();
	void Render();
};

class TitleScreen : public GameState {
private:
	SDL_Surface *titleImage;
	SDL_Texture *titleTexture;
	// If I have text
	SDL_Surface *message;

public:
	TitleScreen();
	~TitleScreen();

	void HandleEvents();
	void Logic();
	void Render();
};

class GameScreen : public GameState {
private:
	SDL_Point tilePosition;
	bool draggingTile;

public:
	GameScreen();
	~GameScreen();

	void HandleEvents();
	void Logic();
	void Render();

};
class Tile {
public:
	Tile();
	void SetPosition(int x, int y);
	void HandleEvent(SDL_Event* event);
	void Render();
	void SetSprite(TileSprite newSprite);
	SDL_Point GetPosition();
	bool MouseOver();
	int GetValue();
	int GetWinValue();
	void SetValue(int newValue);
	void SetWinValue(int newValue);
	int GetX();
	int GetY();
	void LockTile();
	bool Locked();
	void UnlockTile();
	TileSprite GetSprite();

private:
	TileSprite currentSprite;
	SDL_Point position;
	int value;
	int winValue;
	bool locked;
};


class Texture {
public:
	Texture();
	~Texture();

	bool LoadFromFile(std::string path);

#ifdef _SDL_TFF_H
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	void Free();

	void SetColor(int red, int green, int blue);

	void SetBlendMode(SDL_BlendMode blending);

	void SetAlpha(int aplha);

	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
		SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth();
	int GetHeight();

private:
	SDL_Texture* texture;

	int width;
	int height;

};

bool Init();
bool LoadMedia();
void Close();
bool CheckSolved(Tile gameBoard[][9]);
void SetupBoard(int masterGameBoard[][9], int pattern[][9]);
void AddPadding();





//===--- Globals ---===
//SDL_Surface *screen = NULL;
SDL_Event event;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect spriteSet[TILE_SPRITE_TOTAL];
Tile gameBoard[COL_COUNT][ROW_COUNT];
Tile guiTiles[10];
Tile tempTile;
Texture tileSpriteSheetTexture;
int stateID = STATE_NULL;
int nextState = STATE_NULL;
GameState *currentState = NULL;


//===--- Class & Function Imp ---===
//TempTile::TempTile() {
//	currentSprite = TILE_BLANK;
//	value = 0;
//}
//void TempTile::HoldTile(TileSprite newSprite, int newValue) {
//	currentSprite = newSprite;
//	value = newValue;
//}
bool CheckWin();
bool BoardFull();
void SetState(int newState);
void ChangeState();

void SetState(int newState) {
	std::cout << "\nSetstate";
	if (nextState != STATE_EXIT) {
		nextState = newState;
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
		case STATE_GAME:
			currentState = new GameScreen();
			break;
		case STATE_WIN:
			currentState = new WinScreen();
			break;
		}
		stateID = nextState;
		nextState = STATE_NULL;
	}
}
WinScreen::WinScreen() {
	winImage = IMG_Load("assets/win.png");
	if (winImage == NULL) {
		std::cout << "\nIssue loading win image";
	}
	else {
		winTexture = SDL_CreateTextureFromSurface(renderer, winImage);
	}
	if (winTexture == NULL) {
		std::cout << "\nIssue creating win texture";
	}
}
void WinScreen::Render() {
	SDL_RenderCopy(renderer, winTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void WinScreen::HandleEvents() {

}
void WinScreen::Logic() {

}
WinScreen::~WinScreen() {
	SDL_FreeSurface(winImage);
}
GameScreen::GameScreen() {
	int testBoard[9][9]{ { 0, 1, 2, 8, 6, 7, 3, 9, 4 },
	{ 4, 9, 7, 5, 2, 3, 8, 1, 6 },
	{ 8, 6, 3, 9, 1, 4, 7, 2, 5 },
	{ 7, 5, 9, 4, 3, 6, 1, 8, 2 },
	{ 2, 8, 1, 7, 9, 5, 6, 4, 3 },
	{ 6, 3, 4, 1, 8, 2, 5, 7, 9 },
	{ 1, 7, 6, 3, 4, 9, 2, 5, 8 },
	{ 9, 2, 8, 6, 5, 1, 4, 3, 7 },
	{ 3, 4, 5, 2, 7, 8, 9, 6, 1 }
	};
	int cross[9][9] = { { 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1 },
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 } };

	int full[9][9] = { { 0, 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1 } };

	int masterGameBoard[9][9] = { { 0 } };
	BoardGenerator boardGenerator;
	boardGenerator.FillCells();
	boardGenerator.PrintBoard();
	tempTile.SetPosition(999, 999);
	SetupBoard(boardGenerator.board, full);
	AddPadding();


}
TitleScreen::TitleScreen() {

	titleImage = IMG_Load("assets/title.png");

	if (titleImage == NULL) {
		std::cout << "\ntitle image issue";
	}
	else {
		titleTexture = SDL_CreateTextureFromSurface(renderer, titleImage);

		if (titleTexture == NULL) {
			std::cout << "\ntitle texture image issue: " << SDL_GetError() << std::endl;
		}
	}
}

TitleScreen::~TitleScreen() {
	SDL_FreeSurface(titleImage);
}

void TitleScreen::Render() {
	SDL_RenderCopy(renderer, titleTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void TitleScreen::Logic() {

}

void GameScreen::Logic() {

}
GameScreen::~GameScreen() {
}

void GameScreen::Render() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	for (int i = 0; i < COL_COUNT; ++i) {
		for (int j = 0; j < ROW_COUNT; ++j) {
			gameBoard[i][j].Render();
		}
	}


	// draw GUI buttons
	guiTiles[0].SetSprite(TILE_BLANK);
	guiTiles[1].SetSprite(TILE_1);
	guiTiles[2].SetSprite(TILE_2);
	guiTiles[3].SetSprite(TILE_3);
	guiTiles[4].SetSprite(TILE_4);
	guiTiles[5].SetSprite(TILE_5);
	guiTiles[6].SetSprite(TILE_6);
	guiTiles[7].SetSprite(TILE_7);
	guiTiles[8].SetSprite(TILE_8);
	guiTiles[9].SetSprite(TILE_9);

	for (int i = 0; i < TILE_COUNT; ++i) {
		guiTiles[i].Render();
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	// Draw main Sudoku box outline
	SDL_Rect topBorder{ 4, 13, 631, 4 };
	SDL_Rect bottomBorder{ 5, 617, 631, 4 };
	SDL_Rect leftBorder{ 13, 4, 4, 625 };
	SDL_Rect righBorder{ 616, 4, 4, 625 };
	SDL_RenderFillRect(renderer, &topBorder);
	SDL_RenderFillRect(renderer, &bottomBorder);
	SDL_RenderFillRect(renderer, &leftBorder);
	SDL_RenderFillRect(renderer, &righBorder);

	//// Block outlines
	SDL_Rect blockLeft{ 215, 20, 4, 595 };
	SDL_Rect blockRight{ 417, 20, 4, 595 };
	SDL_Rect blockTop{ 20, 215, 595, 4 };
	SDL_Rect blockBottom{ 20, 417, 595, 4 };
	SDL_RenderFillRect(renderer, &blockLeft);
	SDL_RenderFillRect(renderer, &blockRight);
	SDL_RenderFillRect(renderer, &blockTop);
	SDL_RenderFillRect(renderer, &blockBottom);

	// Draw borders around tiles
	// Left top horizontal & vertical
	SDL_Rect leftTopTopH{ 29, 83,  172, 2 };
	SDL_Rect leftTopBotH{ 29, 147, 172, 2 };
	SDL_Rect leftTopTopV{ 83, 29,  2, 172 };
	SDL_Rect leftTopBotV{ 147, 29, 2, 172 };

	SDL_RenderFillRect(renderer, &leftTopTopH);
	SDL_RenderFillRect(renderer, &leftTopBotH);
	SDL_RenderFillRect(renderer, &leftTopTopV);
	SDL_RenderFillRect(renderer, &leftTopBotV);

	// Left middle horizontal & vertical
	SDL_Rect leftMidTopH{ 29, 285,  172, 2 };
	SDL_Rect leftMidBotH{ 29, 349, 172, 2 };
	SDL_Rect leftMidTopV{ 83, 231,  2, 172 };
	SDL_Rect leftMidBotV{ 147, 231, 2, 172 };

	SDL_RenderFillRect(renderer, &leftMidTopH);
	SDL_RenderFillRect(renderer, &leftMidBotH);
	SDL_RenderFillRect(renderer, &leftMidTopV);
	SDL_RenderFillRect(renderer, &leftMidBotV);

	// Left bottom horizontal & vertical
	SDL_Rect leftBotTopH{ 29, 487,  172, 2 };
	SDL_Rect leftBotBotH{ 29, 551, 172, 2 };
	SDL_Rect leftBotTopV{ 83, 433,  2, 172 };
	SDL_Rect leftBotBotV{ 147, 433, 2, 172 };

	SDL_RenderFillRect(renderer, &leftBotTopH);
	SDL_RenderFillRect(renderer, &leftBotBotH);
	SDL_RenderFillRect(renderer, &leftBotTopV);
	SDL_RenderFillRect(renderer, &leftBotBotV);


	// Middle top
	SDL_Rect midTopTopH{ 231, 83,  172, 2 };
	SDL_Rect midTopBotH{ 231, 147, 172, 2 };
	SDL_Rect midTopLeftV{ 285, 29,  2, 172 };
	SDL_Rect midTopRightV{ 349, 29, 2, 172 };

	SDL_RenderFillRect(renderer, &midTopTopH);
	SDL_RenderFillRect(renderer, &midTopBotH);
	SDL_RenderFillRect(renderer, &midTopLeftV);
	SDL_RenderFillRect(renderer, &midTopRightV);

	// Middle middle
	SDL_Rect midMidTopH{ 231, 285, 172, 2 };
	SDL_Rect midMidBotH{ 231, 349, 172, 2 };
	SDL_Rect midMidLeftV{ 285, 231, 2, 172 };
	SDL_Rect midMidRightV{ 349, 231, 2, 172 };
	SDL_RenderFillRect(renderer, &midMidTopH);
	SDL_RenderFillRect(renderer, &midMidBotH);
	SDL_RenderFillRect(renderer, &midMidLeftV);
	SDL_RenderFillRect(renderer, &midMidRightV);

	//// Middle bottom
	SDL_Rect midBotTopH{ 231, 487, 172, 2 };
	SDL_Rect midBotBotH{ 231, 551, 172, 2 };
	SDL_Rect midBotLeftV{ 285, 433, 2, 172 };
	SDL_Rect midBotRightV{ 349, 433, 2, 172 };
	SDL_RenderFillRect(renderer, &midBotTopH);
	SDL_RenderFillRect(renderer, &midBotBotH);
	SDL_RenderFillRect(renderer, &midBotLeftV);
	SDL_RenderFillRect(renderer, &midBotRightV);

	// Right top
	SDL_Rect rightTopTopH{ 433, 83, 172, 2 };
	SDL_Rect rightTopBotH{ 433, 147, 172, 2 };
	SDL_Rect rightTopLeftV{ 487, 29, 2, 172 };
	SDL_Rect rightTopRightV{ 551, 29, 2, 172 };
	SDL_RenderFillRect(renderer, &rightTopTopH);
	SDL_RenderFillRect(renderer, &rightTopBotH);
	SDL_RenderFillRect(renderer, &rightTopLeftV);
	SDL_RenderFillRect(renderer, &rightTopRightV);

	// Right middle
	SDL_Rect rightMidTopH{ 433, 285, 172, 2 };
	SDL_Rect rightMidBotH{ 433, 349, 172, 2 };
	SDL_Rect rightMidLeftV{ 487, 231, 2, 172 };
	SDL_Rect rightMidRightV{ 551, 231, 2, 172 };
	SDL_RenderFillRect(renderer, &rightMidTopH);
	SDL_RenderFillRect(renderer, &rightMidBotH);
	SDL_RenderFillRect(renderer, &rightMidLeftV);
	SDL_RenderFillRect(renderer, &rightMidRightV);

	// Right bottom
	SDL_Rect rightBotTopH{ 433, 487, 172, 2 };
	SDL_Rect rightBotBotH{ 433, 551, 172, 2 };
	SDL_Rect rightBotLeftV{ 487, 433, 2, 172 };
	SDL_Rect rightBotRightV{ 551, 433, 2, 172 };
	SDL_RenderFillRect(renderer, &rightBotTopH);
	SDL_RenderFillRect(renderer, &rightBotBotH);
	SDL_RenderFillRect(renderer, &rightBotLeftV);
	SDL_RenderFillRect(renderer, &rightBotRightV);

	tempTile.Render();
	SDL_RenderPresent(renderer);
}

void TitleScreen::HandleEvents() {

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			SetState(STATE_EXIT);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_RETURN:
				SetState(STATE_GAME);
				break;

			}
			break;
		}
	}
}

void GameScreen::HandleEvents() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SetState(STATE_EXIT);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			for (int i = 0; i < TILE_COUNT; i++) {
				tilePosition = guiTiles[i].GetPosition();
				if (event.button.x > guiTiles[i].GetX() &&
					event.button.x < guiTiles[i].GetX() + TILE_WIDTH &&
					event.button.y > guiTiles[i].GetY() &&
					event.button.y < guiTiles[i].GetY() + TILE_HEIGHT) {
					tempTile = guiTiles[i];
					draggingTile = true;
				}

			}
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			tempTile.SetPosition(999, 999);
			if (draggingTile == true) {
				for (int i = 0; i < COL_COUNT; ++i) {
					for (int j = 0; j < ROW_COUNT; ++j) {
						if (event.button.x > gameBoard[i][j].GetX() &&
							event.button.x < gameBoard[i][j].GetX() + TILE_WIDTH &&
							event.button.y > gameBoard[i][j].GetY() &&
							event.button.y < gameBoard[i][j].GetY() + TILE_HEIGHT) {
							if (!gameBoard[i][j].Locked()) {
								gameBoard[i][j].SetSprite(tempTile.GetSprite());
								gameBoard[i][j].SetValue(tempTile.GetValue());
								if (BoardFull()) {
									CheckWin();
								}
							}
						}
					}
				}
			}
			draggingTile = false;
		}
		if (event.type == SDL_MOUSEMOTION) {
			if (draggingTile == true) {
				tempTile.SetPosition(event.motion.x, event.motion.y);
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
	currentSprite = TILE_BLANK;
	value = 0;
	locked = true;
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

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "\nSDL_Image could not initialize: " << IMG_GetError();
					success = false;
				}
			}
		}
	}
	//screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	return success;
}

bool LoadMedia() {
	bool success = true;
	if (!tileSpriteSheetTexture.LoadFromFile("assets/tiles.png")) {
		std::cout << "\nFailed to load texture ... ";
		success = false;
	}
	else {
		for (int i = 0; i < TILE_SPRITE_TOTAL; i++) {
			spriteSet[i].x = 0;
			spriteSet[i].y = i * 64;
			spriteSet[i].w = TILE_WIDTH;
			spriteSet[i].h = TILE_HEIGHT;
		}

		for (int i = 0; i < COL_COUNT; i++) {
			for (int j = 0; j < ROW_COUNT; j++) {
				gameBoard[i][j].SetPosition((TILE_WIDTH * j) + PADDING_X, (TILE_HEIGHT * i) + PADDING_Y);
			}
		}
		for (int i = 0; i < TILE_COUNT; ++i) {
			guiTiles[i].SetPosition((TILE_WIDTH * i) + PADDING_X, 700);
			guiTiles[i].SetValue(i);
		}
	}
	return success;
}

bool CheckSolved(Tile gameBoard[][9]) {
	bool solved = false;
	return solved;
}
void Close() {
	delete currentState;
	tileSpriteSheetTexture.Free();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

void AddPadding() {
	for (int i = 0; i < COL_COUNT; ++i) {
		for (int j = 0; j < ROW_COUNT; ++j) {
			if (i > 2) {
				gameBoard[i][j].SetPosition(gameBoard[i][j].GetX(), gameBoard[i][j].GetY() + 10);
				if (i > 5) {
					gameBoard[i][j].SetPosition(gameBoard[i][j].GetX(), gameBoard[i][j].GetY() + 10);
				}
			}
			if (j > 2) {
				gameBoard[i][j].SetPosition(gameBoard[i][j].GetX() + 10, gameBoard[i][j].GetY());
				if (j > 5) {
					gameBoard[i][j].SetPosition(gameBoard[i][j].GetX() + 10, gameBoard[i][j].GetY());
				}
			}
		}
	}
}
void ClearCells(int pattern[][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (pattern[i][j] == 0) {
				gameBoard[i][j].SetValue(0);
				gameBoard[i][j].SetSprite(TILE_BLANK);

			}
		}
	}
}

void SetupBoard(int masterGameBoard[][9], int pattern[][9]) {
	for (int i = 0; i < COL_COUNT; ++i) {
		for (int j = 0; j < ROW_COUNT; ++j) {
			//gameBoard[i][j].SetValue(masterGameBoard[i][j]);





			switch (masterGameBoard[i][j]) {
			case 1:
				gameBoard[i][j].SetSprite(TILE_1);
				gameBoard[i][j].SetValue(1);
				gameBoard[i][j].SetWinValue(1);
				//gameBoard[i][j].LockTile();
				break;
			case 2:
				gameBoard[i][j].SetSprite(TILE_2);
				gameBoard[i][j].SetValue(2);
				gameBoard[i][j].SetWinValue(2);
				//gameBoard[i][j].LockTile();
				break;
			case 3:
				gameBoard[i][j].SetSprite(TILE_3);
				gameBoard[i][j].SetValue(3);
				gameBoard[i][j].SetWinValue(3);
				//gameBoard[i][j].LockTile();
				break;
			case 4:
				gameBoard[i][j].SetSprite(TILE_4);
				gameBoard[i][j].SetValue(4);
				gameBoard[i][j].SetWinValue(4);
				//gameBoard[i][j].LockTile();
				break;
			case 5:
				gameBoard[i][j].SetSprite(TILE_5);
				gameBoard[i][j].SetValue(5);
				gameBoard[i][j].SetWinValue(5);
				//gameBoard[i][j].LockTile();
				break;
			case 6:
				gameBoard[i][j].SetSprite(TILE_6);
				gameBoard[i][j].SetValue(6);
				gameBoard[i][j].SetWinValue(6);
				//gameBoard[i][j].LockTile();
				break;
			case 7:
				gameBoard[i][j].SetSprite(TILE_7);
				gameBoard[i][j].SetValue(7);
				gameBoard[i][j].SetWinValue(7);
				//gameBoard[i][j].LockTile();
				break;
			case 8:
				gameBoard[i][j].SetSprite(TILE_8);
				gameBoard[i][j].SetValue(8);
				gameBoard[i][j].SetWinValue(8);
				//gameBoard[i][j].LockTile();
				break;
			case 9:
				gameBoard[i][j].SetSprite(TILE_9);
				gameBoard[i][j].SetValue(9);
				gameBoard[i][j].SetWinValue(9);
				//gameBoard[i][j].LockTile();
				break;
			default:
				gameBoard[i][j].SetSprite(TILE_BLANK);
				break;

			}
			if (pattern[i][j] == 0) {
				gameBoard[i][j].SetValue(0);
				gameBoard[i][j].SetSprite(TILE_BLANK);
				gameBoard[i][j].UnlockTile();

			}
		}
	}
}

bool BoardFull() {
	bool boardFull = true;
	for (int i = 0; i < COL_COUNT; ++i) {
		for (int j = 0; j < ROW_COUNT; ++j) {
			if (gameBoard[i][j].GetValue() < 1) {
				boardFull = false;
				break;
			}
		}
	}
	std::cout << "\nBoard Full - " << boardFull;
	return boardFull;
}
bool CheckWin() {
	std::cout << "\nCheck win ...";
	bool win = true;

	for (int i = 0; i < COL_COUNT; ++i) {
		for (int j = 0; j < ROW_COUNT; ++j) {
			if (gameBoard[i][j].GetValue() != gameBoard[i][j].GetWinValue()) {
				win = false;
				break;
			}
		}
	}
	std::cout << "\nGameWon - " << win;
	if (win) {
		SetState(STATE_WIN);
	}
	return win;
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