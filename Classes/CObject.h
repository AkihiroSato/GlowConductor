#ifndef __C_OBJECT_H__
#define __C_OBJECT_H__

#include "cocos2d.h"
#include "BaseAI.h"
#include "IPlayerStateChange.h"

static const float BALL_RADIUS = 256;
static const float TOUCH_UP_RADIAN = 256.0f;
class CPlayer;

class CObject : public cocos2d::Sprite
{
public:
	CObject(){}
	CObject(float radius, float x, float y){ 
		_radius = radius;
		this->setPosition(cocos2d::Point(x, y));
		this->setScale(_radius / BALL_RADIUS);
	}

	// �Փˎ��Ɏ��s�����֐�
	virtual void CollisionFunction(IPlayerStateChange* playerStateChanger){}

	// �I�u�W�F�N�g�̍X�V����
	virtual void Update(){}

	// ���a�擾
	float GetRadius(){ return _radius; }

	// �N���G�C�g�֐�
	CREATE_FUNC(CObject);

	// �X�e�[�^�X��ݒ肷��
	void SetState(float radius, float x, float y, BaseAI* ai = nullptr)
	{
		_radius = radius;
		this->setPosition(cocos2d::Point(x, y));
		this->setScale(_radius / BALL_RADIUS);
		pAi = ai;
		_hitDeleteFlag = false;
	}

	// �Փˎ��ɏ����邩�ǂ����擾
	bool GetDeleteFlag(){ return _hitDeleteFlag; }

protected:
	float _radius;		// ���a
	BaseAI* pAi;		// AI
	bool _hitDeleteFlag;

};

#endif