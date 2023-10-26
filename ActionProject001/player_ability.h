//============================================
//
// �v���C���[�̔\�̓w�b�_�[[player_ability.h]
// Author�F��������
//
//============================================
#ifndef _PLAYER_ABILITY_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_ABILITY_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CPlayer;			// �v���C���[
class CElevation;		// �N���n��

//--------------------------------------------
// �N���X(�v���C���[�̔\�̓N���X)
//--------------------------------------------
class CAbility
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(�\��)
	enum ABILITY
	{
		ABILITY_NONE = 0,		// �����
		ABILITY_HOVER,			// �z�o�[�W�F�b�g
		ABILITY_JETDASH,		// �W�F�b�g�_�b�V��
		ABILITY_DASHJUMP,		// �_�b�V���W�����v
		ABILITY_GROUNDQUAKE,	// �O���E���h�N�G�C�N
		ABILITY_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_HOVER = 0,			// �z�o�[�W�F�b�g
		TYPE_JETDASH,			// �W�F�b�g�_�b�V��
		TYPE_GROUNDQUAKE,		// �O���E���h�N�G�C�N
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	CAbility();				// �R���X�g���N�^
	~CAbility();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(CPlayer& player);		// �X�V����

	void SetData(void);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֐�
	void SetAbility(const ABILITY ability, CPlayer& player);		// �\�͂̐ݒ菈��
	ABILITY GetAbility(void) const;				// �\�͂̎擾����
	void ResetAbility(void);					// �\�͂̃��Z�b�g����
	void SetPossible(const TYPE type, const bool bPossible);		// �\�󋵂̐ݒ菈��
	bool GetPossible(const TYPE type);								// �\�󋵂̎擾����

	// �ÓI�����o�֐�
	static CAbility* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Ability(CPlayer& player);		// �\�͑��쏈��
	void HoverJet(CPlayer& player);		// �z�o�[�W�F�b�g����
	void SkyDash(CPlayer& player);		// �W�F�b�g�_�b�V������
	void DashJump(CPlayer& player);		// �_�b�V���W�����v����
	void GroundQuake(CPlayer& player);	// �O���E���h�N�G�C�N����

	void PossibleProcess(CPlayer& player);			// �\�󋵔��菈��

	void SearchVertex(const D3DXVECTOR3& pos);		// �N���n�ʂ̒��_�̒T������

	// �����o�ϐ�
	CElevation *m_pElev;				// �N���n�ʂ̃|�C���^

	ABILITY m_ability;					// �\��
	int m_aAblCount[TYPE_MAX];			// �\�̓J�E���g
	bool m_aPossible[TYPE_MAX];			// �\�͂̎g�p��
};

#endif