#ifndef __OBJECT_FACTORY__
#define __OBJECT_FACTORY__

#include "cocos2d.h"
#include <list>
#include <vector>
#include <map>

class CObject;
class BaseAI;

static const float OBJECT_CREATE_POINT = 1500.0f;

// オブジェクト作成に必要なデータ群
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
// ObjectFactoryクラス
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

	// オブジェクトを生成
	CObject* CreateObject(
		int objectType,
		float radian,
		float x, float y,
		BaseAI* ai = nullptr);
	CObject* CreateObject(sObjectData* objectData);

	// 生成ノードを登録する
	void SetNode(cocos2d::Node* node){ currentNode = node; }

	// オブジェクトデータ群にデータを入れる（仮）
	void InitObjectData();

	// オブジェクトデータ群に追加する
	void AddObjectData(sObjectData* objData, const int& stageId);

	// カメラの位置によってオブジェクトを生成する
	CObject* AutoCraeteObject(cocos2d::Point playerPoint);

	CREATE_FUNC(ObjectFactory);

private:
	// 生成するオブジェクト
	// 闇生成関数
	CObject* CreateDark(float radian, float x, float y, BaseAI* ai = nullptr);
	CObject* CreateTouchUp(float radian, float x, float y, BaseAI* ai = nullptr);

	// 生成したオブジェクトを吊り下げるノード
	cocos2d::Node* currentNode;

	// オブジェクトのデータベース
	//type_map _objectData;
	type_map _objectData[eStage_None];

	//データベースへアクセスするためのイテレーター
	type_map::iterator _dataIt;

	// 現在プレイ中のステージデータ
	int _currentStage;

	// ステージを進める(ステージが最後まで来た場合trueを返す)
	bool NextStage();

	// 自動オブジェクト生成時、起点となるX座標
	float _basePointX;
};

#endif