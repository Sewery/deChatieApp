#include "..\Util\Data.h"


UserData::UserData(const char* text, int ip,int id ):id(id),ipAddress(ip)
{
	//assert(strlen(text) < sizeof(nick));
	copyCString(nick, text);
	nickLength = strlen(nick);
}

TextTexture::TextTexture(Color color, SDL_FRect winPos, SDL_Texture *texture, const char* txt):
	color(color), winPos(winPos)
{
	copyCString(text, txt);
	textLength = strlen(text);
}/*
std::ostream& operator<<(std::ostream& os, const Message& mess)
{
	SDL_Color c = palette.at(mess.messLineTexture.color);
	os <<"Message data:\n"
	<< "\tText Texture data:\n"
	<< "\t\tColor rgb data: "<< c.r<<","<< c.g << ","<< c.b<<'\n'
	<< "\t\tPosition in window and size data: coord.x : "<<mess.messLineTexture.winPos.x
	<< ", coord.y : "<<mess.messLineTexture.winPos.y
	<< ", height : " << mess.messLineTexture.winPos.h
	<< ", width : " << mess.messLineTexture.winPos.w<<"\n"
	<< "\t\tText: "<< mess.messLineTexture.text<<"\n"
	<< "\tUser Data:\n"
	<< "\t\t Ip Address: "<<mess.user.ipAddress<<"\n"
	<< "\t\t Id: " << mess.user.id << "\n"
	<< "\t\t Nickname: " << mess.user.nick << "\n";
	return os;
}
*/