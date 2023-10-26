//===================================
//
// �K���W�����e�w�b�_�[[garrejante.h]
// Author ��������
//
//===================================
#ifndef _GARREJANTE_H_
#define _GARREJANTE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "enemy.h"

//-----------------------------------
// �N���X��`(�K���W�����e)
//-----------------------------------
class CGarrejante : public CEnemy
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ���
		STATE_DEATH,		// ���S���
		STATE_SMASH,		// ������я��
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CGarrejante();			// �R���X�g���N�^
	~CGarrejante();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);			// �q�b�g����
	void SmashHit(void);	// ������уq�b�g����
	void StunHit(void);		// �C��̃q�b�g����
	void SetData(const D3DXVECTOR3& pos, const TYPE type);				// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Smash(void);				// ������я�ԏ���
	void TableLand(void);			// ��̒��n���菈��

	// �����o�ϐ�
	STATE m_state;			// ���
	int m_nStateCount;		// ��ԃJ�E���g
};

#endif