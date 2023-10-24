//===================================
//
// ��s�D�w�b�_�[[airplane.h]
// Author ��������
//
//===================================
#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(��s�D)
//-----------------------------------
class CAirplane : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CAirplane();					// �R���X�g���N�^
	~CAirplane();					// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CAirplane* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CAirplane* pNext);	// ��̃|�C���^�̐ݒ菈��
	CAirplane* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CAirplane* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const bool bFront);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	bool GetFront(void) const;		// �O��󋵂̎擾����

	// �ÓI�����o�֐�
	static CAirplane* Create(const D3DXVECTOR3& pos, const bool bFront);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	bool m_bFront;		// �O���

	// ���X�g�\���֌W
	CAirplane* m_pPrev;	// �O�ւ̃|�C���^
	CAirplane* m_pNext;	// ���ւ̃|�C���^
};

#endif