#pragma once

#include "Singleton.h"
#include <list>

class BaseAI;

// �I�u�W�F�N�g�̃f�[�^�x�[�X�i�V���O���g���j
class SObjectDatabase
{
public:
	static SObjectDatabase* Instance()
	{
		static SObjectDatabase obj;
		return &obj;
	}

private:
	SObjectDatabase(){}
	~SObjectDatabase(){}
	SObjectDatabase(const SObjectDatabase& data){}
	SObjectDatabase& operator=(const SObjectDatabase& data){}

	
};