//===========================================
//
// �C�g�L�����̃��C������[itocan.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "machidori.h"
#include "useful.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "player.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define MOVE_DISTANCE			(1400.0f)								// �ړ����鋗��
#define COLLISION_SIZE			(D3DXVECTOR3(40.0f, 93.0f, 44.0f))		// �����蔻��̃T�C�Y
#define ROT_MOVE				(0.05f)									// �����̈ړ���
#define ADD_HEIGHT				(300.0f)								// �ǉ����鍂��
#define CURVE_HEIGHT			(50.0f)									// �������݂̍�

//==============================
// �R���X�g���N�^
//==============================
CMachidori::CMachidori() : CEnemy(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_state = STATE_FLY;	// ���
	m_fCurveRot = 0.0f;		// �J�[�u�p����
	m_bRight = true;		// �O��̉E������
}

//==============================
// �f�X�g���N�^
//==============================
CMachidori::~CMachidori()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CMachidori::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_state = STATE_FLY;	// ���
	m_fCurveRot = 0.0f;		// �J�[�u�p����
	m_bRight = true;		// �O��̉E������

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CMachidori::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CMachidori::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	switch (m_state)
	{
	case STATE_FLY:

		// �N���n�ʂ̓����蔻��
		Elevation();

		// �����̐ݒ菈��
		Height();

		// �v���C���[�̔��菈��
		CheckPlayer();

		// �ړ�����
		Move();

		break;

	case STATE_STANDBY:

		break;

	case STATE_ATTACK:

		break;
	}
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CMachidori::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=====================================
// �q�b�g����
//=====================================
void CMachidori::Hit(void)
{

}

//=====================================
// ���̐ݒ菈��
//=====================================
void CMachidori::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	CEnemy::SetData(pos);

	// ���f���̏���ݒ肷��
	SetFileData(CXFile::TYPE_MACHIDORI);

	// �S�Ă̒l��ݒ肷��
	m_state = STATE_FLY;	// ���
	m_fCurveRot = 0.0f;		// �J�[�u�p����

	// ���̐ݒ菈��
	SetEnableStep(true);			// ���݂�����ݒ�
	SetCollSize(COLLISION_SIZE);	// �����蔻��̃T�C�Y

	// �O��̍��E�󋵂̐ݒ菈��
	SetRightOld();
}

//=====================================
// �v���C���[�̔��f����
//=====================================
void CMachidori::CheckPlayer(void)
{
	if (CPlayer::Get() != nullptr)
	{ // �v���C���[�̏�񂪂���ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// �v���C���[�̈ʒu
		D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
		D3DXVECTOR3 move = GetMove();	// �ړ��ʂ��擾����

		if (posPlayer.x >= pos.x)
		{ // �v���C���[�̈ʒu�����g�����E�ɂ���ꍇ

			// ������ݒ肷��
			move.x = 2.0f;

			if (m_bRight == false)
			{ // �O�񂪍������̏ꍇ

				// �X�^���o�C��Ԃɂ���
				m_state = STATE_STANDBY;
			}
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			move.x = -2.0f;

			if (m_bRight == true)
			{ // �O�񂪉E�����̏ꍇ

				// �X�^���o�C��Ԃɂ���
				m_state = STATE_STANDBY;
			}
		}

		// �ړ��ʂ�K�p����
		SetMove(move);
	}
}

//=====================================
// �ړ�����
//=====================================
void CMachidori::Move(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();			// �ʒu���擾����
	D3DXVECTOR3 move = GetMove();		// �ړ��ʂ��擾����

	// �ʒu��ݒ肷��
	pos.x += move.x;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// �����ݒ菈��
//=====================================
void CMachidori::Height(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����

	// �J�[�u�p�̌��������Z����
	m_fCurveRot += ROT_MOVE;

	// �����̐��K��
	useful::RotNormalize(&m_fCurveRot);

	// �ʒu��ݒ肷��
	pos.y += sinf(m_fCurveRot) * CURVE_HEIGHT + ADD_HEIGHT;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// �N���n�ʂ̓����蔻��
//=====================================
void CMachidori::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	float fHeight = 0.0f;					// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		// ������ݒ肷��
		pos.y = fHeight;

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}

//=====================================
// �O��̍��E�󋵂̐ݒ菈��
//=====================================
void CMachidori::SetRightOld(void)
{
	if (CPlayer::Get() != nullptr)
	{ // �v���C���[�̏�񂪂���ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// �v���C���[�̈ʒu
		D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

		if (posPlayer.x >= pos.x)
		{ // �v���C���[�̈ʒu�����g�����E�ɂ���ꍇ

			// �E�ɐݒ肷��
			m_bRight = true;
		}
		else
		{ // ��L�ȊO

			// ���ɐݒ肷��
			m_bRight = false;
		}
	}
}