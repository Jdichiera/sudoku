#pragma once
#include "texture.h"
class Tile {
public:
	Tile();
	~Tile();
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
	Texture tileSpriteSheetTexture;
	Texture GetTexture();

private:
	TileSprite currentSprite;
	SDL_Point position;
	int value;
	int winValue;
	bool locked;
};
Texture Tile::GetTexture() {
	return tileSpriteSheetTexture;
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
TileSprite Tile::GetSprite() {
	return currentSprite;
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
void Tile::Render() {
	tileSpriteSheetTexture.Render(position.x, position.y, &spriteSet[currentSprite]);
}