//===================================
//
// �V�L�^�w�b�_�[[new_record.h]
// Author ��������
//
//===================================
#ifndef _NEW_RECORD_H_			// ���̃}�N����`������Ă��Ȃ�������
#define _NEW_RECORD_H_			// 2�d�C���N���[�h�h�~�̃}�N����ݒ肷��

//-----------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------
#include "object2D.h"

//-----------------------------------
// �N���X��`(�V�L�^)
//-----------------------------------
class CNewRecord : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CNewRecord();		// �R���X�g���N�^
	~CNewRecord();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3 pos);			// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CNewRecord* Create(const D3DXVECTOR3 pos);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif