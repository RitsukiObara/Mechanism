// �f�o�b�O��
#ifdef _DEBUG
//============================================
//
// �G�f�B�b�g�w�b�_�[[edit.h]
// Author�F��������
//
//============================================
#ifndef _EDIT_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _EDIT_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "model.h"
#include "enemy.h"

//--------------------------------------------
// �N���X��`(�G�f�B�b�g)
//--------------------------------------------
class CEdit : public CModel
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_ITEM = 0,		// �A�C�e��
		TYPE_MACCHINA,		// �}�L�i��
		TYPE_ENEMY,			// �G
		TYPE_TABLE,			// ��
		TYPE_AIRPLANE,		// ��s�@
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CEdit();				// �R���X�g���N�^
	~CEdit();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);			// ���̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CEdit* Create(const D3DXVECTOR3& pos);	// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void ItemProcess(void);		// �A�C�e���G�f�B�b�g�̏���
	void MacchinaProcess(void);	// �}�L�i���G�f�B�b�g�̏���
	void EnemyProcess(void);	// �G�G�f�B�b�g�̏���

	void SetMaccina(void);		// �}�L�i���̐ݒ菈��

	void MoveInput(void);		// �ړ��̃C���v�b�g����
	void AdjustMoveInput(void);	// �������ړ��̃C���v�b�g����
	void Move(void);			// �ړ�����
	void Type(void);			// ��ސݒ菈��
	void Front(void);			// ���s�ݒ菈��
	void Set(void);				// �ݒ菈��
	void Delete(void);			// ��������

	// ��������
	void DeleteItem(void);		// �A�C�e���̏�������
	void DeleteMacchina(void);	// �}�L�i���̏�������
	void DeleteEnemy(void);		// �G�̏�������
	void DeleteTable(void);		// ��̏�������
	void DeleteAirplane(void);	// ��s�@�̏�������

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
	TYPE m_type;				// ���
	CEnemy::TYPE m_enemyType;	// �G�̎��
	float m_fAddDepth;			// �ǉ��̉��s
	bool m_bFront;				// ���s��
	bool m_bAirplaneFront;		// ��s�@�̌����̏�
};

#endif

#endif