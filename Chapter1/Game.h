#pragma once

#include <SDL3/SDL.h>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	virtual ~Game();

	// 윈도우가 정상적으로 만들어졌는지를 확인
	bool IsValid() const;
	// 게임이 끝나기 전까지 게임 루프를 실행
	void RunLoop();

private:
	// 게임 루프를 위한 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOuput();

	// 기본 두깨 상수
	const int thickness = 15;
	// 패들의 높이 상수
	const float paddleH = thickness * 6;

	// SDL이 생성한 윈도우
	SDL_Window* mWindow;
	// SDL 이 생성한 렌더러
	SDL_Renderer* mRenderer;
	// 윈도우가 정상적으로 만들어졌는지를 판단
	bool mIsValid;
	// 게임이 계속 실행돼야 하는지를 판단
	bool mIsRunning;

	// 패들의 위치
	Vector2 mPaddlePos;
	// 공의 위치
	Vector2 mBallPos;
	// 공의 속도
	Vector2 mBallVel;
	// 공과 패들의 y 차
	float diff;

	// 게임 틱 카운터
	Uint32 mTicksCount;
	// 패들의 위치를 제어하는 멤버 변수
	int mPaddleDir;
};