//===================================
//
// �}�L�i���w�b�_�[[macchina.h]
// Author ��������
//
//===================================
#ifndef _MACCHINA_H_				// ���̃}�N����`������Ă��Ȃ�������
#define _MACCHINA_H_				// 2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�}�L�i��)
//-----------------------------------
class CMacchina : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ���
		STATE_REDUCE,		// �k�����
		STATE_EXPANSE,		// �L�я��
		STATE_EJECT,		// �r�o���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CMacchina();			// �R���X�g���N�^
	~CMacchina();			// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CMacchina* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CMacchina* pNext);	// ��̃|�C���^�̐ݒ菈��
	CMacchina* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CMacchina* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);			// �q�b�g����

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	bool GetCollision(void);					// �����蔻��̎擾����

	// �ÓI�����o�֐�
	static CMacchina* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void NoneRescale(void);		// �ʏ��Ԃ̊g�嗦�̕ω�����
	void ReduceScale(void);		// �k����Ԃ̊g�嗦�̕ω�����
	void ExpanseScale(void);	// �L�я�Ԃ̊g�嗦�̕ω�����
	void EjectScale(void);		// �r�o��Ԃ̊g�嗦�̕ω�����

	// �����o�ϐ�
	D3DXVECTOR3 m_scaleDest;	// �ړI�̊g�嗦
	STATE m_state;				// ���
	int m_nStateCount;			// ��ԃJ�E���g
	bool m_bCollision;			// �����蔻��̗L��

	// ���X�g�\���֌W
	CMacchina* m_pPrev;	// �O�ւ̃|�C���^
	CMacchina* m_pNext;	// ���ւ̃|�C���^
};

#endif