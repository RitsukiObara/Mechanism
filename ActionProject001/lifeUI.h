//============================================
//
// �̗�UI�w�b�_�[[lifeUI.h]
// Author�F��������
//
//============================================
#ifndef _LIFEUI_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _LIFEUI_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_LIFE_POLYGON		(3)		// �̗͂̍ő吔

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CObject2D;		// 2D�|���S��

//--------------------------------------------
// �N���X��`(�̗�UI)
//--------------------------------------------
class CLifeUI : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CLifeUI();					// �R���X�g���N�^
	~CLifeUI();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void SetData(void);			// ���̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CLifeUI* Create(void);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void SetDataBack(void);				// �w�i�̐�������
	void SetDataLife(void);				// �̗͂̐�������
	HRESULT CreateBack(void);			// �w�i�̐�������
	HRESULT CreateLife(void);			// �̗͂̐�������

	// �����o�ϐ�
	CObject2D* m_pBack;						// �w�i
	CObject2D* m_apLife[MAX_LIFE_POLYGON];	// �̗�
};

#endif