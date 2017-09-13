#pragma once
const int SWIDTH = 724;
const int SHEIGHT = 768;
const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
const int TILE_COUNT = 10;
const int ROW_COUNT = 9;
const int COL_COUNT = 9;
const int PADDING_X = TILE_HEIGHT;
const int PADDING_Y = TILE_HEIGHT;
const int BORDER_WIDTH = 4;
const int BORDER_HEIGHT = 626;
const int INNER_BORDER_HEIGHT = 595;
const int TILE_BORDER_HEIGHT = 2;
const int TILE_BORDER_WIDTH = 172;
const int TILE_PADDING = 10;
const int BOARD_MAT_X = PADDING_X - TILE_HEIGHT / 2;
const int BOARD_MAT_Y = PADDING_Y - TILE_HEIGHT / 2;
const int BOARD_MAT_WIDTH = TILE_HEIGHT * TILE_COUNT + TILE_PADDING * 2;
const int BOARD_MAT_HEIGHT = TILE_HEIGHT * (TILE_COUNT + 1) + TILE_PADDING * 2;

// Color Palette
// http://www.color-hex.com/color-palette/44135
const SDL_Color backgroundColor{ 0, 0, 0, 1 };			// black
//const SDL_Color borderColor{ 49, 105, 138, 1 };			// DK blue
const SDL_Color borderColor{ 12, 64, 95, 1 };			// Darker blue 0C405F
const SDL_Color darkGreen{ 59, 134, 134, 1 };			//dk green
const SDL_Color lightGreen{ 163, 197, 163, 1 };			// lt green
//const SDL_Color backgroundColor{ 219, 219, 219, 1 };	// gray
const SDL_Color salmon{ 240, 128, 128, 1 };				// salmon
