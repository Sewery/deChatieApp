#include "..\Input\EventContr.h"

bool EventContr::handleEvents(std::string& input, SDL_Event& event, bool& inputSent)
{
	bool quit = false;
	scrolling = false;
	scrollVel = 0;
	if (event.type == SDL_QUIT)
	{
		return quit = true;
	}
	else if (event.type == SDL_MOUSEWHEEL)
	{
		//Handle scrolling thorugh messages
		scrolling = true;
		scrollVel = event.wheel.y;
	}
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			inputSent = true;
		}
		else if ( event.key.keysym.sym == SDLK_BACKSPACE 
			&& input.length() > 0)
		{
			//lop off character
			input.pop_back();
		}
		//Handle copy
		else if ( event.key.keysym.sym == SDLK_c 
			&& ( KMOD_CTRL & SDL_GetModState() ) )
		{
			SDL_SetClipboardText(input.c_str());
		}
		//Handle paste
		else if ( event.key.keysym.sym == SDLK_v
			&& ( KMOD_CTRL & SDL_GetModState() ) )
		{
			input = SDL_GetClipboardText();
		}
		
	}
	//Special text input event
	else if ( event.type == SDL_TEXTINPUT )
	{
		//Not copy or pasting
		if ( !( KMOD_CTRL & SDL_GetModState() 
			&& ( event.text.text[0] == 'c' 
				|| event.text.text[0] == 'C' 
				|| event.text.text[0] == 'v' 
				|| event.text.text[0] == 'V' ) ) )
		{
			//Append character
			input += event.text.text;
		}
	}
	scrollVel *= Acceleration_Factor;
	return quit=false;
}