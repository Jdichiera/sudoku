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