
#include "Game.h"

int main(int argc, char* args[])
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e) 
	{
		// The only exceptions we should get are from SDL
		std::cout << e.what() << '\n';
		return 1;
	}
	
	return 0;
}