//===================================
//
// �l�W�w�b�_�[[screw.h]
// Author ��������
//
//===================================
#ifndef _SCREW_H_
#define _SCREW_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(��s�D)
//-----------------------------------
class CScrew : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CScrew();					// �R���X�g���N�^
	~CScrew();					// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CScrew* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CScrew* pNext);	// ��̃|�C���^�̐ݒ菈��
	CScrew* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CScrew* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(const D3DXVECTOR3& pos);					// �q�b�g����

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CScrew* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Cycle(void);		// ��]����

	// ���X�g�\���֌W
	CScrew* m_pPrev;	// �O�ւ̃|�C���^
	CScrew* m_pNext;	// ���ւ̃|�C���^
};

#endif