//============================================
//
// ���}�l�[�W���[�w�b�_�[[needle_manager.h]
// Author�F��������
//
//============================================
#ifndef _NEEDLE_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _NEEDLE_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CNeedle;		// ��

//--------------------------------------------
// �N���X(���}�l�[�W���[�N���X)
//--------------------------------------------
class CNeedleManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CNeedleManager();			// �R���X�g���N�^
	~CNeedleManager();		// �f�X�g���N�^

	// �����o�֐�
	void Regist(CNeedle* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CNeedle* GetTop(void);				// �擪�̎擾����
	void Pull(CNeedle* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CNeedleManager* Create(void);		// ��������
	static CNeedleManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CNeedle* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CNeedleManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif