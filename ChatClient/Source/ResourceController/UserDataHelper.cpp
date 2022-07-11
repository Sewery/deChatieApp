#include "..\ResourceController\UserDataHelper.h"


void UserDataHelper::givePositonForUserTexture(UserData& user)
{
	SDL_FRect& userText = user.nickTexture.winPos;
	Message lastRect = DataCollector::getNumberOfMesseages() > 1 ? DataCollector::chatContent[DataCollector::getNumberOfMesseages() - 2] : Message();

	userText = {
		WindowStructure::Margin_X_Screen,
		lastRect.messLineTexture[lastRect.lines - 1].winPos.y + MessageProperties::Space_For_Line + WindowStructure::Margin_Beetween_Messages,
		userText.w,
		userText.h
	};
}