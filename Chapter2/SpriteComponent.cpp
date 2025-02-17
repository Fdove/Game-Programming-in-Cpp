#include "SpriteComponent.h"
#include "Actor.h"
#include "Math.h"

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_FRect r;
		// 소유자의 스케일(배율)값으로 너비/높이를 스케일
		r.w = mTexWidth * mOwner->GetScale();
		r.h = mTexHeight * mOwner->GetScale();
		// 소유자의 위치를 중심으로 사각형을 배치
		r.x = mOwner->GetPosition().x - r.w / 2;
		r.y = mOwner->GetPosition().y - r.h / 2;

		// 스프라이트를 그린다
		SDL_RenderTextureRotated(renderer,
			mTexture,		// 그릴 텍스처
			nullptr,			// 그릴 텍스처의 영역, nullptr이면 전체 영역
			&r,				// 그려질 목적지의 사각형 영역
			-Math::ToDegrees(mOwner->GetRotation()),	// (라디안을 각도로 변환)
			nullptr,			// 회전 기준점
			SDL_FLIP_NONE);		// 플립 행동
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// 텍스처의 너비와 높이를 얻자
	SDL_GetTextureSize(texture, &mTexWidth, &mTexHeight);
	SDL_RenderTextureRotated();
}