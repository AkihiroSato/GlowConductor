#include "PlayerFollower.h"
USING_NS_CC;

PlayerFollower* PlayerFollower::createWithTexture(Texture2D* texture)
{
	PlayerFollower *sprite = new PlayerFollower();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		sprite->runAction(Sequence::createWithTwoActions(
			FadeOut::create(0.5f),
			RemoveSelf::create()));
		sprite->Init();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}