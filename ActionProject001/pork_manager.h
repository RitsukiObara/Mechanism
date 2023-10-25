//============================================
//
// �|�[�N�}�l�[�W���[�w�b�_�[[pork_manager.h]
// Author�F��������
//
//============================================
#ifndef _PORK_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _PORK_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CPork;		// �|�[�N

//--------------------------------------------
// �N���X(�|�[�N�}�l�[�W���[�N���X)
//--------------------------------------------
class CPorkManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CPorkManager();			// �R���X�g���N�^
	~CPorkManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CPork* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CPork* GetTop(void);				// �擪�̎擾����
	void Pull(CPork* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CPorkManager* Create(void);		// ��������
	static CPorkManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CPork* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CPorkManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif