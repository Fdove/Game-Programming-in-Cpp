#include "Game.h"

// Game 생성자
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
		"Game Programming in C++ (Chapter 1)",	// 윈도우 제목
		// 100,	// 윈도우의 좌측 상단 x좌표
		// 100,	// 윈도우의 좌측 상단 y좌표
		1024,	// 윈도우 너비
		768,		// 윈도우 높이
		0			// 플래스 (0은 어떤 플래스도 설정되지 않음을 의미)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,	// 렌더링을 위해 생성한 윈도우
		NULL			// 일반적으로 -1 -> NULL
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return;
	}

	mIsValid = true;
}

// Game 소멸자
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
	// 큐에 여전히 이벤트가 남아 있는 동안
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_EVENT_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// 키보드의 상태 얻기
	const Uint8* state = (Uint8*)SDL_GetKeyboardState(NULL);
	// 이스케이프 키를 눌렀다면 루프 종료
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	// 패들의 위치를 제어하는 멤버 변수 갱신
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
	// 마지막 프레임 이후로 16ms가 경과할 때까지 대기
	while (SDL_GetTicks() < mTicksCount + 16);

	// 델타 시간은 마지막 프레임의 틱값과 현재 프레임 틱값의 차
	// (초 단위로 변환)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// 다음 프레임을 위해 틱값을 갱신
	mTicksCount = SDL_GetTicks();

	// 최대 델타 시간값으로 고정
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// 주석: 델타 시간의 함수로 게임 세계의 오브젝트를 갱신!
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.f * deltaTime;
		// 패들이 화면 영역을 벗어나는지를 검증하자!
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

	// 위쪽 벽 충돌 감지
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// 아래쪽 벽 충돌 감지
	if (mBallPos.y >= 768 - thickness && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
	// 오른쪽 벽 충돌 감지
	if (mBallPos.x >= 1024 - thickness && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1;
	}

	// 왼쪽 벽 충돌 시 다시 가운데로 배치
	if (mBallPos.x <= thickness && mBallVel.x < 0.0f)
	{
		mBallPos = { 1024 / 2, 768 / 2 };
	}

	diff = mPaddlePos.y - mBallPos.y;
	diff *= (diff < 0 ? -1 : 1);
	if (
		// y 차가 충분히 작고
		diff <= paddleH / 2.0f &&
		// 공이 올바른 x 값을 갖고 있고
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// 공이 왼쪽으로 이동하고 있다면
		mBallVel.x < 0.0f
		)
	{
		mBallVel.x *= -1.0f;
	}
}

void Game::GenerateOuput()
{
	// 배경 그리기
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G
		255,	// B
		255	// A
	);
	SDL_RenderClear(mRenderer);

	// 색상을 녹색으로 변경
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	// 위, 아래, 오른쪽 벽 그리기
	SDL_FRect topRect{ 0, 0, 1024, thickness };
	SDL_RenderFillRect(mRenderer, &topRect);
	SDL_FRect bottomRect{ 0, 768 - thickness, 1024, thickness };
	SDL_RenderFillRect(mRenderer, &bottomRect);
	SDL_FRect rightRect{ 1024 - thickness, 0, thickness, 768 };
	SDL_RenderFillRect(mRenderer, &rightRect);

	// 색상을 흰색으로 변경
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	// 패들과 공 그리기
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

	// 화면 출력
	SDL_RenderPresent(mRenderer);
}