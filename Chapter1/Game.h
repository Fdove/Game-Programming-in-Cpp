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
	Vector2 mPaddlePos;
	// ���� ��ġ
	Vector2 mBallPos;
	// ���� �ӵ�
	Vector2 mBallVel;
	// ���� �е��� y ��
	float diff;

	// ���� ƽ ī����
	Uint32 mTicksCount;
	// �е��� ��ġ�� �����ϴ� ��� ����
	int mPaddleDir;
};