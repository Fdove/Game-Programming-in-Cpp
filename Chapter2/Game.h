#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOuput();
	void LoadData();
	void UnloadData();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	// ������ ��� ����ž� �ϴ����� �Ǵ�
	bool mIsRunning;
	// ������ ���� ���θ� �Ǵ�
	bool mUpdatingActors;

	// Ȱ��ȭ�� ����
	std::vector<class Actor*> mActors;
	// ��� ���� ����
	std::vector<class Actor*> mPendingActors;

	// �׷��� ��� ��������Ʈ ������Ʈ
	std::vector<class SpriteComponent*> mSprites;
};