#include "Game.h"

// Game ������
Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsValid(false), mIsRunning(true),
mPaddlePos{ static_cast<float>(thickness), 768 / 2 },
mBallPos{ 1024 / 2, 768 / 2 }, mBallVel{ -200.0f, 235.0f }, diff(0),
mTicksCount(0), mPaddleDir(0)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)",	// ������ ����
		// 100,	// �������� ���� ��� x��ǥ
		// 100,	// �������� ���� ��� y��ǥ
		1024,	// ������ �ʺ�
		768,		// ������ ����
		0			// �÷��� (0�� � �÷����� �������� ������ �ǹ�)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,	// �������� ���� ������ ������
		NULL			// �Ϲ������� -1 -> NULL
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return;
	}

	mIsValid = true;
}

// Game �Ҹ���
Game::~Game()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

bool Game::IsValid() const
{
	return mIsValid;
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

void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	// ť�� ������ �̺�Ʈ�� ���� �ִ� ����
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_EVENT_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// Ű������ ���� ���
	const Uint8* state = (Uint8*)SDL_GetKeyboardState(NULL);
	// �̽������� Ű�� �����ٸ� ���� ����
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	// �е��� ��ġ�� �����ϴ� ��� ���� ����
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}


void Game::UpdateGame()
{
	// ������ ������ ���ķ� 16ms�� ����� ������ ���
	while (SDL_GetTicks() < mTicksCount + 16);

	// ��Ÿ �ð��� ������ �������� ƽ���� ���� ������ ƽ���� ��
	// (�� ������ ��ȯ)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// ���� �������� ���� ƽ���� ����
	mTicksCount = SDL_GetTicks();

	// �ִ� ��Ÿ �ð������� ����
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// �ּ�: ��Ÿ �ð��� �Լ��� ���� ������ ������Ʈ�� ����!
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.f * deltaTime;
		// �е��� ȭ�� ������ ��������� ��������!
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// ���� �� �浹 ����
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// �Ʒ��� �� �浹 ����
	if (mBallPos.y >= 768 - thickness && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
	// ������ �� �浹 ����
	if (mBallPos.x >= 1024 - thickness && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1;
	}

	// ���� �� �浹 �� �ٽ� ����� ��ġ
	if (mBallPos.x <= thickness && mBallVel.x < 0.0f)
	{
		mBallPos = { 1024 / 2, 768 / 2 };
	}

	diff = mPaddlePos.y - mBallPos.y;
	diff *= (diff < 0 ? -1 : 1);
	if (
		// y ���� ����� �۰�
		diff <= paddleH / 2.0f &&
		// ���� �ùٸ� x ���� ���� �ְ�
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// ���� �������� �̵��ϰ� �ִٸ�
		mBallVel.x < 0.0f
		)
	{
		mBallVel.x *= -1.0f;
	}
}

void Game::GenerateOuput()
{
	// ��� �׸���
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G
		255,	// B
		255	// A
	);
	SDL_RenderClear(mRenderer);

	// ������ ������� ����
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	// ��, �Ʒ�, ������ �� �׸���
	SDL_FRect topRect{ 0, 0, 1024, thickness };
	SDL_RenderFillRect(mRenderer, &topRect);
	SDL_FRect bottomRect{ 0, 768 - thickness, 1024, thickness };
	SDL_RenderFillRect(mRenderer, &bottomRect);
	SDL_FRect rightRect{ 1024 - thickness, 0, thickness, 768 };
	SDL_RenderFillRect(mRenderer, &rightRect);

	// ������ ������� ����
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	// �е�� �� �׸���
	SDL_FRect paddleRect{
		mPaddlePos.x - thickness / 2,
		mPaddlePos.y - paddleH / 2.0f,
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddleRect);

	SDL_FRect ballRect{
		mBallPos.x - thickness / 2,
		mBallPos.y - thickness / 2,
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ballRect);

	// ȭ�� ���
	SDL_RenderPresent(mRenderer);
}