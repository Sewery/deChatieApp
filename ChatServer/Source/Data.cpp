#include "Data.h"


UserData::UserData(const char* text, int ip,int id ):id(id),ipAddress(ip)
{
	assert(strlen(text) < sizeof(nick));
	copyCString(nick, text);
	nickLength = strlen(nick);
}

TextTexture::TextTexture(Color color, SDL_FRect winPos, SDL_Texture *texture, const char* txt):
	color(color), winPos(winPos)
{
	copyCString(text, txt);
	textLength = strlen(text);
}
