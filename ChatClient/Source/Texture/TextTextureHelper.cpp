#include "..\Texture\TextTextureHelper.h"
#include "..\ResourceController\MessageHelper.h"
#include "..\Gui\Window.h"
#include "..\ResourceController\UserDataHelper.h" 
bool TextTextureHelper::loadTextTexture(TextTexture& pocket, TTF_Font* pFont, SDL_Renderer* pRen)
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(pFont, pocket.text, palette.at(pocket.color));
	if (textSurface == nullptr)
	{
		LOG_ERROR("Unable to render text surface! SDL_ttf Error: " << TTF_GetError());
		return false;
	}

	//Delete last texture
	SDL_DestroyTexture(pocket.ptrSDLTexture);
	pocket.ptrSDLTexture = nullptr;
	//Create texture from surface pixels
	pocket.ptrSDLTexture = SDL_CreateTextureFromSurface(pRen, textSurface);
	if (pocket.ptrSDLTexture == nullptr)
	{
		LOG_ERROR("Unable to create texture from rendered text! SDL Error:" << SDL_GetError() );
		return false;
	}

	pocket.winPos.w = (float)textSurface->w;
	pocket.winPos.h = (float)textSurface->h;
	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	//Return success
	return pocket.ptrSDLTexture != nullptr;
}

bool TextTextureHelper::loadMedia( const int & sizeFont, TextTexture & pocket, SDL_Renderer* pRen)
{
	bool success = true;
	TTF_Font* pFont = TTF_OpenFont("Resource/Fonts/AnekLatin.ttf", sizeFont);
	if (pFont == nullptr)
	{
		LOG_ERROR("Unable to render text surface! SDL_ttf Error: " << TTF_GetError() );
		return success = false;
	}

	if (!TextTextureHelper::loadTextTexture( pocket, pFont, pRen))
	{
		LOG_ERROR("Failed to render text texture!");
		return success = false;
	}
	TTF_CloseFont(pFont);

	return success;
}

bool  TextTextureHelper::loadMediaMessagesFromServer(const int& sizeFont, SDL_Renderer* pRen, WinCompsContr * win)
{
	
	for (auto& mess : DataCollector::chatContent)
	{
		if (!mess.isInit)
		{
			break;
		}
		if (DataCollector::loadedMessages[mess.id] == false)
		{
			DataCollector::loadedMessages[mess.id] = true;
			loadMedia(sizeFont, mess.user.nickTexture, pRen);
			for (auto& line : mess.messLineTexture)
			{
				//std::cout << "Texture: " << line.text << " , " << line.winPos.x << "," << line.winPos.y << "," << line.winPos.w << "," << line.winPos.h << '\n';
				if (strlen(line.text) > 0)
					loadMedia(sizeFont, line, pRen);
			}
			if (!mess.isPositioned) {
				UserDataHelper::givePositonForUserTexture(mess.user);
				MessageHelper::givePositionForNewMessage(mess);
				mess.isPositioned = true;
			}

		}

		
		//std::cout << "Texture: " << mess.user.nickTexture.text << " , " << mess.user.nickTexture.winPos.x << "," << mess.user.nickTexture.winPos.y << "," << mess.user.nickTexture.winPos.w << "," << mess.user.nickTexture.winPos.h << '\n'
		win->messageViewRegulation();
	}
	return true;
}
void TextTextureHelper::centerOnScreenTexture(int windowW, int windowH, TextTexture& text)
{
	text.winPos.x = (windowW / 2) - (text.winPos.w / 2);
	text.winPos.y = (windowH / 2) - (text.winPos.h / 2);
}
void TextTextureHelper::render( TextTexture& texture, SDL_Renderer* pRen )
{
	SDL_RenderCopyF(pRen, texture.ptrSDLTexture, nullptr, &texture.winPos);
}

void TextTextureHelper::renderMessagesFromServer(SDL_Renderer* pRen,int yMax)
{
	for (auto& mess : DataCollector::chatContent)
	{
		if (!mess.isInit)
		{
			break;
		}
		if (mess.isPositioned)
		{
			if (mess.user.nickTexture.winPos.y >= 0
				&& mess.user.nickTexture.winPos.y < (yMax - MessageProperties::Space_For_Line))
			{
				render(mess.user.nickTexture, pRen);
			}
				
			for (auto &line : mess.messLineTexture)
			{
				if (line.winPos.y >= 0 
					&& line.winPos.y < (yMax-MessageProperties::Space_For_Line))
				{
					render(line, pRen);
				}
			}

		}
		
	}
}


void TextTextureHelper::createRectAndRender(bool fill,  SDL_FRect rect, SDL_Renderer* ren, Color c,int extRect)
{
	//Render red filled quad
	SDL_Rect r ={
		rect.x - extRect,
		rect.y - extRect,
		rect.w + (2 *extRect),
		rect.h + (2 *extRect)
	};
	SDL_Color col = palette.at(c);
	SDL_SetRenderDrawColor(ren, col.r,col.g,col.b,col.a);
	
	fill==true?	SDL_RenderFillRect(ren, &r): SDL_RenderDrawRect(ren, &r);
}
