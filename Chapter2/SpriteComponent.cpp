#include "SpriteComponent.h"
#include "Actor.h"
#include "Math.h"

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_FRect r;
		// �������� ������(����)������ �ʺ�/���̸� ������
		r.w = mTexWidth * mOwner->GetScale();
		r.h = mTexHeight * mOwner->GetScale();
		// �������� ��ġ�� �߽����� �簢���� ��ġ
		r.x = mOwner->GetPosition().x - r.w / 2;
		r.y = mOwner->GetPosition().y - r.h / 2;

		// ��������Ʈ�� �׸���
		SDL_RenderTextureRotated(renderer,
			mTexture,		// �׸� �ؽ�ó
			nullptr,			// �׸� �ؽ�ó�� ����, nullptr�̸� ��ü ����
			&r,				// �׷��� �������� �簢�� ����
			-Math::ToDegrees(mOwner->GetRotation()),	// (������ ������ ��ȯ)
			nullptr,			// ȸ�� ������
			SDL_FLIP_NONE);		// �ø� �ൿ
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// �ؽ�ó�� �ʺ�� ���̸� ����
	SDL_GetTextureSize(texture, &mTexWidth, &mTexHeight);
	SDL_RenderTextureRotated();
}