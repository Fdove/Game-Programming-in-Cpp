#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Component.h"

class SpriteComponent : public Component
{
public:
	// (그리기 순서값이 낮을수록 더 뒤쪽에서 그린다)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTextHeight() const { return mTexHeight; }
	int GetTextWidth() const { return mTexWidth; }
protected:
	// 그릴 텍스처
	SDL_Texture* mTexture;
	// 화가 알고리즘에서 사용하는 그리기 순서
	int mDrawOrder;
	// 텍스처의 너비/높이
	float mTexWidth;
	float mTexHeight;
};