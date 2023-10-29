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
#include "objectElevation.h"
#include "elevation_manager.h"
#include "stun.h"

#include "itocan.h"
#include "machidori.h"
#include "garrejante.h"

// �}�N����`
#define GRAVITY			(0.5f)				// �d��
#define SMASH_MOVE		(8.5f)				// ������΂��ړ���
#define SMASH_JUMP		(16.0f)				// ������΂��W�����v��
#define SMASH_ADD_RIGHT	(14.0f)				// �E�ɐ�����΂��ǉ��̈ړ���
#define SMASH_ADD_LEFT	(12.0f)				// ���ɐ�����΂��ǉ��̈ړ���

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
	m_pStun = nullptr;				// �C�≉�o�̃|�C���^
	m_posInit = NONE_D3DXVECTOR3;	// �����ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;	// �����蔻��̃T�C�Y
	m_type = TYPE_ITOCAN;			// ���
	m_nStunCount = 0;				// �C��J�E���g
	m_bStep = false;				// ���݂���
	m_bCollision = true;			// �����蔻���ʂ邩�ǂ���
	m_bStun = false;				// �C���
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
	m_pStun = nullptr;				// �C�≉�o�̃|�C���^
	m_posInit = NONE_D3DXVECTOR3;	// �����ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;	// �����蔻��̃T�C�Y
	m_type = TYPE_ITOCAN;			// ���
	m_nStunCount = 0;				// �C��J�E���g
	m_bStep = false;				// ���݂���
	m_bCollision = true;			// �����蔻���ʂ邩�ǂ���
	m_bStun = false;				// �C���

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CEnemy::Uninit(void)
{
	if (m_pStun != nullptr)
	{ // �C�≉�o�� NULL ����Ȃ��ꍇ

		// �I������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}

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
	if (m_pStun != nullptr)
	{ // �C�≉�o�� NULL ����Ȃ��ꍇ

		// �I������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}

	// �C��󋵂� false �ɂ���
	m_bStun = false;

	// �C��J�E���g������������
	m_nStunCount = 0;
}

//=====================================
// ������уq�b�g����
//=====================================
void CEnemy::SmashHit(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posCamera = CManager::Get()->GetCamera()->GetPosV();		// ���_�̈ʒu���擾����
	CPlayer* player = CPlayer::Get();										// �v���C���[�̏����擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	D3DXVECTOR3 rot = GetRot();		// �������擾����
	float fSmashRot;				// ������΂�����
	
	// ������΂�������ݒ肷��
	fSmashRot = atan2f(posCamera.x - pos.x, posCamera.z - pos.z);

	// ������0.0f�ɂ���
	rot.y = 0.0f;

	if (player->IsRight() == true)
	{ // �E�����̏ꍇ

		// ������ݒ肷��
		m_move.x = sinf(fSmashRot) * SMASH_MOVE + sinf(player->GetRot().y) * SMASH_ADD_RIGHT;
		m_move.y = SMASH_JUMP;
		m_move.z = cosf(fSmashRot) * SMASH_MOVE;
	}
	else
	{ // ��L�ȊO

		// ������ݒ肷��
		m_move.x = sinf(fSmashRot) * SMASH_MOVE + sinf(player->GetRot().y) * SMASH_ADD_LEFT;
		m_move.y = SMASH_JUMP;
		m_move.z = cosf(fSmashRot) * SMASH_MOVE;
	}

	// ����K�p����
	SetRot(rot);		// ����

	if (m_pStun != nullptr)
	{ // �C�≉�o�� NULL ����Ȃ��ꍇ

		// �I������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}

	// �C��󋵂� false �ɂ���
	m_bStun = false;

	// �C��J�E���g������������
	m_nStunCount = 0;
}

//=====================================
// �C��̃q�b�g����
//=====================================
void CEnemy::StunHit(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu

	if (m_pStun == nullptr)
	{ // �C��̏�� NULL �̏ꍇ

		// �C�≉�o�̐�������
		m_pStun = CStun::Create(D3DXVECTOR3(pos.x, pos.y + m_sizeColl.y, pos.z));
	}

	// �C��󋵂� true �ɂ���
	m_bStun = true;

	// �C��J�E���g������������
	m_nStunCount = 0;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CEnemy::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// �g�嗦

	// �S�Ă̒l��ݒ肷��
	m_posInit = pos;				// �����ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;	// �����蔻��̃T�C�Y
	m_type = type;					// ���
	m_nStunCount = 0;				// �C��J�E���g
	m_bStep = false;				// ���݂���
	m_bCollision = true;			// �����蔻���ʂ邩�ǂ���
	m_bStun = false;				// �C���
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
		case TYPE_ITOCAN:		// �C�g�L����

			// �C���X�^���X�𐶐�
			pEnemy = new CItocan;

			break;

		case TYPE_MACHIDORI:	// �}�V���h���[

			// �C���X�^���X�𐶐�
			pEnemy = new CMachidori;

			break;

		case TYPE_GARREJANTE:

			// �C���X�^���X�𐶐�
			pEnemy = new CGarrejante;

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

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEnemy->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G�̃|�C���^��Ԃ�
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
// �����蔻��̃T�C�Y�̐ݒ菈��
//=======================================
void CEnemy::SetCollSize(const D3DXVECTOR3& size)
{
	// �����蔻��̃T�C�Y��ݒ肷��
	m_sizeColl = size;
}

//=======================================
// �����蔻��̃T�C�Y�̎擾����
//=======================================
D3DXVECTOR3 CEnemy::GetCollSize(void) const
{
	// �����蔻��̃T�C�Y��Ԃ�
	return m_sizeColl;
}

//=======================================
// ��ނ̎擾����
//=======================================
CEnemy::TYPE CEnemy::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//=======================================
// �C��J�E���g�̐ݒ菈��
//=======================================
void CEnemy::SetStunCount(const int nCount)
{
	// �C��J�E���g��ݒ肷��
	m_nStunCount = nCount;
}

//=======================================
// �C��J�E���g�̎擾����
//=======================================
int CEnemy::GetStunCount(void) const
{
	// �C��J�E���g��Ԃ�
	return m_nStunCount;
}

//=======================================
// ���݂��󋵂̐ݒ菈��
//=======================================
void CEnemy::SetEnableStep(const bool bStep)
{
	// ���݂��󋵂�ݒ肷��
	m_bStep = bStep;
}

//=======================================
// ���݂��󋵂̎擾����
//=======================================
bool CEnemy::IsStep(void) const
{
	// ���݂��󋵂�Ԃ�
	return m_bStep;
}

//=======================================
// �C�≉�o�̎擾����
//=======================================
CStun* CEnemy::GetStun(void) const
{
	// �C�≉�o��Ԃ�
	return m_pStun;
}

//=======================================
// �C���Ԃ̏�������
//=======================================
void CEnemy::DeleteStun(void)
{
	if (m_pStun != nullptr)
	{ // �C��̏�Ԃ� NULL ����Ȃ��ꍇ

		// ���������������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}
}

//=======================================
// �����ʒu�̎擾����
//=======================================
D3DXVECTOR3 CEnemy::GetInitPos(void) const
{
	// �����ʒu��Ԃ�
	return m_posInit;
}

//=======================================
// �����蔻��󋵂̐ݒ菈��
//=======================================
void CEnemy::SetEnableCollision(const bool bColl)
{
	// �����蔻��󋵂�ݒ肷��
	m_bCollision = bColl;
}

//=======================================
// �����蔻��󋵂̎擾����
//=======================================
bool CEnemy::IsCollision(void) const
{
	// �����蔻���Ԃ�
	return m_bCollision;
}

//=======================================
// �C��󋵂̐ݒ菈��
//=======================================
void CEnemy::SetEnableStun(const bool bStun)
{
	// �C��󋵂�ݒ肷��
	m_bStun = bStun;
}

//=======================================
// �C��󋵂̎擾����
//=======================================
bool CEnemy::IsStun(void) const
{
	// �C��󋵂�Ԃ�
	return m_bStun;
}

//=======================================
// �d�͏���
//=======================================
void CEnemy::Gravity(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu���擾����

	// �d�͏���
	useful::Gravity(&m_move.y, pos, GRAVITY);

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �N���n�ʂ̓����蔻�菈��
//=======================================
bool CEnemy::ElevationCollision(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	float fHeight = 0.0f;					// ����
	bool bLand = false;						// ���n����

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

			// ���n�����t����
			bLand = true;
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);

	// ���n�����Ԃ�
	return bLand;
}

//=======================================
// �u���b�N�Ƃ̓����蔻��
//=======================================
bool CEnemy::BlockCollision(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu
	D3DXVECTOR3 posOld = GetPosOld();	// �O��̈ʒu
	bool bLand = false;					// ���n����

	// ���n������擾����
	bLand = collision::BlockCollision(&pos, posOld, m_sizeColl.x, m_sizeColl.y, false);

	// �ʒu��K�p������
	SetPos(pos);

	// ���n�����Ԃ�
	return bLand;
}

//=======================================
// ��Ƃ̓����蔻��
//=======================================
bool CEnemy::TableCollision(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu
	D3DXVECTOR3 posOld = GetPosOld();	// �O��̈ʒu
	bool bLand = false;					// ���n����

	// ���n������擾����
	bLand = collision::TableCollision(&pos, posOld, m_sizeColl.x, m_sizeColl.z);

	// �ʒu��K�p������
	SetPos(pos);

	// ���n�����Ԃ�
	return bLand;
}