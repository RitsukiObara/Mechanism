//===================================
//
// �R���{�̐����~�w�b�_�[[combo_circle.h]
// Author ��������
//
//===================================
#ifndef _COMBO_CIRCLE_H_
#define _COMBO_CIRCLE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectDonut2D.h"

//-----------------------------------
// �N���X��`(�R���{�̐����~)
//-----------------------------------
class CComboCircle : public CDonut2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CComboCircle();			// �R���X�g���N�^
	~CComboCircle();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const float fSize, const float fDist, const int nDivi);					// ���̐ݒ菈��

	void ResetNumVtx(void);		// ���_�̃��Z�b�g����

	// �Z�b�g�E�Q�b�g�֌W
	void SetEnd(const bool bEnd);		// �I���󋵂̐ݒ菈��
	bool GetEnd(void);					// �I���󋵂̎擾����

	// �ÓI�����o�֐�
	static CComboCircle* Create(const D3DXVECTOR3& pos, const float fSize, const float fDist, const int nDivi);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nVtx;			// ���_��
	bool m_bEnd;		// �I����
};

#endif