#include "ObjectFactory.h"
#include "CDark.h"
#include "CObject.h"
#include "SGraphMgr.h"
#include "BaseAI.h"
#include "CTouchUp.h"
#include "SCameraTargetMgr.h"
#include "CustomParticle.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
USING_NS_CC;
using namespace std;

// �R���X�g���N�^
ObjectFactory::ObjectFactory()
{
	_currentStage = eStage_0;											// ���߂̃X�e�[�W�͂O
	_basePointX = TargetPointer->getPositionX() + OBJECT_CREATE_POINT;	// ��ɃJ�����^�[�Q�b�g�����������Ă����Ȃ���΂Ȃ�Ȃ�
}

// �f�X�g���N�^
ObjectFactory::~ObjectFactory()
{
	for (int i = 0; i < eStage_None; i++)
	{
		_dataIt = _objectData[i].begin();
		// �f���[�g���Ȃ������
		while (_dataIt != _objectData[i].end())
		{
			delete (*_dataIt).second;
			_dataIt = _objectData[i].erase(_dataIt);
		}

		// �I�u�W�F�N�g���c���Ă�����~�߂�
		assert(!((int)_objectData[i].size()));
	}
}

//****************************************************************
// �I�u�W�F�N�g�����֐�
//****************************************************************
CObject* ObjectFactory::CreateObject(	int objectType,
										float radian,
										float x, float y,
										BaseAI* ai)
{
	CObject* object = nullptr;

	// ����
	if (objectType == eDark) object = CreateDark(radian, x, y, ai);
	if (objectType == eTouchUp) object = CreateTouchUp(radian, x, y, ai);

	currentNode->addChild(object);

	return object;
}

CObject* ObjectFactory::CreateObject(sObjectData* objectData)
{
	return CreateObject(objectData->_type,
						objectData->_radius,
						objectData->_x,
						objectData->_y,
						objectData->_ai);
}

//****************************************************************
// �Ő����֐�
//****************************************************************
CObject* ObjectFactory::CreateDark(float radian, float x, float y, BaseAI* ai)
{
	// �e�摜�֐��́A���̃V�[���œǂݍ��܂�Ă��邱�Ƃ��O��ƂȂ�
	CObject* object = CDark::createWithTexture(SGraphMgr::Instance()->GetSpriteBatch(SGraphMgr::eGraph_Dark)->getTexture());
	object->SetState(radian, x, y, ai);

	//// �p�[�e�B�N�����Z�b�g
	ParticleSystemQuad* particle = MyParticles::DarkParticle::create();
	particle->setPosition(BALL_RADIUS, BALL_RADIUS);
	particle->setStartRadius(BALL_RADIUS);
	particle->setPositionType(ParticleSystem::PositionType::RELATIVE);
	object->addChild(particle);

	// �A�N�V�������Z�b�g
	RotateBy* rotate = RotateBy::create(1.0f, -600.0f);
	object->runAction(RepeatForever::create(rotate));

	return object;
}

//****************************************************************
// �^�b�`�A�b�v�A�C�e�������֐�
//****************************************************************
CObject* ObjectFactory::CreateTouchUp(float radian, float x, float y, BaseAI* ai)
{
	CObject* object = CTouchUp::createWithTexture(SGraphMgr::Instance()->GetSpriteBatch(SGraphMgr::eGraph_TouchUp)->getTexture());
	object->SetState(radian, x, y, ai);

	// �A�N�V������ݒ�
	object->setRotation(-30);
	ActionInterval* rotateAct = Sequence::create(
		EaseInOut::create(RotateBy::create(1.0f, 60), 2.0f),
		EaseInOut::create(RotateBy::create(1.0f, -60), 2.0f),
		nullptr);
	object->runAction(RepeatForever::create(rotateAct));

	return object;
}

//****************************************************************
// �J�����̈ʒu�ɂ���ăI�u�W�F�N�g����������
//****************************************************************
CObject* ObjectFactory::AutoCraeteObject(Point targetPoint)
{
	CObject* object = nullptr;

	// �v���C���[�ɂ����Ƃ��߂��f�[�^�݂̂��r
	// ���͈͓��ɓ�������I�u�W�F�N�g�𐶐�����
	if (_dataIt != _objectData[_currentStage].end() && TargetPointer->getPosition().x + OBJECT_CREATE_POINT > (*_dataIt).first + _basePointX)
	{
		// �I�u�W�F�N�g�𐶐�
		sObjectData l_objectData = *((*_dataIt).second);	// �N�_�|�C���g�𑫂����߂̃R�s�[�I�u�W�F�N�g
		l_objectData._x += _basePointX;					// �N�_�|�C���g������
		object = CreateObject(&l_objectData);
		log("%d", (int)(*_dataIt).first);

		// ���̃I�u�W�F�N�g�f�[�^���w��
		_dataIt++;

		// �C�e���[�^�[���Ō�܂ŗ����ꍇ�A���̃X�e�[�W�ɐ؂�ւ��
		if (_dataIt == _objectData[_currentStage].end())
			NextStage();
	}
	
	return object;
}

//****************************************************************
// �I�u�W�F�N�g�f�[�^�Q������������
//****************************************************************
void ObjectFactory::InitObjectData()
{
	// ���炩���ߎg�p����}�b�v�f�[�^�����ׂēǂݍ���ł���
	for (int initStageId = 0; initStageId < eStage_None; initStageId++)
	{
		// �O������G�f�[�^�t�@�C���̓ǂݍ���
		string fileName = "ObjectData";
		stringstream idstream;					// ���l������
		idstream << initStageId;
		string stageIdName = idstream.str();	// ���̃X�e�[�W�ԍ���String�ɕϊ�
		fileName = fileName + stageIdName + ".txt";
		std::string filePath = FileUtils::sharedFileUtils()->fullPathForFilename(fileName);
		ifstream ifs(filePath);
		vector<string> value;
		string str;

		while (getline(ifs, str))
		{
			value.push_back(str);
		}

		vector<string>::iterator it = value.begin();
		int stage = atoi((*it++).c_str());	// �X�e�[�W�ԍ����擾
		int row = atoi((*it++).c_str());	// �I�u�W�F�N�g�����擾
		int col = atoi((*it++).c_str());	// �I�u�W�F�N�g1�̎��f�[�^�����擾

		// �ǂݎ�����f�[�^�����ƂɃI�u�W�F�N�g���쐬
		string kari;
		int objType;
		float r, x, y;
		int a;

		for (int i = 0; i < row; i++)
		{
			stringstream s(*it++);
			getline(s, kari, ',');
			objType = atoi(kari.c_str());
			getline(s, kari, ',');
			r = stof(kari.c_str());
			getline(s, kari, ',');
			x = stof(kari.c_str());
			getline(s, kari, ',');
			y = stof(kari.c_str());
			getline(s, kari, ',');
			a = atoi(kari.c_str());

			// �擾�����X�e�[�W�ԍ��}�b�v�ɃI�u�W�F�N�g��������
			AddObjectData(new sObjectData(objType, r, x, y, nullptr), stage);
		}
	}
	// �C�e���[�^�[���v���C����X�e�[�W�}�b�v�̎n�߂Ɏ����Ă���
	_dataIt = _objectData[_currentStage].begin();
}

//****************************************************************
// �I�u�W�F�N�g�f�[�^�Q�ɒǉ�����
//****************************************************************
void ObjectFactory::AddObjectData(sObjectData* objData, const int& stageId)
{
	_objectData[stageId].insert(type_map::value_type(objData->_x, objData));
}

//****************************************************************
// �X�e�[�W��i�߂�
//****************************************************************
bool ObjectFactory::NextStage()
{
	// �}�b�v�X�e�[�W��ǂݍ���
	_currentStage++;
	// �I�u�W�F�N�g�̐����N�_���Đݒ肷��
	_basePointX = TargetPointer->getPositionX() + OBJECT_CREATE_POINT;
	
	// �Ō�܂ŃX�e�[�W���I�����ꍇ�A���߂ɖ߂�
	if (_currentStage == eStage_None)
	{
		_currentStage = eStage_0;
		_dataIt = _objectData[_currentStage].begin();
		return true;
	}
	// �C�e���[�^�[���n�߂ɃZ�b�g
	_dataIt = _objectData[_currentStage].begin();
	return false;
}