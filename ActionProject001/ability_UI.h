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
class CObject2D;				// 2D�|���S��

//--------------------------------------------
// �N���X��`(�\��UI)
//--------------------------------------------
class CAbilityUI : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(�|���S��)
	enum GAGE
	{
		GAGE_BIG_GROUND = 0,	// ��Z�̉��n
		GAGE_BIG_METER,			// ��Z�̃��[�^�[
		GAGE_SMALL_GROUND,		// ���Z�̉��n
		GAGE_SMALL_METER,		// ���Z�̃��[�^�[
		GAGE_MAX				// ���̗񋓌^�̑���
	};

	// �\���̒�`(�e�N�X�`���֌W�̏��)
	struct STexInfo
	{
		int m_nTexIdx;			// �e�N�X�`���̔ԍ�
		float m_fTexSizeY;		// �e�N�X�`���̏c�T�C�Y
	};

	CAbilityUI();			// �R���X�g���N�^
	~CAbilityUI();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall);				// ���̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CAbilityUI* Create(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall);	// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Size(const CAbility::TYPE type, const CAbilityUI::GAGE gage, const int nInterval, float fSizeMove);		// �T�C�Y�ݒ菈��

	// �����o�ϐ�
	CObject2D* m_apObjectUI[GAGE_MAX];			// �|���S���̏��
	STexInfo m_aTexInfo[CAbility::TYPE_MAX];	// �e�N�X�`���̏��

	// �ÓI�����o�ϐ�
	static const char* m_acTextureFileName[CAbility::TYPE_MAX];		// �e�N�X�`���̖��O
};

#endif