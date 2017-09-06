#pragma once
const int SWIDTH = 724; // 679
const int SHEIGHT = 768;
const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
const int TILE_COUNT = 10;
const int ROW_COUNT = 9;
const int COL_COUNT = 9;
const int PADDING_X = TILE_HEIGHT;//SWIDTH /4;
const int PADDING_Y = TILE_HEIGHT; //SHEIGHT / 8;
const int BORDER_WIDTH = 4;
const int BORDER_HEIGHT = 626;
const int INNER_BORDER_HEIGHT = 595;
const int TILE_BORDER_HEIGHT = 2;
const int TILE_BORDER_WIDTH = 172;
const int TILE_PADDING = 10;
const int BOARD_MAT_X = PADDING_X - TILE_HEIGHT / 2;
const int BOARD_MAT_Y = PADDING_Y - TILE_HEIGHT / 2;
const int BOARD_MAT_WIDTH = TILE_HEIGHT * TILE_COUNT + TILE_PADDING * 2 ; //(TILE_COUNT - 1) + 20;
const int BOARD_MAT_HEIGHT = TILE_HEIGHT * (TILE_COUNT + 1) + TILE_PADDING * 2; // (TILE_COUNT - 1 ) + 20; // TILE_HEIGHT * (TILE_COUNT + 1) + TILE_HEIGHT / 2;


// Color Palette
// http://www.color-hex.com/color-palette/44252
//const SDL_Color green{ 96, 150, 116, 1 };
//const SDL_Color grayBlue{ 117, 167, 178, 1 };
//const SDL_Color purple{ 133, 82, 176, 1 };
//const SDL_Color blue{ 102, 107, 180, 1 };
//const SDL_Color rose{ 169, 63, 127, 1 };

// Color Palette
// http://www.color-hex.com/color-palette/44135
//const SDL_Color backgroundColor{ 255, 255, 255, 1 };	// white
const SDL_Color backgroundColor{ 0, 0, 0, 1 };			// black
//const SDL_Color borderColor{ 49, 105, 138, 1 };			// DK blue
const SDL_Color borderColor{ 12, 64, 95, 1 };			// Darker blue 0C405F
//const SDL_Color borderColor{ 0, 0, 0, 1 };			// black
const SDL_Color darkGreen{ 59, 134, 134, 1 };			//dk green
const SDL_Color lightGreen{ 163, 197, 163, 1 };			// lt green
//const SDL_Color backgroundColor{ 219, 219, 219, 1 };	// gray
const SDL_Color salmon{ 240, 128, 128, 1 };				// salmon

const int testBoard[9][9]{ { 0, 1, 2, 8, 6, 7, 3, 9, 4 },
						   { 4, 9, 7, 5, 2, 3, 8, 1, 6 },
						   { 8, 6, 3, 9, 1, 4, 7, 2, 5 },
						   { 7, 5, 9, 4, 3, 6, 1, 8, 2 },
						   { 2, 8, 1, 7, 9, 5, 6, 4, 3 },
						   { 6, 3, 4, 1, 8, 2, 5, 7, 9 },
						   { 1, 7, 6, 3, 4, 9, 2, 5, 8 },
						   { 9, 2, 8, 6, 5, 1, 4, 3, 7 },
						   { 3, 4, 5, 2, 7, 8, 9, 6, 1 }
						  };

const int cross[9][9] = { { 0, 0, 0, 1, 1, 1, 0, 0, 0 },
						  { 0, 0, 0, 1, 0, 1, 0, 0, 0 },
						  { 0, 0, 0, 1, 0, 1, 0, 0, 0 },
						  { 1, 1, 1, 1, 0, 1, 1, 1, 1 },
						  { 1, 0, 0, 1, 0, 1, 0, 0, 1 },
						  { 1, 1, 1, 1, 0, 1, 1, 1, 1 },
						  { 0, 0, 0, 1, 0, 1, 0, 0, 0 },
						  { 0, 0, 0, 1, 0, 1, 0, 0, 0 },
						  { 0, 0, 0, 1, 1, 1, 0, 0, 0 } 
};

const int FULL[9][9] = { { 0, 1, 1, 0, 1, 0, 1, 1, 0 },
						 { 1, 0, 1, 1, 1, 1, 1, 1, 1 },
						 { 1, 0, 1, 1, 0, 1, 1, 0, 1 },
						 { 1, 1, 1, 1, 1, 0, 1, 1, 1 },
						 { 0, 0, 1, 0, 1, 1, 1, 0, 1 },
						 { 1, 1, 1, 1, 1, 1, 0, 1, 1 },
						 { 0, 0, 1, 0, 1, 1, 1, 1, 1 },
						 { 1, 0, 1, 1, 1, 1, 0, 0, 1 },
						 { 1, 0, 1, 0, 1, 1, 0, 1, 1 } 
};
