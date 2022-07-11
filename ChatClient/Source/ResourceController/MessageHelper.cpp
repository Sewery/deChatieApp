#include "..\ResourceController\MessageHelper.h"

Message MessageHelper::createMessage(char* input, UserData user,   WinCompsData * windata)
{
	std::string inputHelper= std::string(input);
	std::string userHelper = std::string(user.nick) + ": ";
	Message mess;
	int numberOflines = ((strlen(input)+ strlen(user.nick)) / (TextContentProperties::Max_Characters_Line )) + 1;
	user.nickTexture = TextTexture(
		MessageProperties::Font_Color,
		ZERO_FRECT,
		nullptr,
		userHelper.c_str()
	);
	for (int i = 0; i < numberOflines; i++)
	{
		mess.messLineTexture[i]= TextTexture(
			MessageProperties::Font_Color,
			ZERO_FRECT,
			nullptr,
			inputHelper.substr(i * TextContentProperties::Max_Characters_Line, TextContentProperties::Max_Characters_Line).c_str()
		);
	}
	mess.lines = numberOflines;
	mess.user = user;
	mess.isInit = true;
	return mess;
}

void MessageHelper::givePositionForNewMessage(Message& mess )
{
	SDL_FRect& userText = mess.user.nickTexture.winPos;
	mess.messLineTexture[0].winPos = {
		WindowStructure::Margin_X_Screen + userText.w,
		userText.y,
		mess.messLineTexture[0].winPos.w,
		mess.messLineTexture[0].winPos.h
	};

	int i = 1;
	while (i< TextContentProperties::Max_Lines_In_Message &&  strlen(mess.messLineTexture[i].text) > 0)
	{
		mess.messLineTexture[i].winPos.x = WindowStructure::Margin_X_Screen;
		mess.messLineTexture[i].winPos.y = MessageProperties::Space_For_Line + mess.messLineTexture[i - 1].winPos.y;
		i++;
	}
	
}