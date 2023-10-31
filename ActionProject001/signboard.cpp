//===========================================
//
// �Ŕ̃��C������[signboard.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "signboard.h"
#include "useful.h"

// �}�N����`
#define SHIFT_POS		(D3DXVECTOR3(80.0f, 190.0f, 0.0f))			// ���炷�ʒu

//==============================
// �R���X�g���N�^
//==============================
CSignBoard::CSignBoard() : CModel(CObject::TYPE_SIGNBOARD, CObject::PRIORITY_ENTITY)
{

}

//==============================
// �f�X�g���N�^
//==============================
CSignBoard::~CSignBoard()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CSignBoard::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CSignBoard::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CSignBoard::Update(void)
{

}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CSignBoard::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CSignBoard::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos + SHIFT_POS);				// �ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetPosOld(pos);							// �O��̈ʒu
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_SIGNBOARD);	// ���f���̏��
}

//=======================================
// ��������
//=======================================
CSignBoard* CSignBoard::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSignBoard* pSign = nullptr;	// �C���X�^���X�𐶐�

	if (pSign == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pSign = new CSignBoard;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSign != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pSign->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSign->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �Ŕ̃|�C���^��Ԃ�
	return pSign;
}