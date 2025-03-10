// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include "Component.h"
#include "SDL3/SDL.h"

class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	float GetTexHeight() const { return mTexHeight; }
	float GetTexWidth() const { return mTexWidth; }
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	float mTexWidth;
	float mTexHeight;
};