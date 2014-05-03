#include "CTouchUp.h"
#include "CalclateMcr.h"
#include "CPlayer.h"

USING_NS_CC;

// コンストラクタ
CTouchUp::CTouchUp()
{

}

// デストラクタ
CTouchUp::~CTouchUp()
{

}

// 衝突時に実行される関数
void CTouchUp::CollisionFunction(IPlayerStateChange* playerStateChanger)
{
	playerStateChanger->AddTouch(5);
	_hitDeleteFlag = true;
}

//**********************************************************
// クリエイト関数
//**********************************************************
CTouchUp* CTouchUp::createWithTexture(Texture2D *texture)
{
	CTouchUp *sprite = new CTouchUp();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}