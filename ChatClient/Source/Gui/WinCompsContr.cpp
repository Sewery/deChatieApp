#include "..\Gui\WinCompsContr.h"
#include "..\Texture\TextTextureHelper.h"

WinCompsContr::WinCompsContr() :WinCompsData()
{

}
void WinCompsContr::shiftUpDownMessages(int y)
{
	for (auto& mess : dataCollector.chatContent)
	{
		mess.user.nickTexture.winPos.y += y;
		for (auto& line : mess.messLineTexture)
		{
			line.winPos.y += y;
		}
		
	}
}


void WinCompsContr::setUpInfoTextTexture()
{
	infoTextTexture.at(iTextTPos.at(Commands::Entry_Statement))=(TextTexture(
		InfoProperties::Text_Color,
		ZERO_FRECT,
		nullptr,
		Commands::Entry_Statement
		));
	
	infoTextTexture.at(iTextTPos.at(Commands::Bad_Nick_Statement))=(TextTexture(
		InfoProperties::Text_Color,
		ZERO_FRECT,
		nullptr,
		Commands::Bad_Nick_Statement
	));
	
	infoTextTexture.at(iTextTPos.at(Commands::Lost_Connection_Statement))=(TextTexture(
		InfoProperties::Text_Color,
		ZERO_FRECT,
		nullptr,
		Commands::Lost_Connection_Statement
	));
	infoTextTexture.at(iTextTPos.at(Commands::Info_After_Connection)) = (TextTexture(
		InfoProperties::Text_Color,
		ZERO_FRECT,
		nullptr,
		Commands::Info_After_Connection
	));
	infoTextTexture.at(iTextTPos.at(Commands::Not_Possible_Connect_Statement)) = (TextTexture(
		InfoProperties::Text_Color,
		ZERO_FRECT,
		nullptr,
		Commands::Not_Possible_Connect_Statement
	));

}

void WinCompsContr::setUpInputTextTexture()
{
	inputTextTexture[0] = TextTexture(InputProperties::Text_Color, {
			   InputProperties::Pos_X_Win,
			   InputProperties::Pos_Y_Win,
			   0.f,
			   0.f
		},
		nullptr,
		Commands::Input_Statement
	);
	for (int i=1;i< InputProperties::Max_Lines;i++)
	{
		inputTextTexture[i]= TextTexture(InputProperties::Text_Color, {
			   InputProperties::Pos_X_Win,
			  InputProperties::Space_For_Line*i + InputProperties::Pos_Y_Win,
			   0.f,
			   0.f
			},
			nullptr,
			""
		);
	}
	
}

void WinCompsContr::messageViewRegulation()
{
	Message& lastMess = DataCollector::chatContent[(DataCollector::getNumberOfMesseages() - 1)];
	if (lastMess.messLineTexture[lastMess.lines - 1].winPos.y > MessageProperties::Y_Max- MessageProperties::Space_For_Line)
	{
		int diff = lastMess.messLineTexture[lastMess.lines - 1].winPos.y - MessageProperties::Y_Max;
		for (auto& message : DataCollector::chatContent)
		{
			if (message.isInit)
			{
				message.user.nickTexture.winPos.y -= diff;
				for (auto& line : message.messLineTexture)
				{
					line.winPos.y -= diff;
				}
			}
		}
	}
}

void WinCompsContr::loadMediaInfo()
{
	for (auto& info : infoTextTexture)
	{
		TextTextureHelper::loadMedia(InfoProperties::Font_Size, info, pRenderer);
		TextTextureHelper::centerOnScreenTexture(currWindowWidth, currWindowHeight, info);
	}
	
	
}
void WinCompsContr::loadMediaInput()
{
	for (auto& texture : inputTextTexture)
	{
		if (strlen(texture.text))
		{
			TextTextureHelper::loadMedia(InputProperties::Font_Size, texture, pRenderer);
		}
		
	}
	
}
void WinCompsContr::loadMediaServer()
{
	TextTextureHelper::loadMediaMessagesFromServer(MessageProperties::Font_Size,pRenderer,this);
}
