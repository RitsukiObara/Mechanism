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
#include "collision.h"
#include "objectElevation.h"
#include "elevation_manager.h"

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
	m_pPrev = nullptr;			// �O�̃|�C���^
	m_pNext = nullptr;			// ���̃|�C���^
	m_move = NONE_D3DXVECTOR3;	// �ړ���
	m_bGravity = false;			// �d�͏�
	m_bHit = true;				// �����蔻���

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

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;	// �ړ���
	m_bGravity = false;			// �d�͏�
	m_bHit = true;				// �����蔻���

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
	if(m_bGravity == true)
	{ // �d�͏󋵂� true �̏ꍇ

		// �d�͏���
		Gravity();
	}

	// ��]����
	Cycle();

	// �N���n�ʂ̓����蔻��
	Elevation();

	// ��Ƃ̓����蔻��
	Table();

	// �u���b�N�Ƃ̓����蔻��
	Block();
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
void CScrew::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const bool bGravity)
{
	// ���̐ݒ菈��
	SetPos(pos);						// �ʒu
	SetPosOld(pos);						// �O��̈ʒu
	SetRot(INIT_ROT);					// ����
	SetScale(NONE_SCALE);				// �g�嗦
	SetFileData(CXFile::TYPE_SCREW);	// ���f���̏��

	// �S�Ă̒l������������
	m_move = move;				// �ړ���
	m_bGravity = bGravity;		// �d�͏�

	if (m_bGravity == true)
	{ // �d�͏󋵂� true �̏ꍇ

		// �����蔻��󋵂�ݒ肷��
		m_bHit = false;				// �����蔻���
	}
	else
	{ // ��L�ȊO

		// �����蔻��󋵂�ݒ肷��
		m_bHit = true;				// �����蔻���
	}
}

//=======================================
// �����蔻��̎擾����
//=======================================
bool CScrew::IsHit(void) const
{
	// �����蔻��󋵂�Ԃ�
	return m_bHit;
}

//=======================================
// ��������
//=======================================
CScrew* CScrew::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const bool bGravity)
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

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pScrew != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pScrew->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pScrew->SetData(pos, move, bGravity);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �l�W�̃|�C���^��Ԃ�
	return pScrew;
}

//=======================================
// �d�͏���
//=======================================
void CScrew::Gravity(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	// �d�͏���
	useful::Gravity(&m_move.y, pos, 0.8f);

	if (m_move.y <= 0.0f)
	{ // �ړ��ʂ� 0.0f �ȉ��̏ꍇ

		// �q�b�g�󋵂� true �ɂ���
		m_bHit = true;
	}

	// �ʒu��K�p����
	SetPos(pos);
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

//=======================================
// �N���̓����蔻�菈��
//=======================================
void CScrew::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	float fHeight = 0.0f;			// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);
		
		if (pos.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight;

			// �d�͂�ݒ肷��
			m_move.y = 0.0f;
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}

//=======================================
// ��Ƃ̓����蔻�菈��
//=======================================
void CScrew::Table(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu
	D3DXVECTOR3 posOld = GetPosOld();	// �O��̈ʒu

	if (collision::TableCollision(&pos, posOld, GetFileData().collsize.x, GetFileData().collsize.z) == true)
	{ // ��Ƃ̓����蔻�肪 true �������ꍇ

		// �c�̈ړ��ʂ𖳂���
		m_move.y = 0.0f;
	}

	// �ʒu��K�p������
	SetPos(pos);
}

//=======================================
// �u���b�N�Ƃ̓����蔻�菈��
//=======================================
void CScrew::Block(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu
	D3DXVECTOR3 posOld = GetPosOld();	// �O��̈ʒu

	if (collision::BlockCollision(&pos, posOld, GetFileData().collsize.x, GetFileData().collsize.y, false, nullptr) == true)
	{ // ��Ƃ̓����蔻�肪 true �������ꍇ

		// �c�̈ړ��ʂ𖳂���
		m_move.y = 0.0f;
	}

	// �ʒu��K�p������
	SetPos(pos);
}