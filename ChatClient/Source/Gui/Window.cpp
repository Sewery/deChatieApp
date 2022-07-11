#include "..\Gui\Window.h"
#include "..\Texture\TextTextureHelper.h"
Window::Window():WinCompsContr()
{
	initWindow();
}
Window::~Window()
{
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pRenderer = nullptr;
	pWindow = nullptr;
}
bool Window::initWindow()
{
	bool success = true;
	pWindow = SDL_CreateWindow(Title_Of_Window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//resizeWindow(this->ratioToBaseWidth, this->ratioToBaseHeight);
	if (pWindow == nullptr)
	{
		LOG_ERROR("Window could not be created! SDL Error: " << SDL_GetError());
		return success = false;
	}
	//Create vsynced renderer for window
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (pRenderer == nullptr)
	{
		LOG_ERROR("Renderer could not be created! SDL Error:" << SDL_GetError() );
		return success = false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0xFF);
	return success;
}
void Window::loadMediaAndSetUp()
{
	setUpInfoTextTexture();
	setUpInputTextTexture();
	loadMediaInput();
	loadMediaInfo();
	loadMediaServer();

}
void Window::renderMessages()
{
	TextTextureHelper::loadMediaMessagesFromServer(MessageProperties::Font_Size, pRenderer, this);
	TextTextureHelper::renderMessagesFromServer(pRenderer, InputProperties::Pos_Y_Win- WindowStructure::Margin_Beetween_Message_Input);
}
void Window::renderInput()
{
	
	if (strlen(inputTextTexture[0].text) > 0)
	{
		loadMediaInput();
		SDL_FRect rectAreaPos = {
			InputProperties::Pos_X_Win,
			InputProperties::Pos_Y_Win,
			currWindowWidth - 2* WindowStructure::Margin_Y_Screen,
			InputProperties::Max_Lines * InputProperties::Space_For_Line
		};
		TextTextureHelper::createRectAndRender(true, rectAreaPos, pRenderer, InputProperties::Area_Color, 10);
		for (auto& texture : inputTextTexture)
		{
			if (strlen(texture.text) > 0)
			{
				TextTextureHelper::render(texture, pRenderer);
			}
			
		}
		
	}
	
}
void Window::renderInfo(const char * info)
{
	TextTextureHelper::createRectAndRender(true, infoTextTexture.at(iTextTPos.at(info)).winPos, pRenderer, InputProperties::Area_Color, 15);
	TextTextureHelper::render(infoTextTexture.at(iTextTPos.at(info)), pRenderer);
}
void Window::renderBackground()
{
	//Main background:
	TextTextureHelper::createRectAndRender(true, {
			0.f,
			0.f,
			(float)currWindowWidth,
			(float)currWindowHeight,
		},
		pRenderer,
		Main_Background_Color,0);
	//Input background
	TextTextureHelper::createRectAndRender(true, {
		0.f,
		0.f,
		(float)currWindowWidth,
		(float)InputProperties::Pos_Y_Win - (  WindowStructure::Margin_Beetween_Message_Input)
		},
		pRenderer,
		InputProperties::Background_Color, 0);
}

void Window::cleanScreen()
{
	//Clear screen
	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRenderer);
}
void Window::cleanInput( char * input)
{
	copyCString(input, "");
	for (int i = 0; i < InputProperties::Max_Lines; i++)
	{
		copyCString(inputTextTexture[i].text, "");
	}
}
void Window::changeInput(const char* str)
{
	int lines = (strlen(str) / InputProperties::Max_Characters_Lines) + 1;
	//if (strlen(str) > TextContentProperties::Input_Max_Character_Lines * TextContentProperties::Input_Max_Lines);
	std::string textHelper = std::string(str);
	for (int i = 0; i < lines; i++)
	{
		copyCString(inputTextTexture[i].text,
		textHelper.substr(i * InputProperties::Max_Characters_Lines, InputProperties::Max_Characters_Lines).c_str());
	}
}