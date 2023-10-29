//============================================
//
// �U������w�b�_�[[turn.h]
// Author�F��������
//
//============================================
#ifndef _TURN_H_			//���̃}�N����`������Ă��Ȃ�������
#define _TURN_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "objectbillboard.h"

//--------------------------------------------
// �N���X(�U������N���X)
//--------------------------------------------
class CTurn : public CBillboardAnim
{
public:			// �N�ł��A�N�Z�X�ł���

	CTurn();				// �R���X�g���N�^
	~CTurn();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const bool bRight);				// �ݒ菈��

	// �ÓI�����o�֐�
	static CTurn* Create(const D3DXVECTOR3& pos, const bool bRight);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nLife;			// ����
	bool m_bRight;			// �E������
};

#endif