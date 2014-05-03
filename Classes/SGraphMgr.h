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
	// �e�V�[���Ŏg�p����摜
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

	// ���̃V�[���Ŏg�p����摜��z��ɓo�^����֐�
	bool SetUsingGraph(eScene scene);

	// �z����̃X�v���C�g�o�b�`���w��m�[�h�ɓo�^����֐�
	bool AddUsingScene(cocos2d::Node* node);

	// �z��摜���擾����
	cocos2d::SpriteBatchNode* GetSpriteBatch(int index);

	// �e�N�X�`�����擾
	cocos2d::Texture2D* GetBatchTexture(int index);

	//**********************************************************
	// �e�V�[���Ŏg�p����摜�ǂݍ��݊֐�
	//**********************************************************
	bool SetGraph_Game();
	bool SetGraph_Title();

private:
	SGraphMgr();

	// �摜�z��	
	cocos2d::SpriteBatchNode* pSpriteBatchNode[GRAPH_MAX];

	// �摜�����݂���t�H���_
	cocos2d::String* _texturePlace;

};

#endif // __HELLOWORLD_SCENE_H__
