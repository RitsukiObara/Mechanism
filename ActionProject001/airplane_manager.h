//============================================
//
// ��s�@�}�l�[�W���[�w�b�_�[[airplane_manager.h]
// Author�F��������
//
//============================================
#ifndef _AIRPLANE_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _AIRPLANE_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CAirplane;		// ��s�@

//--------------------------------------------
// �N���X(�r�u���I���}�l�[�W���[�N���X)
//--------------------------------------------
class CAirplaneManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CAirplaneManager();			// �R���X�g���N�^
	~CAirplaneManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CAirplane* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CAirplane* GetTop(void);				// �擪�̎擾����
	void Pull(CAirplane* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CAirplaneManager* Create(void);		// ��������
	static CAirplaneManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CAirplane* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CAirplaneManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif