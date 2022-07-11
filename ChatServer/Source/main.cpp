
#include "Server.h"
bool init()
{
	//Initialization flag
	bool success = true;
	
	//Initialize ENet
	if (enet_initialize() != 0)
	{
		LOG_ERROR( "An error occurred while initializing ENet!\n");
		return success = false;
	}
	return success;
}
void commandsController(bool& quit)
{
	std::string input;
	while (!quit)
	{
		std::cin >> input;
		if (input == Commands::QUIT_COMMAND)
		{
			quit = true;
		}
		input="";
	}
	
	
}
void run()
{
	//Start up SDL and create window
	if (!init())
	{
		LOG_ERROR("Failed to initialize!\n");
		return;
	}
	atexit(enet_deinitialize);
	LOG("If you want to quit type : .quit");
	//Main loop flag
	bool quit = false;

	Server server;
	
	if (server.init())
	{
		LOG_ERROR(" An unexpected error occurred at initialzation of server\n");
		return ;
	}
	std::thread threadControllerInput(commandsController,std::ref(quit));
	while (!quit)
	{
		server.serverEventsHandling();
	}
	threadControllerInput.join();
	server.closeServer();
}



int main(int argc, char* args[])
{
	try {
		run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}