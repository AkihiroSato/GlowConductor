#include "CameraTarget.h"
USING_NS_CC;

// �R���X�g���N�^
CameraTarget::CameraTarget()
{
	
}

// �X�V����
void CameraTarget::Update(const Point& playerPoint)
{
	// �v���C���[�̉E�����J���邽�߂̕ϐ�
	float spaceLeft = Director::getInstance()->getWinSize().width / 3;

	// �^�[�Q�b�g���X�V
	float moveX = 2.0f;	// �^�[�Q�b�g���i�ދ���
	float moveY = (playerPoint.y - this->getPosition().y) * 0.05f;
	this->setPosition(this->getPosition() + Point(moveX, moveY));
	

	// ���ړ��ʂ𑫂�
	_movedX = moveX;

	// �����X�N���[�����ǂ��t���Ȃ��ꍇ�A�^�[�Q�b�g���v���C���[�Ɋ񂹂�
	if (this->getPosition().x <= playerPoint.x + spaceLeft)
	{
		moveX = (playerPoint.x + spaceLeft - this->getPosition().x) * 0.005f;
		_movedX += moveX;
		this->setPosition(this->getPosition() + Point(moveX, this->getPosition().y));
	}
}

//**********************************************************
// �N���G�C�g�֐�
//**********************************************************
CameraTarget* CameraTarget::createWithTexture(Texture2D *texture)
{
	CameraTarget *sprite = new CameraTarget();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->setOpacity(0);
		sprite->autorelease();
		sprite->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}