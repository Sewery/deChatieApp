#pragma once


#include "LightTexture.h"
#include "CollisionBox.h"

class LightEntity 
{
public:
		LightTexture* eTextures;
		SDL_Renderer* eRenderer;
		CollisionBox * eCollisionBox;
		//const std::string name;
		LightEntity(const std::string&, SDL_Renderer*, SDL_Rect, SDL_Rect);
		~LightEntity();
		virtual bool loadMedia() = 0;
		virtual void render() = 0;
		virtual void render(SDL_Rect)=0;
		virtual void close() = 0;
};
