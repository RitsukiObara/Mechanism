//===================================
//
// �`���[�g���A���ӂ������w�b�_�[[tutorial.h]
// Author ��������
//
//===================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"
#include "pork.h"

//-----------------------------------
// �N���X��`(�`���[�g���A��)
//-----------------------------------
class CTutorial : public CBillboard
{
public:			// �N�ł��A�N�Z�X�ł���

	CTutorial();			// �R���X�g���N�^
	~CTutorial();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const CPork::TYPE type);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTutorial* Create(const D3DXVECTOR3& pos, const CPork::TYPE type);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CPork::TYPE m_type;		// ���
};

#endif