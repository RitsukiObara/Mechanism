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
		ABILITY_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_HOVER = 0,			// �z�o�[�W�F�b�g
		TYPE_JETDASH,			// �W�F�b�g�_�b�V��
		TYPE_GROUNDQUAKE,		// �O���E���h�N�G�C�N
		TYPE_STARDROP,			// �X�^�[�h���b�v
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
	void SetAbility(const ABILITY ability);		// �\�͂̐ݒ菈��
	ABILITY GetAbility(void) const;				// �\�͂̎擾����
	void SetPossible(const TYPE type, const bool bPossible);		// �\�󋵂̐ݒ菈��
	bool GetPossible(const TYPE type);								// �\�󋵂̎擾����
	void SetInterval(const TYPE type, const int nCount);			// �Ԋu�J�E���g�̐ݒ菈��
	int GetInterval(const TYPE type) const;							// �Ԋu�J�E���g�̎擾����

	// �ÓI�����o�֐�
	static CAbility* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void HoverJet(CPlayer& player);		// �z�o�[�W�F�b�g����
	void SkyDash(CPlayer& player);		// �W�F�b�g�_�b�V������

	void Interval(void);				// �Ԋu�J�E���g����

	// �����o�ϐ�
	ABILITY m_ability;					// �\��
	int m_nAblCount;					// �\�̓J�E���g
	int m_aIntervalCount[TYPE_MAX];		// �Ԋu�J�E���g
	bool m_aPossible[TYPE_MAX];			// �\�͂̎g�p��
};

#endif