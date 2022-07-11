//#pragma once

#pragma once
#include "Config.hpp"
class LightTexture
{
private:
	const std::string path;
	SDL_Rect currentPositon;
	SDL_Texture* tTexture;
	//The window renderer
	SDL_Renderer* tRenderer;
	//
	
public:
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	//initalize
	LightTexture(const std::string &, SDL_Rect, SDL_Renderer*);

	//Delocates memory
	~LightTexture();
	//
	void free();
	//
	bool loadFile();
	//Creates image from font string
	bool loadFromRenderedText(const std::string &, SDL_Color, TTF_Font*);
	void render(int, int, SDL_Rect = { 0,0,0,0 });
	void render(int , int, SDL_Rect , double , SDL_Point* =nullptr , SDL_RendererFlip= SDL_FLIP_NONE) ;
	void setPositionAndSize(SDL_Rect);
	void setRenderer(SDL_Renderer*);
	int getHeight() const;
	int getWidth() const;
	int getPosX() const;
	int getPosY() const;
	SDL_Rect getCurrentPositon() ;


};