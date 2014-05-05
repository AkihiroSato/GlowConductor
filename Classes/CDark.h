#ifndef __C_DARK_H__
#define __C_DARK_H__

#include "CObject.h"

class CDark : public CObject
{
public:
	CDark();
	CDark(float radius, float x, float y);
	virtual ~CDark();

	// �X�V����
	void update(float delta);

	// �Փˎ��Ɏ��s�����֐�
	void CollisionFunction(IPlayerStateChange* playerStateChanger);

	// �N���G�C�g�֐�
	CREATE_FUNC(CDark);
	static CDark* createWithTexture(cocos2d::Texture2D *texture);

private:
	//++++++++++++++++++++++++++++++++++++++
	// �v���C�x�[�g�ϐ�
	//++++++++++++++++++++++++++++++++++++++
			

	//++++++++++++++++++++++++++++++++++++++
	// �v���C�x�[�g�֐�
	//++++++++++++++++++++++++++++++++++++++
	
};

#endif
