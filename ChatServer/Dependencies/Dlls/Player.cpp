#include "Player.h"

Player::Player( const std::string& textureFile, SDL_Renderer* ren, SDL_Rect pos, SDL_Rect box) :LightEntity(textureFile,ren, pos,box) {
	

}
Player::~Player()
{
	close();
}
bool Player::loadMedia()
{

	bool success = true;
	if (!eTextures->loadFile())
	{
		std::cerr << "Failed to load walking animation texture of player!\n";
		return success = false;
	}
	for (int i = 0; i < 4; i++)
	{
		positionMovement[Movement::IDLE].push_back({ characterBoxSize * i,characterBoxSize * 7,characterBoxSize ,characterBoxSize });
	}
	for (int i = 0; i < 6; i++)
	{
		positionMovement[Movement::WALK].push_back({ characterBoxSize * i,characterBoxSize * 10,characterBoxSize ,characterBoxSize });
	}
	for (int i = 0; i < 6; i++)
	{
		positionMovement[Movement::CLIMB].push_back({ characterBoxSize * i,characterBoxSize * 3,characterBoxSize ,characterBoxSize });
	}
	for (int i = 0; i < 6; i++)
	{
		positionMovement[Movement::ATTACK].push_back({ characterBoxSize * i,characterBoxSize * 0,characterBoxSize ,characterBoxSize });
	}
	for (int i = 0; i < 7; i++)
	{
		positionMovement[Movement::JUMP].push_back({ characterBoxSize * i,characterBoxSize * 8,characterBoxSize ,characterBoxSize });
	}
	positionMovement[Movement::FALL].push_back({ characterBoxSize * 1,characterBoxSize * 4,characterBoxSize ,characterBoxSize });
	return true;
}
bool isLadder() {
	return true;
}

void  Player::update(std::map<int, bool> & keyboardState,bool & mouseClick,const int& screenHeight, const int& screenWidth,std::vector<CollisionBox*>& vecBox)
{

	int scan = 0;
	int PosX = eTextures->getPosX();
	int PosY = eTextures->getPosY();
	std::pair<int, int>  change={0,0};
	
	//std::cout << change.second << '\n';
	if( currentMovement!=JUMP)
	{
		currentSpeed = ceil(velocity.at(FALL) * (currentFrame + 1.0) / 10.0);
		change = eCollisionBox->move(vecBox, 0, currentSpeed, screenWidth, screenHeight, 2);
		if (change.second != 0)
		{
			if (currentMovement != Movement::FALL)
				currentFrame = -1;
			currentMovement = Movement::FALL;
			currentFrame += 1;
		}
		else
		{
			if (currentMovement == Movement::FALL)
				currentMovement = Movement::IDLE;

		}
	}
	
	if (currentMovement != Movement::FALL &&(mouseClick  || ( mouseClick==0 && currentMovement== Movement::ATTACK && currentFrame!=0)))
	{
		if (currentMovement != Movement::ATTACK)
			currentFrame = -1;
		scan |= 1;
		currentMovement = Movement::ATTACK;
		(currentFrame += 1) %= (positionMovement[Movement::ATTACK].size() * delayRender.at(ATTACK));
	}
	else if (keyboardState[SDLK_UP] && isLadder()) {
		if (mouseClick == 0 && ((currentMovement != Movement::ATTACK) || (currentMovement == Movement::ATTACK && currentFrame == 0)))
		{
			if (currentMovement != Movement::CLIMB)
				currentFrame = -1;
			std::pair<int, int> ch = eCollisionBox->move(vecBox, 0, -velocity.at(CLIMB), screenWidth, screenHeight, 2);
			change = { ch.first + change.first, ch.second + change.second };
			scan |= SDL_SCANCODE_UP;
			currentMovement = Movement::CLIMB;
		}
		(currentFrame+=1)%= (positionMovement[Movement::CLIMB].size() * delayRender.at(CLIMB));
	}
	else if (keyboardState[SDLK_DOWN] && isLadder()) {
		if (mouseClick == 0 && ((currentMovement != Movement::ATTACK) || (currentMovement == Movement::ATTACK && currentFrame == 0)))
		{
			if (currentMovement != Movement::CLIMB)
				currentFrame = -1;
			std::pair<int, int> ch = eCollisionBox->move(vecBox, 0, velocity.at(CLIMB), screenWidth, screenHeight, 2);
			change = { ch.first + change.first, ch.second + change.second };
			scan |= SDL_SCANCODE_DOWN;
			currentMovement = Movement::CLIMB;
		}
		(currentFrame += 1) %= (positionMovement[Movement::CLIMB].size() * delayRender.at(CLIMB));
	}
	else if (keyboardState[SDLK_LEFT])
	{
		std::cout << currentFrame << "@@\n";
		if (mouseClick == 0 && ((currentMovement != Movement::ATTACK) || (currentMovement == Movement::ATTACK && currentFrame == 0)))
		{
			if (currentMovement != Movement::WALK && currentMovement != Movement::JUMP)
				currentFrame = -1;
			
			if (SDL_FLIP_NONE == eTextures->flipType)
			{
				eTextures->flipType = SDL_FLIP_HORIZONTAL;
				auto rect = eCollisionBox->getCollBox();
				eCollisionBox->setCollBox({ rect.x +characterBoxSize - rect.w - 14, rect.y ,rect.w,rect.h});
			}
			std::pair<int, int> ch = eCollisionBox->move(vecBox, -velocity.at(WALK), 0, screenWidth, screenHeight, 1);
			change = { ch.first + change.first, ch.second + change.second };
			scan |= SDL_SCANCODE_LEFT;
			if (currentMovement != Movement::JUMP)
				currentMovement = Movement::WALK;
		}
		if (currentMovement == Movement::JUMP)
			goto jumping;
		(currentFrame += 1) %= (positionMovement[Movement::WALK].size()* delayRender.at(WALK));
	}
	else if (keyboardState[SDLK_RIGHT])
	{
		if (mouseClick == 0 && ((currentMovement != Movement::ATTACK) || (currentMovement == Movement::ATTACK && currentFrame == 0)))
		{
			if (currentMovement != Movement::WALK && currentMovement!= Movement::JUMP)
				currentFrame = -1;
			
			if (SDL_FLIP_HORIZONTAL == eTextures->flipType)
			{
				eTextures->flipType = SDL_FLIP_NONE;
				auto rect = eCollisionBox->getCollBox();
				eCollisionBox->setCollBox({ rect.x-characterBoxSize + rect.w +14 ,rect.y,rect.w,rect.h });
			}
			std::pair<int, int> ch = eCollisionBox->move(vecBox, velocity.at(WALK), 0, screenWidth, screenHeight, 0);
			change = { ch.first + change.first, ch.second + change.second };
			scan |= SDL_SCANCODE_RIGHT;
			if (currentMovement != Movement::JUMP)
				currentMovement = Movement::WALK;
		
		}
		if (currentMovement == Movement::JUMP)
			goto jumping;
		(currentFrame += 1) %= (positionMovement[Movement::WALK].size()* delayRender.at(WALK));
	}
	 if (keyboardState[SDLK_SPACE] && currentMovement!=FALL)
	{
		if (mouseClick == 0 && ((currentMovement != Movement::ATTACK) || (currentMovement == Movement::ATTACK && currentFrame == 0)))
		{
			if (currentMovement != Movement::JUMP)
				currentFrame = -1;
			scan |= SDL_SCANCODE_RIGHT;
			currentMovement = Movement::JUMP;
		}
		jumping:
		std::pair<int, int> ch={0,0};
		if(currentFrame+2>(positionMovement[Movement::JUMP].size() * delayRender.at(JUMP))/2)
			 ch = eCollisionBox->move(vecBox, 0, velocity.at(JUMP), screenWidth, screenHeight, 2);
		else
			ch = eCollisionBox->move(vecBox,  0, -velocity.at(JUMP) , screenWidth, screenHeight, 2);
		change = { ch.first + change.first, ch.second + change.second };
		(currentFrame += 1) %= (positionMovement[Movement::JUMP].size() * delayRender.at(JUMP));
	}
	if( scan==0 && currentMovement!=FALL)
	{
		if (mouseClick == 0 && ((currentMovement != Movement::ATTACK) || (currentMovement == Movement::ATTACK && currentFrame == 0)))
		{
			if (currentMovement != Movement::IDLE)
				currentFrame = -1;
			currentMovement = Movement::IDLE;
		}
		(currentFrame += 1) %= (positionMovement[Movement::IDLE].size() * delayRender.at(IDLE));
	
		
	}
	eTextures->setPositionAndSize({ PosX+change.first,PosY+ change.second,eTextures->getWidth() ,eTextures->getHeight()});
}
void Player::render()
{
	if(currentMovement==FALL)
		eTextures->render(eTextures->getPosX(), eTextures->getPosY(), positionMovement[currentMovement][0], 0.0, nullptr, eTextures->flipType);
	else
		eTextures->render(eTextures->getPosX(), eTextures->getPosY(), positionMovement[currentMovement][currentFrame/ delayRender.at(currentMovement)], 0.0, nullptr, eTextures->flipType);

}
void Player::render(SDL_Rect)
{
	eTextures->render(eTextures->getPosX(), eTextures->getPosY(), positionMovement[currentMovement][0 / delayRender.at(currentMovement)], 0.0, nullptr, eTextures->flipType);

}
void Player::close()
{
	eTextures->free();
}