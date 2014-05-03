#ifndef __SGRAPH_MGR_H__
#define __SGRAPH_MGR_H__

static const int GRAPH_MAX = 64;

#include "Singleton.h"
#include "cocos2d.h"

enum eScene
{
	eScene_title,
	eScene_Game,
	eScene_Result,
};



class SGraphMgr : public Singleton<SGraphMgr>, public cocos2d::Node
{
	friend Singleton< SGraphMgr >;

public:
	//**************************************************************
	// 各シーンで使用する画像
	//**************************************************************
	enum GameSceneGraph
	{
		eGraph_Ball = 0,
		eGraph_Dark,
		eGraph_TouchUp,
		eGraph_TouchBack,
	};
	enum TitleSceneGraph
	{
		eGraph_title_name_1,
		eGraph_title_name_2,
		eGraph_title_start_button,
		eGraph_title_back_graph
	};

	// そのシーンで使用する画像を配列に登録する関数
	bool SetUsingGraph(eScene scene);

	// 配列内のスプライトバッチを指定ノードに登録する関数
	bool AddUsingScene(cocos2d::Node* node);

	// 配列画像を取得する
	cocos2d::SpriteBatchNode* GetSpriteBatch(int index);

	// テクスチャを取得
	cocos2d::Texture2D* GetBatchTexture(int index);

	//**********************************************************
	// 各シーンで使用する画像読み込み関数
	//**********************************************************
	bool SetGraph_Game();
	bool SetGraph_Title();

private:
	SGraphMgr();

	// 画像配列	
	cocos2d::SpriteBatchNode* pSpriteBatchNode[GRAPH_MAX];

	// 画像が存在するフォルダ
	cocos2d::String* _texturePlace;

};

#endif // __HELLOWORLD_SCENE_H__
