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
class CNumber;			// ����

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_COMBO_DIGIT		(3)			// �R���{�̌���

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

	void SetData(void);			// ���̐ݒ菈��
	void SetDataCombo(void);	// �R���{�̏��̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetCombo(const int nCombo);	// �R���{�̐ݒ菈��
	int GetCombo(void) const;			// �R���{�̎擾����
	void AddCombo(void);				// �R���{�̉��Z����

	// �ÓI�����o�ϐ�
	static CCombo* Create(void);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	HRESULT CreateCombo(void);	// �R���{�̐�������
	HRESULT CreateLimit(void);	// �R���{�����̐�������
	void Calculate(void);		// �v�Z����

	// �����o�ϐ�
	CComboCircle* m_pTimeLimit;		// �R���{����
	CNumber *m_apNumber[MAX_COMBO_DIGIT];		// �ԍ��̏��
	int m_nCombo;				// �R���{��
};

#endif