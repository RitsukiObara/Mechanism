//============================================
//
// �{�[�i�X�w�b�_�[[bonus.h]
// Author�F��������
//
//============================================
#ifndef _BONUS_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _BONUS_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define NUM_BONUS_DIGIT			(3)			// �{�[�i�X�̌���

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CBillboardAnim;		// �r���{�[�h

//--------------------------------------------
// �N���X��`(�{�[�i�X)
//--------------------------------------------
class CBonus : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CBonus();		// �R���X�g���N�^
	~CBonus();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��
	
	// �Z�b�g�E�Q�b�g�֌W
	int GetBonus(void) const;	// �{�[�i�X�̎擾����
	void AddBonus(void);		// �{�[�i�X�̉��Z����

	// �ÓI�����o�֐�
	static CBonus* Get(void);		// �擾����
	static CBonus* Create(const D3DXVECTOR3& pos);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void SetShift(void);		// ���炷���̐ݒ菈��

	// �����o�ϐ�
	CBillboardAnim* m_aNumber[NUM_BONUS_DIGIT];		// �����̏��
	D3DXVECTOR3 m_posShift;		// ���炷��
	int m_nBonusCombo;			// �{�[�i�X�̃R���{��

	// �ÓI�����o�ϐ�
	static CBonus* m_pBonus;	// �{�[�i�X�̏��
};

#endif