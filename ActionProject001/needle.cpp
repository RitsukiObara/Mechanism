//===========================================
//
// ���̃��C������[needle.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "needle.h"
#include "needle_manager.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CNeedle::CNeedle() : CModel(CObject::TYPE_PORK, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;		// �O�ւ̃|�C���^
	m_pNext = nullptr;		// ���ւ̃|�C���^

	if (CNeedleManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CNeedleManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CNeedle::~CNeedle()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CNeedle::SetPrev(CNeedle* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CNeedle::SetNext(CNeedle* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CNeedle* CNeedle::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CNeedle* CNeedle::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CNeedle::Init(void)
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
void CNeedle::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CNeedleManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CNeedleManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CNeedle::Update(void)
{

}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CNeedle::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CNeedle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3 rot)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(rot);							// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_NEEDLE);		// ���f���̏��
}

//=======================================
// ��������
//=======================================
CNeedle* CNeedle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3 rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CNeedle* pPork = nullptr;	// �C���X�^���X�𐶐�

	if (pPork == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pPork = new CNeedle;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPork != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPork->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPork->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �|�[�N�̃|�C���^��Ԃ�
	return pPork;
}