//===========================================
//
// �G�̃��C������[enemy.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "collision.h"
#include "useful.h"

#include "player.h"
#include "mesh_elevation.h"
#include "elevation_manager.h"

#include "itocan.h"

//==============================
// �R���X�g���N�^
//==============================
CEnemy::CEnemy() : CModel(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CEnemy::CEnemy(CObject::TYPE type, PRIORITY priority) : CModel(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �f�X�g���N�^
//==============================
CEnemy::~CEnemy()
{

}

//==============================
// �R���X�g���N�^�̔�
//==============================
void CEnemy::Box(void)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_pPrev = nullptr;				// �O�̃|�C���^
	m_pNext = nullptr;				// ���̃|�C���^

	if (CEnemyManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CEnemyManager::Get()->Regist(this);
	}
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CEnemy::SetPrev(CEnemy* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CEnemy::SetNext(CEnemy* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CEnemy* CEnemy::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CEnemy* CEnemy::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CEnemy::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;		// �ړ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CEnemy::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CEnemyManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CEnemyManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CEnemy::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// �q�b�g����
//=====================================
void CEnemy::Hit(void)
{

}

//=====================================
// ���̐ݒ菈��
//=====================================
void CEnemy::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// �g�嗦
	SetFileData(CXFile::TYPE_ITOCAN);			// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
}

//=======================================
// ��������
//=======================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEnemy* pEnemy = nullptr;	// �C���X�^���X�𐶐�

	if (pEnemy == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case TYPE_ITOCAN:

			// �C���X�^���X�𐶐�
			pEnemy = new CItocan;

			break;

		default:

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;

			break;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEnemy != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEnemy->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�l�W�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEnemy->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �l�W�̃|�C���^��Ԃ�
	return pEnemy;
}

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
void CEnemy::SetMove(const D3DXVECTOR3& move)
{
	// �ړ��ʂ�ݒ肷��
	m_move = move;
}

//=======================================
// �ړ��ʂ̎擾����
//=======================================
D3DXVECTOR3 CEnemy::GetMove(void) const
{
	// �ړ��ʂ�Ԃ�
	return m_move;
}

//=======================================
// �d�͏���
//=======================================
void CEnemy::Gravity(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu���擾����

	// �d�͏���
	useful::Gravity(&m_move.y, pos, 0.5f);

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �N���n�ʂ̓����蔻�菈��
//=======================================
void CEnemy::ElevationCollision(void)
{
	// ���[�J���ϐ��錾
	CMeshElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	float fHeight = 0.0f;					// ����

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