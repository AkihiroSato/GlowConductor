#ifndef __OBJECT_MGR__
#define __OBJECT_MGR__

#include "cocos2d.h"
#include <list>

class CObject;
class IPlayerStateChange;

static const int REGIST_OBJ_MAX = 32;
static const int REGIST_ARRAY = 2;

class ObjectMgr : public cocos2d::Node
{
public:
	ObjectMgr();
	~ObjectMgr();

	// ����������
	void InitObjMgr();

	// �I�u�W�F�N�g�ɓo�^(�ǂ����̔��ɓo�^���邩)
	// �o�^�ɐ��������ꍇ�Atrue��Ԃ�
	bool RegistObject(const int arrayNum, CObject* obj);

	// �����蔻��̌v�Z
	void CalcCollision();

	// �X�V����
	void Update(const cocos2d::Point& target);

	// �N���G�C�g�֐�
	CREATE_FUNC(ObjectMgr);

	// �v���C���[�A�h���X��o�^
	void SetPlayerStateChanger(IPlayerStateChange* changer){ playerStateChanger = changer; }

private:
	// �����蔻����Ƃ�I�u�W�F�N�g�̓o�^�z��
	std::list<CObject*> CollisionObject[REGIST_ARRAY];

	// �v���C���[�̃A�h���X
	IPlayerStateChange* playerStateChanger;

};

#endif