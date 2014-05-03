#include "ObjectMgr.h"
#include "CObject.h"
#include "cocos2d.h"
#include "Collision.h"
USING_NS_CC;
using namespace std;

// �R���X�g���N�^
ObjectMgr::ObjectMgr()
{

}

// �f�X�g���N�^
ObjectMgr::~ObjectMgr()
{
	for (int i = 0; i < REGIST_ARRAY; i++)
	{
		list<CObject*>::iterator it = CollisionObject[i].begin();
		while (it != CollisionObject[i].end())
		{
			(*it)->removeFromParentAndCleanup(true);
			it = CollisionObject[i].erase(it);
		}
	}
}

// ����������
void ObjectMgr::InitObjMgr()
{

}

// �I�u�W�F�N�g�o�^
bool ObjectMgr::RegistObject(const int arrayNum, CObject* obj)
{
	// �z��O�A�N�Z�X��h��
	if (arrayNum >= REGIST_ARRAY)
	{

		return false;
	}

	// �I�u�W�F�N�g��ǉ�
	CollisionObject[arrayNum].push_back(obj);
	
	return false;
}

// �����蔻��v�Z
void ObjectMgr::CalcCollision()
{
	// �z��Q�̑�������
	for (int i = 0; i < REGIST_ARRAY - 1; i++)
	{
		for (int j = i + 1; j < REGIST_ARRAY; j++)
		{
			list<CObject*>::iterator it_1 = CollisionObject[i].begin();

			while (it_1 != CollisionObject[i].end())
			{
				list<CObject*>::iterator it_2 = CollisionObject[j].begin();
				while (it_2 != CollisionObject[j].end())
				{
					if (CollisionCircle(**it_1, **it_2))
					{
						(*it_1)->CollisionFunction(playerStateChanger);
						(*it_2)->CollisionFunction(playerStateChanger);
					}
					it_2++;
				}
				it_1++;
			}			
		}
	}
}

// �X�V����(��ʒ������W���擾)
void ObjectMgr::Update(const Point& target)
{

	for (int i = 1; i < REGIST_ARRAY; i++)
	{
		list<CObject*>::iterator it = CollisionObject[i].begin();
		while (it != CollisionObject[i].end())
		{
			// ���S�t���O�����Ă��������
			// ��ʊO�ɍs�����I�u�W�F�N�g�̏���(�̂��Ƀv���C���[��Ɨ�������)
			if ((*it)->GetDeleteFlag() ||
				((target.x - Director::getInstance()->getWinSize().width / 2 - (*it)->GetRadius() - 10) >(*it)->getPosition().x))
			{
				(*it)->removeFromParentAndCleanup(true);
				it = CollisionObject[i].erase(it);
			}else it++;
			
		}
	}
}