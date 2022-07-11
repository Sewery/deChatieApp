#include "..\Main\Chat.h"

//static  const int SCREEN_FPS = 60;
//static  const int SCREEN_TICKS_PER_FRAME = 1000 \ SCREEN_FPS;
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		LOG_ERROR("SDL could not initialize! SDL Error:");//SDL_GetError()
		return success = false;
	}
	
	if (TTF_Init() == -1)
	{
		LOG_ERROR("SDL_ttf could not initialize! SDL_ttf Error: ");// TTF_GetError()
		return success = false;
	}
	
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		LOG_ERROR("Warning: Linear texture filtering not enabled!");
		return success = false;
	}
	
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		LOG_ERROR("SDL_image could not initialize! SDL_image Error: ");// IMG_GetError());
		return success = false;
	}
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG_ERROR("SDL_mixer could not initialize! SDL_mixer Error: ");//Mix_GetError()
		return success = false;
	}
	//Initialize ENet
	if (enet_initialize() != 0)
	{
		LOG_ERROR("An error occurred while initializing ENet!");
		return EXIT_FAILURE;
	}
	return success;

}


//Frees media and shuts down SDL
void close()
{
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
void run()
{
	//Start up SDL and create window
	init();
	atexit(enet_deinitialize);

	//Main loop flag
	bool quit = false;

	//Creating chat object
	Chat chat;
	Client client;
	SDL_Event e;

	SDL_StartTextInput();
	std::thread threadRec;
	bool startedReceiving = false;

	while (!quit)
	{
		chat.chatLoop(e, client, quit, threadRec);
	}
	threadRec.join();
	client.disconnectWithServer();
	//Disable text input
	SDL_StopTextInput();
	//Free resources and close SDL
	close();

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