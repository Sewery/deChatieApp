#pragma once
#include "..\Util\Config.h"
#define TICKRATE 128
#define SEC_IN_MS 1000
#define FIVE_SEC_IN_MS 5000
#define THREE_SEC_IN_MS 3000
namespace Commands
{
	static const char* QUIT_COMMAND = "/quit";
	static const char* DISCONNECT = "/disconnect";

	static const char* Input_Statement = "Some Text";

	static const char* Entry_Statement = "Write your username to try connect to server";
	static const char* Bad_Nick_Statement = "Bad nickname. Try again or quit";
	static const char* Not_Possible_Connect_Statement = "Can not connect to server. Try again  or quit";
	static const char* Lost_Connection_Statement = "You lost your connection. Try again or quit";
	static const char* Info_After_Connection = "You can now send your messages";

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

enum  ChatMode {
	ENTERING,
	WRITING
};

enum class Color  {
	white= 0,
	black=1,
	red ,
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
	UserData(){}
	UserData(const char*,int, int = -1);
	int ipAddress=0;
	char nick[TextContentProperties::Max_Characters_Nick] = {};
	TextTexture nickTexture;
	int id = -1;//it indicates position in static array in datacontroller
	int nickLength =-1; 
}UserData;


 typedef struct  Message{
	 Message() {}
	 TextTexture messLineTexture[TextContentProperties::Max_Lines_In_Message]={};
	 int lines = 0;
	 UserData user;
	 bool isInit = false;
	 bool isPositioned=false;
	 int id = -1;
}Message;

 namespace WindowStructure
 {
	 const float Margin_X_Screen = 40.f;
	 const float Margin_Y_Screen = 50.f;
	 const float Margin_Beetween_Messages = 10.f;
	 const float Margin_Beetween_Message_Input = 20.f;
	 const float Margin_Beetween_Information_Input = 50.f;
 }


 namespace InputProperties
 {
	 //Input box coords and data
	 static const float Space_For_Line = 35.f;
	 static const float Pos_X_Win = 40.f;
	 static const float Pos_Y_Win = 600.f;
	 static const int Font_Size = 18;
	 static const Color Text_Color = Color::grainsboro;
	 static const Color Area_Color = Color::black;
	 static const Color Background_Color = Color::grainsboro;
	 static const int Max_Characters_Lines = 100;
	 static const int Max_Lines = 4;
 }
 namespace MessageProperties
 {
	 //Message data
	 static const float Space_For_Line = 30.f;
	 static const int Font_Size = 18;
	 static const Color Font_Color = Color::black;
	 static const Color Area_Color = Color::black;
	 static const float Y_Max = InputProperties::Pos_Y_Win - WindowStructure::Margin_Beetween_Message_Input;
 }
 namespace InfoProperties
 {
	 //Information coords and data
	 static const int Font_Size = 26;
	 static const Color Text_Color = Color::white;
	 static const Color Area_Color = Color::dodgerblue;
 };
 
