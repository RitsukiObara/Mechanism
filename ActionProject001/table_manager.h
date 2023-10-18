//============================================
//
// ��}�l�[�W���[�w�b�_�[[table_manager.h]
// Author�F��������
//
//============================================
#ifndef _TABLE_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _TABLE_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CTable;		// ��

//--------------------------------------------
// �N���X(��}�l�[�W���[�N���X)
//--------------------------------------------
class CTableManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CTableManager();			// �R���X�g���N�^
	~CTableManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CTable* pThis);		// �o�^����
	void Uninit(void);				// �I������
	
	CTable* GetTop(void);			// �擪�̎擾����
	void Pull(CTable* pThis);		// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CTableManager* Create(void);		// ��������
	static CTableManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CTable* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;		// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CTableManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif