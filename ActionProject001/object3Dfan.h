//===================================
//
// �I�u�W�F�N�g3D�t�@���w�b�_�[[object3Dfan.h]
// Author ��������
//
//===================================
#ifndef _OBJECT3DFAN_H_
#define _OBJECT3DFAN_H_

#include "object.h"

//--------------------------------------------
// �N���X(�I�u�W�F�N�g3D�N���X)
//--------------------------------------------
class CObject3DFan : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CObject3DFan();			// �R���X�g���N�^
	virtual ~CObject3DFan();		// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	//void BindTexture(int nIdx);				// �e�N�X�`���̊��蓖�ď���

	// ���_����n
	void SetVertex(void);						// ���_���̐ݒ�
	void SetVtxColor(const D3DXCOLOR& col);		// ���_�J���[�̐ݒ菈��

	// �ÓI�����o�֐�
	static CObject3DFan* Create(void);			// ��������

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X

	int m_nNumAngle;							// �p�x�̐�
	float m_fRadius;							// ���a
};

#endif