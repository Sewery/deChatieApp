#pragma once
#include "..\ResourceController\DataCollector.h"
class WinCompsContr;
struct TextTextureHelper
{
private:
	static bool loadTextTexture(TextTexture &, TTF_Font*, SDL_Renderer*);
public:

	static bool loadMedia( const int&, TextTexture&, SDL_Renderer*);
	static void render( TextTexture&, SDL_Renderer*);
	static void centerOnScreenTexture(int , int , TextTexture&);
	static bool loadMediaMessagesFromServer(const int&,  SDL_Renderer*, WinCompsContr *);
	static void renderMessagesFromServer(SDL_Renderer*,int);
	
	static void createRectAndRender(bool ,const  SDL_FRect, SDL_Renderer*, Color,int );
};
