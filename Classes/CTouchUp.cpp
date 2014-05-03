#include "CTouchUp.h"
#include "CalclateMcr.h"
#include "CPlayer.h"

USING_NS_CC;

// �R���X�g���N�^
CTouchUp::CTouchUp()
{

}

// �f�X�g���N�^
CTouchUp::~CTouchUp()
{

}

// �Փˎ��Ɏ��s�����֐�
void CTouchUp::CollisionFunction(IPlayerStateChange* playerStateChanger)
{
	playerStateChanger->AddTouch(5);
	_hitDeleteFlag = true;
}

//**********************************************************
// �N���G�C�g�֐�
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