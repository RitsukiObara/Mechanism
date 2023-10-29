//===================================
//
// �u���b�N�w�b�_�[[block.h]
// Author ��������
//
//===================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�u���b�N)
//-----------------------------------
class CBlock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CBlock();				// �R���X�g���N�^
	~CBlock();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CBlock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif