
#include "LightEntity.h"

class Player :public LightEntity {
private:
	enum  Movement
	{
		WALK = 0, IDLE, ATTACK, JUMP, CLIMB,FALL
	};
	//Animations and movement
	std::map<Movement,std::vector<SDL_Rect>> positionMovement;
	const std::map<Movement, int> velocity = { {WALK,5},{CLIMB,2},{JUMP,1},{FALL,3} };
	const std::map<Movement, int> delayRender = { {WALK,6 },{IDLE,11 }, { CLIMB,10}, {ATTACK,8},{JUMP,5} };
	Movement currentMovement = IDLE;
	const float accerlationFalling = 1.6f;
	float currentSpeed = 0;
	//Sounds from player
	//std::vector<Mix_Music*> pMusic;
	
	const int characterBoxSize = 48;
	int currentFrame=0;
public:
	Player(const std::string& , SDL_Renderer*,SDL_Rect, SDL_Rect);
	~Player();
	bool loadMedia() override;
	void update(std::map<int,bool>&,bool&, const int&, const int&,std::vector<CollisionBox*>&) ;
	void render() override;
	void render(SDL_Rect) override;
	void close() override;
};