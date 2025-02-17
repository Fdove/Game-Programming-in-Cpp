#include "Ship.h"
#include "Game.h"
#include "AnimSpriteComponent.h"

Ship::Ship(Game* game) : Actor(game), mRightSpeed(0), mDownSpeed(0)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png")
	};
	asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// 속도와 델타 시간으로 위치를 갱신
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// 화면의 왼쪽 반으로 위치를 제한
	// ... SetPosition(pos)
}