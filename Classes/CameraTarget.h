#pragma once

#include "cocos2d.h"

class CameraTarget : public cocos2d::Sprite
{
public:
	CameraTarget();
	~CameraTarget(){}
	
	// �X�V����
	void Update(const cocos2d::Point& playerPoint);

	// �N���G�C�g�֐�
	CREATE_FUNC(CameraTarget);
	static CameraTarget* createWithTexture(cocos2d::Texture2D *texture);

	// 

private:
	float _movedX;	// 1�t���[���łǂꂾ����������
};

