//============================================
//
// �}�L�i���}�l�[�W���[�w�b�_�[[macchina_manager.h]
// Author�F��������
//
//============================================
#ifndef _MACCHINA_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _MACCHINA_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMacchina;		// ��s�@

//--------------------------------------------
// �N���X(�}�L�i�}�l�[�W���[�N���X)
//--------------------------------------------
class CMacchinaManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CMacchinaManager();			// �R���X�g���N�^
	~CMacchinaManager();		// �f�X�g���N�^

	// �����o�֐�
	void Regist(CMacchina* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CMacchina* GetTop(void);				// �擪�̎擾����
	void Pull(CMacchina* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CMacchinaManager* Create(void);		// ��������
	static CMacchinaManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CMacchina* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CMacchinaManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif