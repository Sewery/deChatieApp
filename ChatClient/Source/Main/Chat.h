
#include "..\Util\Timer.h"
#include "..\Input\EventContr.h"
#include "..\Gui\Window.h"
#include "..\Network\Client.h"

class Chat
{
private:
	EventContr eventController;
	ChatMode chatMode = ENTERING;

	//Window parameters
	std::shared_ptr<Window> win;
	float ratioToBaseWidth= 1.0f;
	float ratioToBaseHeight=1.0f;

	//Actual user data
	UserData user;

	//Accepted input from buffer
	char input[InputProperties::Max_Characters_Lines * InputProperties::Max_Lines];
	std::string currentInfo = Commands::Entry_Statement;
public:
	Chat();
	~Chat();
	UserData getUserData(char* input);
	void entryLoop(SDL_Event&, Client&, bool&);
	void chatLoop(SDL_Event&, Client &, bool&,std::thread&);
	void resizeWindow(float,float);
	
};
