//============================================
//
// �\�͂�UI�w�b�_�[[ability_UI.h]
// Author�F��������
//
//============================================
#ifndef _ABILITY_UI_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _ABILITY_UI_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"
#include "player_ability.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CBillboard;			// �r���{�[�h

//--------------------------------------------
// �N���X��`(�\��UI)
//--------------------------------------------
class CAbilityUI : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CAbilityUI();			// �R���X�g���N�^
	~CAbilityUI();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3 pos);					// ���̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CAbilityUI* Create(const D3DXVECTOR3 pos);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void PossibleColor(void);	// �g�p�󋵂̐ݒ菈��
	void PosChase(void);		// �ʒu�ǔ�����

	// �����o�ϐ�
	CBillboard* m_apAbilityUI[TYPE_MAX];	// �\�͂̏��

	// �ÓI�����o�ϐ�
	static const char* m_acTextureFileName[CAbility::TYPE_MAX];		// �e�N�X�`���̖��O
};

#endif