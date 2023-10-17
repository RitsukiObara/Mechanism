//============================================
//
// �v���C���[�w�b�_�[[player.h]
// Author�F��������
//
//============================================
#ifndef _PLAYER_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "character.h"
#include "scene.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMotion;				// ���[�V����
class CPlayerAct;			// �v���C���[�̍s��
class CAbility;				// �\��
class CAbilityUI;			// �\��UI
class CScrewUI;				// �l�WUI

//--------------------------------------------
// �N���X(�v���C���[�N���X)
//--------------------------------------------
class CPlayer : public CCharacter
{
public:			// �N�ł��A�N�Z�X�ł���

	//************************************************************
	//	�񋓌^��`(���[�V�����̎��)
	//************************************************************
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ҋ@
		MOTIONTYPE_MOVE,			// �ړ�
		MOTIONTYPE_JUMP,			// �W�����v
		MOTIONTYPE_WALLFRIC,		// �ǎC����
		MOTIONTYPE_WALLSTEPIN,		// ���ݍ���
		MOTIONTYPE_WALLKICK,		// �ǃL�b�N
		MOTIONTYPE_BIGJUMP,			// ���W�����v
		MOTIONTYPE_CLIFFCATCH,		// �R�߂܂�
		MOTIONTYPE_CLIFFUP,			// �R�オ��
		MOTIONTYPE_HANGING,			// �Ԃ牺����
		MOTIONTYPE_LANDING,			// ���n���[�V����
		MOTIONTYPE_LAMPJUMP,		// �X���W�����v
		MOTIONTYPE_POLEDOWN,		// �|�[������
		MOTIONTYPE_FALL,			// ����
		MOTIONTYPE_START,			// �X�^�[�g�O
		MOTIONTYPE_ASCENT,			// �悶�o��
		MOTIONTYPE_ATTACK,			// �U��
		MOTIONTYPE_MAX				// ���̗񋓂̑���
	};

	// �񋓌^��`(���[�h)
	enum MODE
	{
		MODE_ACROBAT = 0,			// �A�N���o�b�g���[�h
		MODE_MASSIVE,				// �}�b�V�u���[�h
		MODE_REBOOT,				// ���u�[�g�h���C�u���[�h
		MODE_MAX					// ���̗񋓌^�̑���
	};

	CPlayer();				// �R���X�g���N�^
	~CPlayer();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);			// �q�b�g����
	void StepHit(void);		// ���݂����̏���
	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetMove(const D3DXVECTOR3& move);		// �ړ��ʂ̐ݒ菈��
	D3DXVECTOR3 GetMove(void) const;			// �ړ��ʂ̎擾����
	void SetRotDest(const D3DXVECTOR3& rot);	// �ڕW�̌����̐ݒ菈��
	D3DXVECTOR3 GetRotDest(void) const;			// �ڕW�̌����̎擾����
	void SetMode(const MODE type);				// ���[�h�̐ݒ菈��
	MODE GetMode(void) const;					// ���[�h�̎擾����
	void SetSpeed(float fSpeed);				// ���x�̐ݒ菈��
	float GetSpeed(void) const;					// ���x�̎擾����
	void SetEnableMove(bool bMove);				// �ړ��󋵂̐ݒ菈��
	bool IsMove(void) const;					// �ړ��󋵂̎擾����
	void SetEnableRight(bool bRight);			// �E�����󋵂̐ݒ菈��
	bool IsRight(void) const;					// �E�����󋵂̎擾����
	void SetEnableJump(bool bJump);				// �W�����v�󋵂̐ݒ菈��
	bool IsJump(void) const;					// �W�����v�󋵂̎擾����

	CMotion* GetMotion(void) const;				// ���[�V�����̏��̎擾����
	CPlayerAct* GetAction(void) const;			// �A�N�V�����̏��̎擾����
	CAbility* GetAbility(void) const;			// �\�͂̏��̎擾����
	CAbilityUI* GetAbilityUI(void) const;		// �\��UI�̏��̎擾����
	CScrewUI* GetScrewUI(void) const;			// �l�WUI�̏��̎擾����

	// �ÓI�����o�֐�
	static CPlayer* Get(void);					// �擾����
	static CPlayer* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void ElevationCollision(void);	// �N���n�ʂ̓����蔻�菈��
	void SetNone(void);				// ���n���̒ʏ��Ԃ̐ݒ菈��
	void CollisionMagicWall(void);	// �ړ���������

	// �����o�ϐ�
	CMotion* m_pMotion;				// ���[�V�����̏��
	CPlayerAct* m_pAction;			// �v���C���[�̍s���̏��
	CAbility* m_pAbility;			// �\�͂̏��
	CAbilityUI* m_pAbilityUI;		// �\��UI�̏��
	CScrewUI* m_pScrewUI;			// �l�WUI�̏��

	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
	MODE m_mode;					// ���[�h
	int m_nShadowIdx;				// �e�̃C���f�b�N�X
	float m_fSpeed;					// ���x
	bool m_bMove;					// �ړ���
	bool m_bRight;					// �E������
	bool m_bJump;					// �W�����v��

	// �ÓI�����o�ϐ�
	static CPlayer* m_pPlayer;		// �v���C���[�̃|�C���^
};

#endif