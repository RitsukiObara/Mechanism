//===========================================
//
// �l�W�̃��C������[screw.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "screw.h"
#include "screw_manager.h"
#include "useful.h"

#include "Particle.h"
#include "destruction.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define INIT_ROT		(D3DXVECTOR3(0.0f,0.0f,0.7f))			// �l�W�̌���
#define ROT_MOVE		(0.04f)									// �l�W�̌����̈ړ���
#define DSTR_SIZE		(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// �򖗉��o�̃T�C�Y
#define DSTR_COL		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f))		// �򖗉��o�̐F
#define DSTR_LIFE		(6)										// �򖗉��o�̎���

//==============================
// �R���X�g���N�^
//==============================
CScrew::CScrew() : CModel(CObject::TYPE_SCREW, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;		// �O�̃|�C���^
	m_pNext = nullptr;		// ���̃|�C���^

	if (CScrewManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CScrewManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CScrew::~CScrew()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CScrew::SetPrev(CScrew* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CScrew::SetNext(CScrew* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CScrew* CScrew::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CScrew* CScrew::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CScrew::Init(void)
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
void CScrew::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CScrewManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CScrewManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CScrew::Update(void)
{
	// ��]����
	Cycle();
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CScrew::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// �q�b�g����
//=====================================
void CScrew::Hit(const D3DXVECTOR3& pos)
{
	// �I������
	Uninit();

	// �p�[�e�B�N���̐���
	CParticle::Create(pos, CParticle::TYPE_ITEMGET);

	// ���j�̐���
	CDestruction::Create(pos, DSTR_SIZE, DSTR_COL, CDestruction::TYPE_AIRY, DSTR_LIFE);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CScrew::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(INIT_ROT);							// ����
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// �g�嗦
	SetFileData(CXFile::TYPE_SCREW);			// ���f���̏��
}

//=======================================
// ��������
//=======================================
CScrew* CScrew::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CScrew* pScrew = nullptr;	// �C���X�^���X�𐶐�

	if (pScrew == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pScrew = new CScrew;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pScrew != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pScrew->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�l�W�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pScrew->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �l�W�̃|�C���^��Ԃ�
	return pScrew;
}

//=======================================
// ��]����
//=======================================
void CScrew::Cycle(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();		// �����̐ݒ菈��

	// ���������Z����
	rot.y += ROT_MOVE;

	// ������K�p����
	SetRot(rot);
}