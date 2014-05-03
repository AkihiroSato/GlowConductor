#include "CDark.h"
#include "CalclateMcr.h"
#include "CPlayer.h"
#include "CustomParticle.h"

USING_NS_CC;

// �R���X�g���N�^
CDark::CDark()
{

}

CDark::CDark(float radius, float x, float y) : CObject(radius, x, y)
{

}

// �f�X�g���N�^
CDark::~CDark()
{

}

// �Փˎ��Ɏ��s�����֐�
void CDark::CollisionFunction(IPlayerStateChange* playerStateChanger)
{
	playerStateChanger->KillPlayer();
	_hitDeleteFlag = false;
}

//**********************************************************
// �N���G�C�g�֐�
//**********************************************************
CDark* CDark::createWithTexture(Texture2D *texture)
{
	CDark *sprite = new CDark();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}