//============================================
//
// �G�}�l�[�W���[�w�b�_�[[enemy_manager.h]
// Author�F��������
//
//============================================
#ifndef _ENEMY_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CEnemy;		// �G

//--------------------------------------------
// �N���X(�G�}�l�[�W���[�N���X)
//--------------------------------------------
class CEnemyManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CEnemyManager();			// �R���X�g���N�^
	~CEnemyManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CEnemy* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CEnemy* GetTop(void);				// �擪�̎擾����
	void Pull(CEnemy* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CEnemyManager* Create(void);		// ��������
	static CEnemyManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CEnemy* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CEnemyManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif