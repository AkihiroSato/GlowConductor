#ifndef __TOUCH_UP__
#define __TOUCH_UP__

#include "CObject.h"

class CTouchUp : public CObject
{
public:
	CTouchUp();
	~CTouchUp();

	// �X�V�A���S���Y��
	void Update(){}

	// �I�u�W�F�N�g�ɂ����������̏���
	void CollisionFunction(IPlayerStateChange* playerStateChanger);

	// �N���G�C�g�֐�
	CREATE_FUNC(CTouchUp);
	static CTouchUp* createWithTexture(cocos2d::Texture2D *texture);

private:

};

#endif