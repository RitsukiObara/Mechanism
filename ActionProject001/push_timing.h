//============================================
//
// �����^�C�~���O�\���w�b�_�[[push_timing.h]
// Author�F��������
//
//============================================
#ifndef _PUSH_TIMING_H_			//���̃}�N����`������Ă��Ȃ�������
#define _PUSH_TIMING_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "objectbillboard.h"

//--------------------------------------------
// �N���X(�����^�C�~���O�N���X)
//--------------------------------------------
class CPushTiming : public CBillboardAnim
{
public:			// �N�ł��A�N�Z�X�ł���

	CPushTiming();			// �R���X�g���N�^
	~CPushTiming();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// �ݒ菈��

	// �ÓI�����o�֐�
	static CPushTiming* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	bool m_bGamePad;		// �Q�[���p�b�h��
};

#endif