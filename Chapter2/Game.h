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
	// 게임이 계속 실행돼야 하는지를 판단
	bool mIsRunning;
	// 액터의 갱신 여부를 판단
	bool mUpdatingActors;

	// 활성화된 액터
	std::vector<class Actor*> mActors;
	// 대기 중인 액터
	std::vector<class Actor*> mPendingActors;

	// 그려질 모든 스프라이트 컴포넌트
	std::vector<class SpriteComponent*> mSprites;
};