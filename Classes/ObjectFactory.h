#ifndef __OBJECT_FACTORY__
#define __OBJECT_FACTORY__

#include "cocos2d.h"
#include <list>
#include <vector>
#include <map>

class CObject;
class BaseAI;

static const float OBJECT_CREATE_POINT = 1500.0f;

// �I�u�W�F�N�g�쐬�ɕK�v�ȃf�[�^�Q
class sObjectData
{
public:
	sObjectData(int type, float radian, float x, float y, BaseAI* ai)
		: _type(type), _radius(radian), _x(x), _y(y), _ai(ai){}

	int	_type;
	float _radius;
	float _x;
	float _y;
	BaseAI* _ai;
};

enum eObjectType
{
	eDark, eTouchUp
};

//****************************************************************
// ObjectFactory�N���X
//****************************************************************
class ObjectFactory : public cocos2d::Node
{
	typedef std::multimap<float, sObjectData*> type_map;
	enum eStageNum
	{
		eStage_0,
		eStage_1,
		eStage_2,

		eStage_None
	};
public:
	ObjectFactory();
	~ObjectFactory();

	// �I�u�W�F�N�g�𐶐�
	CObject* CreateObject(
		int objectType,
		float radian,
		float x, float y,
		BaseAI* ai = nullptr);
	CObject* CreateObject(sObjectData* objectData);

	// �����m�[�h��o�^����
	void SetNode(cocos2d::Node* node){ currentNode = node; }

	// �I�u�W�F�N�g�f�[�^�Q�Ƀf�[�^������i���j
	void InitObjectData();

	// �I�u�W�F�N�g�f�[�^�Q�ɒǉ�����
	void AddObjectData(sObjectData* objData, const int& stageId);

	// �J�����̈ʒu�ɂ���ăI�u�W�F�N�g�𐶐�����
	CObject* AutoCraeteObject(cocos2d::Point playerPoint);

	CREATE_FUNC(ObjectFactory);

private:
	// ��������I�u�W�F�N�g
	// �Ő����֐�
	CObject* CreateDark(float radian, float x, float y, BaseAI* ai = nullptr);
	CObject* CreateTouchUp(float radian, float x, float y, BaseAI* ai = nullptr);

	// ���������I�u�W�F�N�g��݂艺����m�[�h
	cocos2d::Node* currentNode;

	// �I�u�W�F�N�g�̃f�[�^�x�[�X
	//type_map _objectData;
	type_map _objectData[eStage_None];

	//�f�[�^�x�[�X�փA�N�Z�X���邽�߂̃C�e���[�^�[
	type_map::iterator _dataIt;

	// ���݃v���C���̃X�e�[�W�f�[�^
	int _currentStage;

	// �X�e�[�W��i�߂�(�X�e�[�W���Ō�܂ŗ����ꍇtrue��Ԃ�)
	bool NextStage();

	// �����I�u�W�F�N�g�������A�N�_�ƂȂ�X���W
	float _basePointX;
};

#endif