//===================================
//
// ���w�b�_�[[needle.h]
// Author ��������
//
//===================================
#ifndef _NEEDLE_H_
#define _NEEDLE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CNeedle;		// ��

//-----------------------------------
// �N���X��`(��)
//-----------------------------------
class CNeedle : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CNeedle();				// �R���X�g���N�^
	~CNeedle();				// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CNeedle* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CNeedle* pNext);	// ��̃|�C���^�̐ݒ菈��
	CNeedle* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CNeedle* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3 rot);			// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CNeedle* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3 rot);	// ��������

private:		// ���������A�N�Z�X�ł���

	// ���X�g�\���֌W
	CNeedle* m_pPrev;	// �O�ւ̃|�C���^
	CNeedle* m_pNext;	// ���ւ̃|�C���^
};

#endif