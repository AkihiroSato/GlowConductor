#include "CObject.h"

// �f�X�g���N�^
CObject::~CObject()
{
	if (pAi != nullptr)
		delete pAi;
}