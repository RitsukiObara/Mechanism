//============================================
//
// �R���{�{���w�b�_�[[combo_magni.h]
// Author�F��������
//
//============================================
#ifndef _COMBO_MAGNI_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _COMBO_MAGNI_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "number.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_COMBO_DIGIT		(3)			// �R���{�̌���

//--------------------------------------------
// �N���X��`(�R���{�{��)
//--------------------------------------------
class CComboMagni : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CComboMagni();			// �R���X�g���N�^
	~CComboMagni();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fShift);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetMagni(const int nMagni);	// �{���̐ݒ菈��
	int GetMagni(void) const;			// �{���̎擾����

	// �ÓI�����o�ϐ�
	void AddMagni(void);	// �X�R�A�̉��Z����
	static CComboMagni* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fShift);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Calculate(void);			// �v�Z����

	// �����o�ϐ�
	CNumber* m_apNumber[MAX_COMBO_DIGIT];		// �ԍ��̏��
	int m_nMagni;					// �R���{�{��
};

#endif