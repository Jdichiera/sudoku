#pragma once
#include "globals.h"
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