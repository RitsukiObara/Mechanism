//===========================================
//
// ��s�@�̃��C������[airplane.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "airplane.h"
#include "airplane_manager.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CAirplane::CAirplane() : CModel(CObject::TYPE_AIRPLANE, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;		// �O�̃A�E�g�{�[���ւ̃|�C���^
	m_pNext = nullptr;		// ���̃A�E�g�{�[���ւ̃|�C���^

	if (CAirplaneManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CAirplaneManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CAirplane::~CAirplane()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CAirplane::SetPrev(CAirplane* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CAirplane::SetNext(CAirplane* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CAirplane* CAirplane::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CAirplane* CAirplane::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CAirplane::Init(void)
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
void CAirplane::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CAirplaneManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CAirplaneManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CAirplane::Update(void)
{

}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CAirplane::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CAirplane::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(rot);								// ����
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// �g�嗦
	SetFileData(CXFile::TYPE_AIRPLANE);			// ���f���̏��
}

//=======================================
// ��������
//=======================================
CAirplane* CAirplane::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAirplane* pAirplane = nullptr;	// �C���X�^���X�𐶐�

	if (pAirplane == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pAirplane = new CAirplane;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pAirplane != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAirplane->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "��s�@�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pAirplane->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��s�@�̃|�C���^��Ԃ�
	return pAirplane;
}