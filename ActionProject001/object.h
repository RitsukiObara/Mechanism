//============================================
//
// �I�u�W�F�N�g�w�b�_�[[object.h]
// Author�F��������
//
//============================================
#ifndef _OBJECT_H_		//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �N���X(�I�u�W�F�N�g�N���X)
//--------------------------------------------
class CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// ���
	enum TYPE
	{
		TYPE_NONE = 0,			// ����
		TYPE_PLAYER,			// �v���C���[
		TYPE_AIRPLANE,			// ��s�@
		TYPE_TIME,				// ����
		TYPE_SHADOW,			// �e
		TYPE_SCORE,				// �X�R�A
		TYPE_GAMESCORE,			// �Q�[���X�R�A
		TYPE_PAUSE,				// �|�[�Y
		TYPE_3DPOLYGON,			// 3D�|���S��
		TYPE_CHARA,				// �L�����N�^�[
		TYPE_MESH,				// ���b�V��
		TYPE_FIELD,				// �t�B�[���h
		TYPE_LOGOMARK,			// ���S�}�[�N
		TYPE_LOCUS,				// �c��
		TYPE_EFFECT,			// �G�t�F�N�g
		TYPE_SCREW,				// �l�W
		TYPE_COLLPOLY,			// �����蔻��|���S��
		TYPE_DESTRUCTION,		// ���j
		TYPE_ABILITYUI,			// �\��UI
		TYPE_ENEMY,				// �G
		TYPE_FRACTION,			// �j��
		TYPE_NEWRECORD,			// �V�L�^
		TYPE_SCREWUI,			// �l�W��UI
		TYPE_COMBO,				// �R���{
		TYPE_VIVLIO,			// �r�u���I��
		TYPE_RIPPLE,			// �g��
		TYPE_GOAL,				// �S�[��
		TYPE_BONUSCOMBO,		// �{�[�i�X�R���{
		TYPE_TITLELOGO,			// �^�C�g�����S
		TYPE_EDIT,				// �G�f�B�b�g
		TYPE_SKYBOX,			// �X�J�C�{�b�N�X
		TYPE_STUN,				// �C�≉�o
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	// �D�揇��
	enum PRIORITY
	{
		PRIORITY_BG = 0,			// �w�i�֌W
		PRIORITY_BLOCK,				// �u���b�N�E��Q���n
		PRIORITY_EFFECT,			// �G�t�F�N�g�n
		PRIORITY_SHADOW,			// �e�֌W
		PRIORITY_ENTITY,			// �G�E�A�C�e���֌W
		PRIORITY_PLAYER,			// �v���C���[�֌W
		PRIORITY_UI,				// UI�֌W
		PRIORITY_PAUSE,				// �|�[�Y(��ΑO�ɏo�����)
		PRIORITY_MAX				// ���̗񋓌^�̑���
	};

	CObject();													// �R���X�g���N�^
	CObject(TYPE type, PRIORITY priority = PRIORITY_ENTITY);	// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CObject();											// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void) = 0;	// ����������
	virtual void Uninit(void) = 0;	// �I������
	virtual void Update(void) = 0;	// �X�V����
	virtual void Draw(void) = 0;	// �`�揈��

	// �Z�b�g�E�Q�b�g�֌W
	static CObject* GetTop(PRIORITY priority);		// �I�u�W�F�N�g�̎擾����

	CObject* GetNext(void);				// ���̃|�C���^�̎擾����

	void SetType(const TYPE type);		// ��ނ̐ݒ菈��
	TYPE GetType(void) const;			// ��ނ̎擾����

	// �ÓI�����o�֐�
	static void ReleaseAll(void);		// �S�Ă̔j������
	static void UpdateAll(void);		// �S�Ă̍X�V����
	static void DrawAll(void);			// �S�Ă̕`�揈��

	static void AnyAllClear(const TYPE type);		// �ėp�I�ȑS��������
	static void AnyAllClear(const PRIORITY priority, const TYPE type);		// �ėp�I�ȑS��������
	static void DeathDecision(const int nCnt);		// ���S���ʏ���

	static void UpdateNormal(void);		// �ʏ�X�V����
	static void UpdateGame(void);		// �Q�[���̍X�V����

	static void DrawNormal(void);		// �ʏ�`�揈��
	static void DrawGame(void);			// �Q�[���̕`�揈��

protected:		// �����Ɣh���N���X�������A�N�Z�X�ł���

	// �����o�֐�
	void Release(void);					// �j������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Death(void);					// ���S����

	// �����o�ϐ�
	CObject* m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_type;						// ���
	PRIORITY m_priority;				// �I�u�W�F�N�g�̗D�揇��
	bool m_bDeath;						// ���S�t���O
	
	// �ÓI�����o�ϐ�
	static CObject* m_apTop[PRIORITY_MAX];				// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject* m_apCur[PRIORITY_MAX];				// �Ō���I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;								// �I�u�W�F�N�g�̑���
};

#endif