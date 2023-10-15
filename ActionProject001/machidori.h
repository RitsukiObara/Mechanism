//===================================
//
// �}�V���h���[�w�b�_�[[machidori.h]
// Author ��������
//
//===================================
#ifndef _MACHIDORI_H_
#define _MACHIDORI_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "enemy.h"

//-----------------------------------
// �N���X��`(�}�V���h���[)
//-----------------------------------
class CMachidori : public CEnemy
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_FLY = 0,		// ���V���
		STATE_STANDBY,		// �X�^���o�C���
		STATE_ATTACK,		// �U�����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CMachidori();			// �R���X�g���N�^
	~CMachidori();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);			// �q�b�g����
	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void CheckPlayer(void);	// �v���C���[�̔��f����
	void Move(void);		// �ړ�����
	void Height(void);		// �����ݒ菈��
	void Elevation(void);	// �N���n�ʂ̓����蔻��
	void SetRightOld(void);	// �O��̍��E�󋵂̐ݒ菈��

	// �����o�ϐ�
	STATE m_state;			// ���
	float m_fCurveRot;		// �J�[�u�p����
	bool m_bRight;			// �E������
};

#endif