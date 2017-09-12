#pragma once
#include "tile.h"
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