#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Component.h"

class SpriteComponent : public Component
{
public:
	// (�׸��� �������� �������� �� ���ʿ��� �׸���)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTextHeight() const { return mTexHeight; }
	int GetTextWidth() const { return mTexWidth; }
protected:
	// �׸� �ؽ�ó
	SDL_Texture* mTexture;
	// ȭ�� �˰��򿡼� ����ϴ� �׸��� ����
	int mDrawOrder;
	// �ؽ�ó�� �ʺ�/����
	float mTexWidth;
	float mTexHeight;
};