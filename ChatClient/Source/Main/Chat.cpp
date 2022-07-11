#include "..\Main\Chat.h"
#include "..\ResourceController\MessageHelper.h"
#include "..\ResourceController\DataAuthorizator.h"
Chat::Chat()
{
	win = std::make_shared<Window>();

	copyCString(input, Commands::Input_Statement);
	win->loadMediaAndSetUp();
}

Chat::~Chat()
{
	
}
void Chat::entryLoop(SDL_Event & event, Client & client, bool &mainQuit)
{
	/*
	while (SDL_WaitEventTimeout(&event, SEC_IN_MS / TICKRATE) != 0)
	{
		//Handle events on queue and update input
		bool quit = false;
		bool inputSent = false;
		std::string editedInput = input;
		quit = eventController.handleEvents(editedInput, event, inputSent);
		if (quit)
		{
			mainQuit = quit;
			return;
		}
		if (strcmp(editedInput.c_str(), input) && DataCollector::checkCorrectness(editedInput, chatMode))
		{
			copyCString(input, editedInput.c_str());
		}
		win->cleanScreen();
		win->renderBackground();
		if (!inputSent)
		{
			win->renderInfo(Commands::Entry_Statement);
		}
		else
		{
			if (!client.isConnected && client.connectionRequest(getUserData(input)))
			{
				chatMode = WRITING;
				LOG("Succesfull connected to server");
				copyCString(input, "");
				mainQuit = quit;
				return;
			}
			win->renderInfo(Commands::Bad_Nick_Statement);
		}
		win->changeInput(input);
		win->renderInput();
		win->renderSDL();
	}
	*/
}
void Chat::chatLoop(SDL_Event & event, Client & client, bool &mainQuit,std::thread& receiveData)
{
	while (SDL_WaitEventTimeout(&event, SEC_IN_MS / TICKRATE) != 0)
	{
		//Handle events on queue and update input
		bool quit = false;
		bool inputSent = false;
		std::string editedInput = input;
		quit = eventController.handleEvents(editedInput, event, inputSent);
		if (quit)
		{
			mainQuit=quit;
			return;
		}
		//resizeWindow(this->ratioToBaseWidth, this->ratioToBaseHeight);

		win->cleanScreen();
		//Rendering
		win->renderBackground();
		if (chatMode == ENTERING)
		{
			if (strcmp(editedInput.c_str(), input) && DataAuthorizator::checkInputNick(editedInput))
			{
				copyCString(input, editedInput.c_str());
			}
			
			if (inputSent && !client.isConnected
				&& client.connectionRequest(getUserData(input), receiveData,currentInfo))
					
			{
				currentInfo = "";
				chatMode = WRITING;
				LOG("Succesfull connected to server");
				copyCString(input, "") ;
			}
			
		}
		else if (chatMode == WRITING)
		{
			if (strcmp(editedInput.c_str(), input) && DataAuthorizator::checkInputMessage(editedInput,user))
			{
				copyCString(input, editedInput.c_str());
			}
			if (eventController.scrolling)
			{
				win->shiftUpDownMessages(eventController.scrollVel);
			}
			if (!client.isConnected)
			{
				chatMode = ENTERING ;
				currentInfo=Commands::Lost_Connection_Statement;
			}
			if (DataCollector::getNumberOfMesseages() == 0)
			{
				currentInfo = Commands::Info_After_Connection;
			}
			if (inputSent && strlen(input) > 0)
			{
				client.sendMessage(input, user, win);
				win->cleanInput(input);

			}
			win->renderMessages();
		}
		if (chatMode == ENTERING && currentInfo.size()>0)
		{ 
			win->renderInfo(currentInfo.c_str());
		}
		win->changeInput(input);
		win->renderInput();
		win->renderSDL();
	}
	 return;
}



UserData Chat::getUserData( char* input)
{

	user = UserData(input, 0);
	return user;
}
void Chat::resizeWindow(float ratioWidth, float ratioHeight) 
{

}