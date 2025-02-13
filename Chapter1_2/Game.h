#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <cstdlib>

struct Vector2
{
	float x;
	float y;
};

const size_t BALL_COUNT = 3;
struct Ball
{
	Vector2 pos;
	Vector2 vel;
	SDL_Color color;
};

class Game
{
public:
	Game();
	virtual ~Game();

	// �����찡 ���������� ������������� Ȯ��
	bool IsValid() const;
	// ������ ������ ������ ���� ������ ����
	void RunLoop();

private:
	// ���� ������ ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOuput();

	// �⺻ �α� ���
	const int thickness = 15;
	// �е��� ���� ���
	const float paddleH = thickness * 6;

	// SDL�� ������ ������
	SDL_Window* mWindow;
	// SDL �� ������ ������
	SDL_Renderer* mRenderer;
	// �����찡 ���������� ������������� �Ǵ�
	bool mIsValid;
	// ������ ��� ����ž� �ϴ����� �Ǵ�
	bool mIsRunning;

	// �е��� ��ġ
	Vector2 mPaddlePos1;
	Vector2 mPaddlePos2;
	// ����
	std::vector<Ball> mBalls;
	// ���� �е��� y ��
	float diff;

	// ���� ƽ ī����
	Uint32 mTicksCount;
	// �е��� ��ġ�� �����ϴ� ��� ����
	int mPaddleDir1;
	int mPaddleDir2;
};