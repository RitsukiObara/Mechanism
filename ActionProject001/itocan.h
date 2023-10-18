//===================================
//
// �C�g�L�����w�b�_�[[itocan.h]
// Author ��������
//
//===================================
#ifndef _ITOCAN_H_
#define _ITOCAN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "enemy.h"

//-----------------------------------
// �N���X��`(�C�g�L����)
//-----------------------------------
class CItocan : public CEnemy
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_STOP = 0,			// ��~���
		STATE_MOVE,				// �ړ����
		STATE_DEATH,			// ���S���
		STATE_SMASH,			// ������я��
		STATE_MAX				// ���̗񋓌^�̑���
	};

	CItocan();					// �R���X�g���N�^
	~CItocan();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);			// �q�b�g����
	void SmashHit(void);	// ������уq�b�g����
	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void CheckPlayer(void);			// �v���C���[�̔��菈��
	void CheckState(void);			// ��Ԃ̔��菈��
	void Move(void);				// �ړ�����
	void RotMove(void);				// �����ړ�����
	void DeathScaling(void);		// ���S���̊g�嗦
	void Smash(void);				// ������я�ԏ���
	void TableLand(void);			// ��̒��n���菈��

	// �����o�ϐ�
	STATE m_state;					// ���
	int m_nStateCount;				// ��ԃJ�E���g
	float m_fRotDest;				// �ڕW�̌���
};

#endif