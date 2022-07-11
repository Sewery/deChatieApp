#pragma once
#include "Config.h"
#define TICKRATE 128
#define SEC_IN_MS 1000
#define TEN_SEC_IN_MS 10000

namespace Commands
{
	static const char* QUIT_COMMAND = "/quit";
	static const char* DISCONNECT = "/disconnect";

	static const char* Input_Statement = "Some Text";

	static const char* Entry_Statement = "Write your username";
	static const char* Bad_Nick_Statement = "Bad nickname. Try again";
	static const char* Lost_Connection_Statement = "You lost your connection";
	static const char* Info_After_Connection = "You can now send your messages";
	static const char* Not_Possible_Connect_Statement = "Can not connect to server";

}
namespace TextContentProperties
{
	static const int Additional_Characters = 2;
	static const int Max_Messages = 10000;
	static const int Max_Characters_Line = 100;
	static const int Max_Lines_In_Message = 10;
	static const int Max_Characters_Nick = 12;
	static const int Visible_Messages = 15;
	static const int Max_Users = 10;


}



enum class Color {
	white = 0,
	black = 1,
	red,
	green,
	blue,
	magneta,
	yellow,
	cyan,
	slategrey,
	dodgerblue,
	brass,
	grainsboro
};
const static std::unordered_map< Color, SDL_Color> palette
{
	{ Color::white , {255,255,255} },
	{ Color::black , {0,0,0} },
	{ Color::red , {255,0,0} },
	{ Color::green , {0,255,0} },
	{ Color::blue , {0,0,255} },
	{ Color::magneta , {255,0,255} },
	{ Color::yellow , {255,255,0} },
	{ Color::cyan , {0,255,255} },
	{ Color::slategrey,{112,128,144} },
	{ Color::dodgerblue	,{100,149,237} },
	{ Color::brass	,{255,87,51} },
	{ Color::grainsboro	,{220, 220, 220} }
};
typedef struct TextTexture
{
	TextTexture() {}
	TextTexture(Color, SDL_FRect, SDL_Texture*, const char*);
	Color color = Color::red;
	SDL_FRect winPos = ZERO_FRECT;
	SDL_Texture* ptrSDLTexture = nullptr;
	char text[TextContentProperties::Max_Characters_Line] = {};
	int textLength = 0;
}TextTexture;

typedef struct UserData
{
	UserData() {}
	UserData(const char*, int, int = -1);
	int ipAddress = 0;
	char nick[TextContentProperties::Max_Characters_Nick] = {};
	TextTexture nickTexture;
	int id = -1;//it indicates position in static array in datacontroller
	int nickLength = -1;
}UserData;


typedef struct  Message {
	Message() {}
	TextTexture messLineTexture[TextContentProperties::Max_Lines_In_Message] = {};
	int lines = 0;
	UserData user;
	bool isInit = false;
	bool isPositioned = false;
	int id = -1;
}Message;



