//============================================
//
// �R���{�w�b�_�[[combo.h]
// Author�F��������
//
//============================================
#ifndef _COMBO_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _COMBO_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CComboCircle;		// �R���{�̉~
class CComboScore;		// �R���{�X�R�A
class CComboMagni;		// �R���{�{��

//--------------------------------------------
// �}�N����`
//--------------------------------------------

//--------------------------------------------
// �N���X��`(�R���{)
//--------------------------------------------
class CCombo : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CCombo();					// �R���X�g���N�^
	~CCombo();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void AddCombo(const int nScore);	// �R���{�̉��Z����

	// �ÓI�����o�ϐ�
	static CCombo* Create(void);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	HRESULT CreateCombo(void);		// �R���{�̐�������
	HRESULT CreateLimit(void);		// �R���{�����̐�������
	HRESULT CreateComboScore(void);	// �R���{�X�R�A�̐�������

	// �����o�ϐ�
	CComboMagni* m_pMagni;			// �{��
	CComboCircle* m_pTimeLimit;		// �R���{����
	CComboScore* m_pScore;			// �R���{�X�R�A
};

#endif