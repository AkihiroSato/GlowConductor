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

// コンストラクタ
ObjectFactory::ObjectFactory()
{
	_currentStage = eStage_0;											// 初めのステージは０
	_basePointX = TargetPointer->getPositionX() + OBJECT_CREATE_POINT;	// 先にカメラターゲットを初期化しておかなければならない
}

// デストラクタ
ObjectFactory::~ObjectFactory()
{
	for (int i = 0; i < eStage_None; i++)
	{
		_dataIt = _objectData[i].begin();
		// デリートしながら消す
		while (_dataIt != _objectData[i].end())
		{
			delete (*_dataIt).second;
			_dataIt = _objectData[i].erase(_dataIt);
		}

		// オブジェクトが残っていたら止める
		assert(!((int)_objectData[i].size()));
	}
}

//****************************************************************
// オブジェクト生成関数
//****************************************************************
CObject* ObjectFactory::CreateObject(	int objectType,
										float radian,
										float x, float y,
										BaseAI* ai)
{
	CObject* object = nullptr;

	// 生成
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
// 闇生成関数
//****************************************************************
CObject* ObjectFactory::CreateDark(float radian, float x, float y, BaseAI* ai)
{
	// 各画像関数は、そのシーンで読み込まれていることが前提となる
	CObject* object = CDark::createWithTexture(SGraphMgr::Instance()->GetSpriteBatch(SGraphMgr::eGraph_Dark)->getTexture());
	object->SetState(radian, x, y, ai);

	//// パーティクルをセット
	ParticleSystemQuad* particle = MyParticles::DarkParticle::create();
	particle->setPosition(BALL_RADIUS, BALL_RADIUS);
	particle->setStartRadius(BALL_RADIUS);
	particle->setPositionType(ParticleSystem::PositionType::RELATIVE);
	object->addChild(particle);

	// アクションをセット
	RotateBy* rotate = RotateBy::create(1.0f, -600.0f);
	object->runAction(RepeatForever::create(rotate));

	return object;
}

//****************************************************************
// タッチアップアイテム生成関数
//****************************************************************
CObject* ObjectFactory::CreateTouchUp(float radian, float x, float y, BaseAI* ai)
{
	CObject* object = CTouchUp::createWithTexture(SGraphMgr::Instance()->GetSpriteBatch(SGraphMgr::eGraph_TouchUp)->getTexture());
	object->SetState(radian, x, y, ai);

	// アクションを設定
	object->setRotation(-30);
	ActionInterval* rotateAct = Sequence::create(
		EaseInOut::create(RotateBy::create(1.0f, 60), 2.0f),
		EaseInOut::create(RotateBy::create(1.0f, -60), 2.0f),
		nullptr);
	object->runAction(RepeatForever::create(rotateAct));

	return object;
}

//****************************************************************
// カメラの位置によってオブジェクトを自動生成
//****************************************************************
CObject* ObjectFactory::AutoCraeteObject(Point targetPoint)
{
	CObject* object = nullptr;

	// プレイヤーにもっとも近いデータのみを比較
	// 一定範囲内に入ったらオブジェクトを生成する
	if (_dataIt != _objectData[_currentStage].end() && TargetPointer->getPosition().x + OBJECT_CREATE_POINT > (*_dataIt).first + _basePointX)
	{
		// オブジェクトを生成
		sObjectData l_objectData = *((*_dataIt).second);	// 起点ポイントを足すためのコピーオブジェクト
		l_objectData._x += _basePointX;					// 起点ポイント分足す
		object = CreateObject(&l_objectData);
		log("%d", (int)(*_dataIt).first);

		// 次のオブジェクトデータを指す
		_dataIt++;

		// イテレーターが最後まで来た場合、次のステージに切り替わる
		if (_dataIt == _objectData[_currentStage].end())
			NextStage();
	}
	
	return object;
}

//****************************************************************
// オブジェクトデータ群を初期化する
//****************************************************************
void ObjectFactory::InitObjectData()
{
	// あらかじめ使用するマップデータをすべて読み込んでおく
	for (int initStageId = 0; initStageId < eStage_None; initStageId++)
	{
		// 外部から敵データファイルの読み込み
		string fileName = "ObjectData";
		stringstream idstream;					// 数値を入れる
		idstream << initStageId;
		string stageIdName = idstream.str();	// 今のステージ番号をStringに変換
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
		int stage = atoi((*it++).c_str());	// ステージ番号を取得
		int row = atoi((*it++).c_str());	// オブジェクト数を取得
		int col = atoi((*it++).c_str());	// オブジェクト1つの持つデータ数を取得

		// 読み取ったデータをもとにオブジェクトを作成
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

			// 取得したステージ番号マップにオブジェクト情報を入れる
			AddObjectData(new sObjectData(objType, r, x, y, nullptr), stage);
		}
	}
	// イテレーターをプレイするステージマップの始めに持ってくる
	_dataIt = _objectData[_currentStage].begin();
}

//****************************************************************
// オブジェクトデータ群に追加する
//****************************************************************
void ObjectFactory::AddObjectData(sObjectData* objData, const int& stageId)
{
	_objectData[stageId].insert(type_map::value_type(objData->_x, objData));
}

//****************************************************************
// ステージを進める
//****************************************************************
bool ObjectFactory::NextStage()
{
	// マップステージを読み込む
	_currentStage++;
	// オブジェクトの生成起点を再設定する
	_basePointX = TargetPointer->getPositionX() + OBJECT_CREATE_POINT;
	
	// 最後までステージを終えた場合、初めに戻す
	if (_currentStage == eStage_None)
	{
		_currentStage = eStage_0;
		_dataIt = _objectData[_currentStage].begin();
		return true;
	}
	// イテレーターを始めにセット
	_dataIt = _objectData[_currentStage].begin();
	return false;
}