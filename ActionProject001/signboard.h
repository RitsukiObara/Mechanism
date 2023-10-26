//===================================
//
// �Ŕw�b�_�[[signboard.h]
// Author ��������
//
//===================================
#ifndef _SIGNBOARD_H_
#define _SIGNBOARD_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�Ŕ�)
//-----------------------------------
class CSignBoard : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CSignBoard();				// �R���X�g���N�^
	~CSignBoard();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CSignBoard* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif