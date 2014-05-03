#include "SGraphMgr.h"
USING_NS_CC;

// コンストラクタ
SGraphMgr::SGraphMgr()
{
	// すべての要素をnullptrで初期化
	for (int i = 0; i < GRAPH_MAX; i++)
	{
		pSpriteBatchNode[i] = nullptr;
	}

	_texturePlace = String::createWithFormat("textures");
}

// 指定したシーン内で使用する画像を読み込む
bool SGraphMgr::SetUsingGraph(eScene scene)
{
	// すべての要素をnullptrで初期化
	for (int i = 0; i < GRAPH_MAX; i++)
	{
		pSpriteBatchNode[i] = nullptr;
	}
	if (scene == eScene_Game) return SetGraph_Game();
	if (scene == eScene_title) return SetGraph_Title();

	return true;
}

// 配列内のスプライトバッチを指定ノードに登録する関数
bool SGraphMgr::AddUsingScene(Node* node)
{
	for (int i = 0; i < GRAPH_MAX; i++)
	{
		if (pSpriteBatchNode[i] == nullptr) continue;
		node->addChild(pSpriteBatchNode[i]);
	}

	return true;
}

// バッチノードを取得
SpriteBatchNode* SGraphMgr::GetSpriteBatch(int index)
{
	if (pSpriteBatchNode[index] == nullptr) return nullptr;
	else return pSpriteBatchNode[index];
}

// バッチノードのテクスチャを取得
Texture2D* SGraphMgr::GetBatchTexture(int index)
{
	// 登録されていない場合nullptrを返す
	if (pSpriteBatchNode[index] == nullptr) return nullptr;

	return pSpriteBatchNode[index]->getTexture();
}

//**********************************************************
// 各シーンで使用する画像読み込み関数
//**********************************************************
// ゲームシーンで使用する画像を読み込む関数
bool SGraphMgr::SetGraph_Game()
{
	pSpriteBatchNode[eGraph_Ball] = SpriteBatchNode::create("Ball.png");
	pSpriteBatchNode[eGraph_Dark] = SpriteBatchNode::create("dark.png");
	pSpriteBatchNode[eGraph_TouchUp] = SpriteBatchNode::create("touch_up.png");
	pSpriteBatchNode[eGraph_TouchBack] = SpriteBatchNode::create("touchWindow.png");
	return true;
}

// タイトルシーンで使用する画像を読み込む関数
bool SGraphMgr::SetGraph_Title()
{
	pSpriteBatchNode[eGraph_title_name_1] = SpriteBatchNode::create("title_name_1.png");
	pSpriteBatchNode[eGraph_title_name_2] = SpriteBatchNode::create("title_name_2.png");
	pSpriteBatchNode[eGraph_title_start_button] = SpriteBatchNode::create("title_start_button.png");
	pSpriteBatchNode[eGraph_title_back_graph] = SpriteBatchNode::create("title_back_graph.png");
	return true;
}