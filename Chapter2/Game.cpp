#include "Game.h"
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"

// Game ������
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
	// ���͸� ���� ���̶�� ��� ���Ϳ� ���͸� �߰�
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
	// ��� ���� �������� Ȯ��
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// ������ ���ҿ� ��ȯ �� ����(���� ���� ����)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Ȱ��ȭ�� �������� Ȯ��
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// ������ ���ҿ� ��ȯ �� ����(���� ���� ����)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(class SpriteComponent* sprite)
{
	// ���ĵ� ���Ϳ��� �����ؾ� �� ��ġ�� ã�´�.
	// (�ڽź��� �׸��� �������� ū ���� ���)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// �ݺ��� ��ġ �տ� ��Ҹ� �����Ѵ�.
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
	// ~Actor �Լ��� RemoveActor�� ȣ���ϹǷ� �ٸ� ��Ÿ���� ������ �������
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

void Game::UpdateGame()
{
	// ������ ������ ���ķ� 16ms�� ����� ������ ���
	while (SDL_GetTicks() < mTicksCount + 16);

	float deltaTime = static_cast<float>((SDL_GetTicks() - mTicksCount) / 1000.0f);
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// ��� ���͸� ����
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// ��� ���� ���͸� mActors�� �̵�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// ���� ���͸� �ӽ� ���Ϳ� �߰�
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// ���� ���� ����(mActors���� �߷��� ���͵�)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOuput()
{

}

