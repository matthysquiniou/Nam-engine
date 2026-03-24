#pragma once
#include <Sprite.h>

namespace nam
{
	struct SpriteRendererComponent
	{
		Sprite* mp_sprite = nullptr;

	public:
		//Create a new Sprite in the component
		Sprite* CreateSpriteInstance();

		//Using a existing Sprite
		void SetSpriteInstance(Sprite* p_sprite);

		void SetSpriteTag(size spriteTag);

		void SetSpriteInstanceFromTag(size spriteTag);

		//Delete the Sprite member
		void DeleteSpriteInstance();
	};
}

