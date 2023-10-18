//===================================
//
// ��w�b�_�[[table.h]
// Author ��������
//
//===================================
#ifndef _TABLE_H_
#define _TABLE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(��)
//-----------------------------------
class CTable : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CTable();					// �R���X�g���N�^
	~CTable();					// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CTable* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CTable* pNext);	// ��̃|�C���^�̐ݒ菈��
	CTable* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CTable* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTable* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�

	// ���X�g�\���֌W
	CTable* m_pPrev;	// �O�ւ̃|�C���^
	CTable* m_pNext;	// ���ւ̃|�C���^
};

#endif