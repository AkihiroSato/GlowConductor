#include "SGraphMgr.h"
USING_NS_CC;

// �R���X�g���N�^
SGraphMgr::SGraphMgr()
{
	// ���ׂĂ̗v�f��nullptr�ŏ�����
	for (int i = 0; i < GRAPH_MAX; i++)
	{
		pSpriteBatchNode[i] = nullptr;
	}

	_texturePlace = String::createWithFormat("textures");
}

// �w�肵���V�[�����Ŏg�p����摜��ǂݍ���
bool SGraphMgr::SetUsingGraph(eScene scene)
{
	// ���ׂĂ̗v�f��nullptr�ŏ�����
	for (int i = 0; i < GRAPH_MAX; i++)
	{
		pSpriteBatchNode[i] = nullptr;
	}
	if (scene == eScene_Game) return SetGraph_Game();
	if (scene == eScene_title) return SetGraph_Title();

	return true;
}

// �z����̃X�v���C�g�o�b�`���w��m�[�h�ɓo�^����֐�
bool SGraphMgr::AddUsingScene(Node* node)
{
	for (int i = 0; i < GRAPH_MAX; i++)
	{
		if (pSpriteBatchNode[i] == nullptr) continue;
		node->addChild(pSpriteBatchNode[i]);
	}

	return true;
}

// �o�b�`�m�[�h���擾
SpriteBatchNode* SGraphMgr::GetSpriteBatch(int index)
{
	if (pSpriteBatchNode[index] == nullptr) return nullptr;
	else return pSpriteBatchNode[index];
}

// �o�b�`�m�[�h�̃e�N�X�`�����擾
Texture2D* SGraphMgr::GetBatchTexture(int index)
{
	// �o�^����Ă��Ȃ��ꍇnullptr��Ԃ�
	if (pSpriteBatchNode[index] == nullptr) return nullptr;

	return pSpriteBatchNode[index]->getTexture();
}

//**********************************************************
// �e�V�[���Ŏg�p����摜�ǂݍ��݊֐�
//**********************************************************
// �Q�[���V�[���Ŏg�p����摜��ǂݍ��ފ֐�
bool SGraphMgr::SetGraph_Game()
{
	pSpriteBatchNode[eGraph_Ball] = SpriteBatchNode::create("Ball.png");
	pSpriteBatchNode[eGraph_Dark] = SpriteBatchNode::create("dark.png");
	pSpriteBatchNode[eGraph_TouchUp] = SpriteBatchNode::create("touch_up.png");
	pSpriteBatchNode[eGraph_TouchBack] = SpriteBatchNode::create("touchWindow.png");
	return true;
}

// �^�C�g���V�[���Ŏg�p����摜��ǂݍ��ފ֐�
bool SGraphMgr::SetGraph_Title()
{
	pSpriteBatchNode[eGraph_title_name_1] = SpriteBatchNode::create("title_name_1.png");
	pSpriteBatchNode[eGraph_title_name_2] = SpriteBatchNode::create("title_name_2.png");
	pSpriteBatchNode[eGraph_title_start_button] = SpriteBatchNode::create("title_start_button.png");
	pSpriteBatchNode[eGraph_title_back_graph] = SpriteBatchNode::create("title_back_graph.png");
	return true;
}