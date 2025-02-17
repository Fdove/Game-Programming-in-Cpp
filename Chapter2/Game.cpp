#include "Game.h"
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"

// Game 생성자
Game::Game() : mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true), mUpdatingActors(false) {}

bool Game::Initialize()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)",
		1024,
		768,
		0
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		NULL
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	LoadData();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOuput();
	}
}

void Game::Shutdown()
{
	UnloadData();
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	// 액터를 갱신 중이라면 대기 벡터에 액터를 추가
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}
void Game::RemoveActor(class Actor* actor)
{
	// 대기 중인 액터인지 확인
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// 마지막 원소와 교환 후 제거(제거 복사 방지)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// 활성화된 액터인지 확인
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// 마지막 원소와 교환 후 제거(제거 복사 방지)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(class SpriteComponent* sprite)
{
	// 정렬된 벡터에서 삽입해야 할 위치를 찾는다.
	// (자신보다 그리기 순서값이 큰 최초 요소)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// 반복자 위치 앞에 요소를 삽입한다.
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(class SpriteComponent* sprite)
{

}

void Game::ProcessInput()
{

}

void Game::UnloadData()
{
	// ~Actor 함수가 RemoveActor를 호출하므로 다른 스타일의 루프를 사용하자
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

void Game::UpdateGame()
{
	// 마지막 프레임 이후로 16ms가 경과할 때까지 대기
	while (SDL_GetTicks() < mTicksCount + 16);

	float deltaTime = static_cast<float>((SDL_GetTicks() - mTicksCount) / 1000.0f);
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// 모든 액터를 갱신
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// 대기 중인 액터를 mActors로 이동
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// 죽은 액터를 임시 벡터에 추가
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// 죽은 액터 제거(mActors에서 추려낸 액터들)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOuput()
{

}

