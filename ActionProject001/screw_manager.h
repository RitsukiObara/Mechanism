//============================================
//
// �l�W�}�l�[�W���[�w�b�_�[[screw_manager.h]
// Author�F��������
//
//============================================
#ifndef _SCREW_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _SCREW_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CScrew;		// �l�W

//--------------------------------------------
// �N���X(�N���}�l�[�W���[�N���X)
//--------------------------------------------
class CScrewManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CScrewManager();			// �R���X�g���N�^
	~CScrewManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CScrew* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CScrew* GetTop(void);				// �擪�̎擾����
	void Pull(CScrew* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CScrewManager* Create(void);		// ��������
	static CScrewManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CScrew* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CScrewManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif