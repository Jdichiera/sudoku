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
	Tile gameBoard[COL_COUNT][ROW_COUNT];
	Tile guiTiles[10];
	Texture gameTextures;
	


public:
	bool playing = false;
	GameScreen();
	~GameScreen();

	void HandleEvents();
	void Logic();
	void Render();
	void CheckSolved();
	void DigHoles();
	void SetupBoard(int masterGameBoard[][9]);
	bool BoardFull();
};

void GameScreen::SetupBoard(int masterGameBoard[][9]) {

	for (int i = 0; i < COL_COUNT; ++i) {
		for (int j = 0; j < ROW_COUNT; ++j) {

			switch (masterGameBoard[i][j]) {
			case 1:
				gameBoard[i][j].SetSprite(LOCKED_TILE_1);
				gameBoard[i][j].SetValue(1);
				gameBoard[i][j].SetWinValue(1);
				break;
			case 2:
				gameBoard[i][j].SetSprite(LOCKED_TILE_2);
				gameBoard[i][j].SetValue(2);
				gameBoard[i][j].SetWinValue(2);
				break;
			case 3:
				gameBoard[i][j].SetSprite(LOCKED_TILE_3);
				gameBoard[i][j].SetValue(3);
				gameBoard[i][j].SetWinValue(3);
				break;
			case 4:
				gameBoard[i][j].SetSprite(LOCKED_TILE_4);
				gameBoard[i][j].SetValue(4);
				gameBoard[i][j].SetWinValue(4);
				break;
			case 5:
				gameBoard[i][j].SetSprite(LOCKED_TILE_5);
				gameBoard[i][j].SetValue(5);
				gameBoard[i][j].SetWinValue(5);
				break;
			case 6:
				gameBoard[i][j].SetSprite(LOCKED_TILE_6);
				gameBoard[i][j].SetValue(6);
				gameBoard[i][j].SetWinValue(6);
				break;
			case 7:
				gameBoard[i][j].SetSprite(LOCKED_TILE_7);
				gameBoard[i][j].SetValue(7);
				gameBoard[i][j].SetWinValue(7);
				break;
			case 8:
				gameBoard[i][j].SetSprite(LOCKED_TILE_8);
				gameBoard[i][j].SetValue(8);
				gameBoard[i][j].SetWinValue(8);
				break;
			case 9:
				gameBoard[i][j].SetSprite(LOCKED_TILE_9);
				gameBoard[i][j].SetValue(9);
				gameBoard[i][j].SetWinValue(9);
				break;
			default:
				gameBoard[i][j].SetSprite(LOCKED_TILE_BLANK);
				break;

			}
		}
	}
}

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
	BoardGenerator boardGenerator;
	boardGenerator.FillCells();
	boardGenerator.PrintBoard();
	tempTile.SetPosition(999, 999);
	
	// Place the game tiles
	for (int i = 0; i < COL_COUNT; i++) {
		for (int j = 0; j < ROW_COUNT; j++) {
			gameBoard[i][j].SetPosition((TILE_WIDTH * j) + PADDING_X, (TILE_HEIGHT * i) + PADDING_Y);
		}
	}
	// Add padding to the tiles
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
	// Place the GUI tiles
	for (int i = 0; i < TILE_COUNT; ++i) {
		guiTiles[i].SetPosition((TILE_WIDTH * i) + PADDING_X - 24, PADDING_Y + (ROW_COUNT * TILE_HEIGHT) + TILE_HEIGHT - TILE_HEIGHT / 4);
		guiTiles[i].SetValue(i);
	}
	SetupBoard(boardGenerator.board);
	DigHoles();
}

bool GameScreen::BoardFull() {
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
void GameScreen::DigHoles() {
	int boardPattern[9]{ 1 };
	int firstRows[4]{ 0 };
	int maxHoles = 0;
	int digHole = 0;
	int holeCount = 0;
	if (debug == false) {
		for (int i = 0; i < 5; i++) {
			boardPattern[i] = rand() % 6 + 1;
		}


		for (int j = 5; j < 9; j++) {
			boardPattern[j] = boardPattern[8 - j];
		}
	}
	for (int i = 0; i < 9; i++) {
		holeCount += boardPattern[i];
	}
	for (int i = 0; i < 9; i++) {
		std::cout << boardPattern[i];
	}
	for (int i = 0; i < 9; i++) {
		maxHoles = boardPattern[i];
		for (int j = 0; j < 9; j++) {
			if (gameBoard[i][j].GetValue() != 0) {
				if (maxHoles > 0) {
					digHole = rand() % 10;
					if (digHole % 2 == 0) {
						gameBoard[i][j].SetValue(0);
						gameBoard[i][j].SetSprite(UNLOCKED_TILE_BLANK);
						gameBoard[i][j].UnlockTile();
						maxHoles--;
					}
				}
			}
			if (j == 8) {
				if (maxHoles != 0) {
					j = -1;
				}
			}
		}
	}
}

void GameScreen::Logic() {

}
void GameScreen::CheckSolved() {
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
		//SetState(STATE_WIN);
		solved = true;
	}
	//return win;
}
GameScreen::~GameScreen() {
}

void GameScreen::Render() {
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.b, backgroundColor.g, 0);
	SDL_RenderClear(renderer);
	// Draw background
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	//Draw game board mat
	SDL_Rect boardMat;
	boardMat.x = BOARD_MAT_X;
	boardMat.y = BOARD_MAT_Y;
	boardMat.h = BOARD_MAT_HEIGHT;
	boardMat.w = BOARD_MAT_WIDTH;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderFillRect(renderer, &boardMat);
	for (int i = 0; i < COL_COUNT; ++i) {
		for (int j = 0; j < ROW_COUNT; ++j) {
			gameBoard[i][j].Render();
		}
	}

	if (solved == false) {
		// draw GUI buttons
		guiTiles[0].SetSprite(UNLOCKED_TILE_BLANK);
		guiTiles[1].SetSprite(UNLOCKED_TILE_1);
		guiTiles[2].SetSprite(UNLOCKED_TILE_2);
		guiTiles[3].SetSprite(UNLOCKED_TILE_3);
		guiTiles[4].SetSprite(UNLOCKED_TILE_4);
		guiTiles[5].SetSprite(UNLOCKED_TILE_5);
		guiTiles[6].SetSprite(UNLOCKED_TILE_6);
		guiTiles[7].SetSprite(UNLOCKED_TILE_7);
		guiTiles[8].SetSprite(UNLOCKED_TILE_8);
		guiTiles[9].SetSprite(UNLOCKED_TILE_9);

		for (int i = 0; i < TILE_COUNT; ++i) {
			guiTiles[i].Render();
		}
	}

	SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.b, borderColor.g, SDL_ALPHA_OPAQUE);

	// Draw main Sudoku box outline
	int firstTileX = gameBoard[0][0].GetX();
	int firstTileY = gameBoard[0][0].GetY();
	int lastTileX = gameBoard[8][8].GetX();
	int lastTileY = gameBoard[8][8].GetY();
	const int BORDER_PADDING_X = PADDING_X + 9;

	SDL_Rect topBorder{ firstTileX - 16, firstTileY - 7, BORDER_HEIGHT, BORDER_WIDTH };
	SDL_Rect bottomBorder{ firstTileX - 16, lastTileY + TILE_HEIGHT, BORDER_HEIGHT, BORDER_WIDTH };
	SDL_Rect leftBorder{ firstTileX - 7, firstTileY - 16, BORDER_WIDTH, BORDER_HEIGHT };
	SDL_Rect righBorder{ lastTileX + TILE_HEIGHT, firstTileY - 16, BORDER_WIDTH, BORDER_HEIGHT };

	SDL_RenderFillRect(renderer, &topBorder);
	SDL_RenderFillRect(renderer, &bottomBorder);
	SDL_RenderFillRect(renderer, &leftBorder);
	SDL_RenderFillRect(renderer, &righBorder);

	//// Block outlines
	SDL_Rect blockLeft{ PADDING_X + 3 + (TILE_HEIGHT * 3) , PADDING_Y, BORDER_WIDTH, INNER_BORDER_HEIGHT };
	SDL_Rect blockRight{ PADDING_X + 13 + (6 * TILE_HEIGHT), PADDING_Y, BORDER_WIDTH, INNER_BORDER_HEIGHT };
	SDL_Rect blockTop{ PADDING_X, PADDING_Y + 3 + (TILE_HEIGHT * 3), INNER_BORDER_HEIGHT, BORDER_WIDTH };
	SDL_Rect blockBottom{ PADDING_X, PADDING_Y + 13 + (6 * TILE_HEIGHT), INNER_BORDER_HEIGHT, BORDER_WIDTH };
	SDL_RenderFillRect(renderer, &blockLeft);
	SDL_RenderFillRect(renderer, &blockRight);
	SDL_RenderFillRect(renderer, &blockTop);
	SDL_RenderFillRect(renderer, &blockBottom);

	// Draw borders around tiles
	// Left top horizontal & vertical
	SDL_Rect leftTopTopH{ PADDING_X + 9, (PADDING_Y - 1) + TILE_HEIGHT,  TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect leftTopBotH{ PADDING_X + 9, (PADDING_Y - 1) + (TILE_HEIGHT * 2), TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect leftTopTopV{ (PADDING_X - 1) + TILE_HEIGHT, PADDING_Y + 9,  TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect leftTopBotV{ (PADDING_X - 1) + (TILE_HEIGHT * 2), PADDING_Y + 9, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &leftTopTopH);
	SDL_RenderFillRect(renderer, &leftTopBotH);
	SDL_RenderFillRect(renderer, &leftTopTopV);
	SDL_RenderFillRect(renderer, &leftTopBotV);

	// Left middle horizontal & vertical
	SDL_Rect leftMidTopH{ PADDING_X + 9, (PADDING_Y - 1) + (TILE_HEIGHT * 4) + 10,  TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect leftMidBotH{ PADDING_X + 9, (PADDING_Y - 1) + (TILE_HEIGHT * 5) + 10, TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect leftMidTopV{ (PADDING_X - 1) + TILE_HEIGHT, (PADDING_Y - 1) + (TILE_HEIGHT * 3) + 19,  TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect leftMidBotV{ (PADDING_X - 1) + (TILE_HEIGHT * 2),  (PADDING_Y - 1) + (TILE_HEIGHT * 3) + 19, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &leftMidTopH);
	SDL_RenderFillRect(renderer, &leftMidBotH);
	SDL_RenderFillRect(renderer, &leftMidTopV);
	SDL_RenderFillRect(renderer, &leftMidBotV);

	// Left bottom horizontal & vertical
	SDL_Rect leftBotTopH{ PADDING_X + 9, (PADDING_Y - 1) + (TILE_HEIGHT * 7) + 20,  TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect leftBotBotH{ PADDING_X + 9, (PADDING_Y - 1) + (TILE_HEIGHT * 8) + 20, TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect leftBotTopV{ (PADDING_X - 1) + TILE_HEIGHT, (PADDING_Y - 1) + (TILE_HEIGHT * 6) + 29,  TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect leftBotBotV{ (PADDING_X - 1) + (TILE_HEIGHT * 2), (PADDING_Y - 1) + (TILE_HEIGHT * 6) + 29, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &leftBotTopH);
	SDL_RenderFillRect(renderer, &leftBotBotH);
	SDL_RenderFillRect(renderer, &leftBotTopV);
	SDL_RenderFillRect(renderer, &leftBotBotV);


	// Middle top
	SDL_Rect midTopTopH{ PADDING_X + 9 + (TILE_HEIGHT * 3) + 11, (PADDING_Y - 1) + TILE_HEIGHT,  TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect midTopBotH{ PADDING_X + 9 + (TILE_HEIGHT * 3) + 11, (PADDING_Y - 1) + (TILE_HEIGHT * 2), TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect midTopLeftV{ PADDING_X + 9 + (TILE_HEIGHT * 4), PADDING_Y + 9,  TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect midTopRightV{ PADDING_X + 9 + (TILE_HEIGHT * 5), PADDING_Y + 9, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &midTopTopH);
	SDL_RenderFillRect(renderer, &midTopBotH);
	SDL_RenderFillRect(renderer, &midTopLeftV);
	SDL_RenderFillRect(renderer, &midTopRightV);

	// Middle middle
	SDL_Rect midMidTopH{ PADDING_X + 9 + (TILE_HEIGHT * 3) + 11, PADDING_Y + 9 + (TILE_HEIGHT * 4), TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect midMidBotH{ PADDING_X + 9 + (TILE_HEIGHT * 3) + 11, PADDING_Y + 9 + (TILE_HEIGHT * 5), TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect midMidLeftV{ PADDING_X + 9 + (TILE_HEIGHT * 4), PADDING_Y + 9 + (TILE_HEIGHT * 3) + 11, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect midMidRightV{ PADDING_X + 9 + (TILE_HEIGHT * 5), PADDING_Y + 9 + (TILE_HEIGHT * 3) + 11, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &midMidTopH);
	SDL_RenderFillRect(renderer, &midMidBotH);
	SDL_RenderFillRect(renderer, &midMidLeftV);
	SDL_RenderFillRect(renderer, &midMidRightV);

	//// Middle bottom
	SDL_Rect midBotTopH{ PADDING_X + 9 + (TILE_HEIGHT * 3) + 11, PADDING_Y + 9 + (TILE_HEIGHT * 7) + 10, TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect midBotBotH{ PADDING_X + 9 + (TILE_HEIGHT * 3) + 11, PADDING_Y + 9 + (TILE_HEIGHT * 8) + 10, TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect midBotLeftV{ PADDING_X + 9 + (TILE_HEIGHT * 4), PADDING_Y + 9 + (TILE_HEIGHT * 6) + 20, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect midBotRightV{ PADDING_X + 9 + (TILE_HEIGHT * 5), PADDING_Y + 9 + (TILE_HEIGHT * 6) + 20, TILE_BORDER_HEIGHT,TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &midBotTopH);
	SDL_RenderFillRect(renderer, &midBotBotH);
	SDL_RenderFillRect(renderer, &midBotLeftV);
	SDL_RenderFillRect(renderer, &midBotRightV);

	// Right top
	SDL_Rect rightTopTopH{ PADDING_X + 9 + (TILE_HEIGHT * 6) + 20, (PADDING_Y - 1) + TILE_HEIGHT, TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect rightTopBotH{ PADDING_X + 9 + (TILE_HEIGHT * 6) + 20, (PADDING_Y - 1) + (TILE_HEIGHT * 2), TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect rightTopLeftV{ PADDING_X + 9 + (TILE_HEIGHT * 7) + 10, PADDING_Y + 9, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect rightTopRightV{ PADDING_X + 9 + (TILE_HEIGHT * 8) + 10, PADDING_Y + 9, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &rightTopTopH);
	SDL_RenderFillRect(renderer, &rightTopBotH);
	SDL_RenderFillRect(renderer, &rightTopLeftV);
	SDL_RenderFillRect(renderer, &rightTopRightV);

	// Right middle
	SDL_Rect rightMidTopH{ PADDING_X + 9 + (TILE_HEIGHT * 6) + 20, PADDING_Y + 9 + (TILE_HEIGHT * 4), TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect rightMidBotH{ PADDING_X + 9 + (TILE_HEIGHT * 6) + 20, PADDING_Y + 9 + (TILE_HEIGHT * 5), TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect rightMidLeftV{ PADDING_X + 9 + (TILE_HEIGHT * 7) + 10, PADDING_Y + 9 + (TILE_HEIGHT * 3) + 11, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect rightMidRightV{ PADDING_X + 9 + (TILE_HEIGHT * 8) + 10, PADDING_Y + 9 + (TILE_HEIGHT * 3) + 11, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &rightMidTopH);
	SDL_RenderFillRect(renderer, &rightMidBotH);
	SDL_RenderFillRect(renderer, &rightMidLeftV);
	SDL_RenderFillRect(renderer, &rightMidRightV);

	// Right bottom
	SDL_Rect rightBotTopH{ PADDING_X + 9 + (TILE_HEIGHT * 6) + 20, PADDING_Y + 9 + (TILE_HEIGHT * 7) + 10, TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect rightBotBotH{ PADDING_X + 9 + (TILE_HEIGHT * 6) + 20, PADDING_Y + 9 + (TILE_HEIGHT * 8) + 10, TILE_BORDER_WIDTH, TILE_BORDER_HEIGHT };
	SDL_Rect rightBotLeftV{ PADDING_X + 9 + (TILE_HEIGHT * 7) + 10, PADDING_Y + 9 + (TILE_HEIGHT * 6) + 20, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };
	SDL_Rect rightBotRightV{ PADDING_X + 9 + (TILE_HEIGHT * 8) + 10, PADDING_Y + 9 + (TILE_HEIGHT * 6) + 20, TILE_BORDER_HEIGHT, TILE_BORDER_WIDTH };

	SDL_RenderFillRect(renderer, &rightBotTopH);
	SDL_RenderFillRect(renderer, &rightBotBotH);
	SDL_RenderFillRect(renderer, &rightBotLeftV);
	SDL_RenderFillRect(renderer, &rightBotRightV);

	if (solved == true) {
		if (rotation == 5) {
			direction = -1;
		}
		else if (rotation == -5) {
			direction = 1;
		}

		if (direction == 1) {
			rotation++;
		}
		else if (direction == -1) {
			rotation--;
		}
		if (playAgainButton.y > 675) {
			playAgainButton.y -= 5;
		}
		else {
			if (mouseOverPlayAgainButton) {
				playAgainButton.x = 264;
				playAgainButton.y = 671;
				playAgainButton.w = 194;
				playAgainButton.h = 66;
			}
			else {
				playAgainButton.x = 268;
				playAgainButton.y = 675;
				playAgainButton.w = 186;
				playAgainButton.h = 59;
			}
		}
		SDL_RenderCopy(renderer, playAgainTexture, NULL, &playAgainButton);
		for (int i = 0; i < COL_COUNT; ++i) {
			for (int j = 0; j < ROW_COUNT; ++j) {
				if (direction > 0){
					gameBoard[i][j].SetPosition(gameBoard[i][j].GetX() + 1, gameBoard[i][j].GetY() + 1);
				}
				else if (direction < 0) {
					gameBoard[i][j].SetPosition(gameBoard[i][j].GetX() - 1, gameBoard[i][j].GetY() - 1);
				}
			}
		}
	}
	// Mark the unlocked tiles
	tempTile.Render();
	SDL_RenderPresent(renderer);
	//}
}
void GameScreen::HandleEvents() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SetState(STATE_EXIT);
		}
		if (solved == false) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				for (int i = 0; i < TILE_COUNT; i++) {
					tilePosition = guiTiles[i].GetPosition();
					if (event.button.x > guiTiles[i].GetX() &&
						event.button.x < guiTiles[i].GetX() + TILE_WIDTH &&
						event.button.y > guiTiles[i].GetY() &&
						event.button.y < guiTiles[i].GetY() + TILE_HEIGHT) {
						tempTile = guiTiles[i];
						draggingTile = true;
						Mix_PlayChannel(-1, soundPickUp, 0);
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
								Mix_PlayChannel(-1, soundSet, 0);
								if (!gameBoard[i][j].Locked()) {
									gameBoard[i][j].SetSprite(tempTile.GetSprite());
									gameBoard[i][j].SetValue(tempTile.GetValue());
									if (BoardFull()) {
										CheckSolved();
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
		else {
			if (event.type == SDL_MOUSEMOTION) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (event.button.x > playAgainButton.x && event.button.x < playAgainButton.x + playAgainButton.w &&
					event.button.y > playAgainButton.y && event.button.y < playAgainButton.y + playAgainButton.h) {
					mouseOverPlayAgainButton = true;
				}
				else {
					mouseOverPlayAgainButton = false;
				}

			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.x > playAgainButton.x && event.button.x < playAgainButton.x + playAgainButton.w &&
					event.button.y > playAgainButton.y && event.button.y < playAgainButton.y + playAgainButton.h) {
					SetState(STATE_GAME);
				}
			}
		}
	}
}
