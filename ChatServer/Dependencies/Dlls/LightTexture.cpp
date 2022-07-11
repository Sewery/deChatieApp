#include "LightTexture.h"

LightTexture::LightTexture(const std::string & path, SDL_Rect currentPositon, SDL_Renderer* tRenderer ):path(path)
{
	//Initialize
	this->tRenderer = tRenderer;
	this->currentPositon = currentPositon;
	tTexture = nullptr;

}

LightTexture::~LightTexture()
{
	// Deallocate
	free();
}
void LightTexture::free()
{
	// Free texture if it exists
	if (tTexture != nullptr)
	{
		SDL_DestroyTexture(tTexture);
		tTexture = nullptr;
		//currentPositon = { 0,0,0,0 };
	}
}

bool LightTexture::loadFile()
{
	//Get rid of preexisting texture
	free();
	if (tRenderer == nullptr)
	{
		std::cerr << "There is no renderer for LightTexture\n";
		return 0;
	}
	//Load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		std::cerr<<"Unable to load image "<<path<<" !SDL_image Error : "<<IMG_GetError()<<'\n';
		return 0;
	}

	//Create texture from surface pixels
	SDL_Texture* newTexture = nullptr;
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 179, 176, 187));
	newTexture = SDL_CreateTextureFromSurface(tRenderer, loadedSurface);
	
	if (newTexture == nullptr)
	{
		std::cerr << "Unable to create texture from " << path << " !SDL Error : " << SDL_GetError() << '\n';
		return 0;
	}

	//Get image size
	//currentPositon.w = loadedSurface->w;
	//currentPositon.h = loadedSurface->h;

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	tTexture = newTexture;
	return 1;
}
void LightTexture::render(int x, int y, SDL_Rect clip) 
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, currentPositon.w, currentPositon.h };
	SDL_Rect lastClip = { clip.x, clip.y,clip.w,clip.h };
	//Set clip rendering dimensions
	if (&lastClip != nullptr)
	{
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;
	}

	//Render to screen
	SDL_RenderCopy(tRenderer, tTexture, &lastClip, &renderQuad);
}
void  LightTexture::render(int x, int y, SDL_Rect clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, currentPositon.w, currentPositon.h };
	SDL_Rect lastClip = { clip.x, clip.y,clip.w,clip.h };
	//Set clip rendering dimensions
	if (&lastClip != nullptr)
	{
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;
	}

	//Render to screen
	SDL_RenderCopyEx(tRenderer, tTexture, &lastClip, &renderQuad,angle, center,flip);
}
bool LightTexture::loadFromRenderedText(const std::string& textureText, SDL_Color textColor, TTF_Font * font)
{
	//Get rid of preexisting texture
	free();
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}
	else
	{
		//Create texture from surface pixels
		tTexture = SDL_CreateTextureFromSurface(tRenderer, textSurface);
		if (tTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return 0;
		}
		currentPositon.w = textSurface->w;
		currentPositon.h = textSurface->h;
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	std::cout << "WWWW"<< currentPositon.x << " "<< currentPositon.y << " " << currentPositon.w << " " << currentPositon.h << "\n";
	//Return success
	return tTexture != nullptr;
}
void LightTexture::setPositionAndSize(SDL_Rect rect)
{
	currentPositon = rect;
}
void LightTexture::setRenderer(SDL_Renderer* renderer)
{
	this->tRenderer = renderer;
}
int LightTexture::getWidth() const
{
	return currentPositon.w;
}

int LightTexture::getHeight() const
{
	return currentPositon.h;
}

int LightTexture::getPosX() const
{
	return currentPositon.x;
}

int LightTexture::getPosY() const
{
	return currentPositon.y;
}
SDL_Rect LightTexture::getCurrentPositon() 
{
	return currentPositon;
}