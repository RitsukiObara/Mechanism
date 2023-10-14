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
#include "renderer.h"
#include "itocan.h"
#include "collision.h"
#include "useful.h"

#include "player.h"
#include "debugproc.h"
#include "collpolygon.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define MOVE_DISTANCE		(1200.0f)							// �ړ����鋗��
#define MOVE				(D3DXVECTOR3(3.0f, 0.0f, 0.0f))		// �ړ���
#define CHECK_COUNT			(10)								// �`�F�b�N����J�E���g��

//==============================
// �R���X�g���N�^
//==============================
CItocan::CItocan() : CEnemy(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_state = STATE_STOP;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
}

//==============================
// �f�X�g���N�^
//==============================
CItocan::~CItocan()
{

}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CItocan::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	m_state = STATE_STOP;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CItocan::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CItocan::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	if (m_nStateCount % CHECK_COUNT == 0)
	{ // ���J�E���g���ɂȂ����ꍇ

		// �v���C���[�̔��菈��
		CheckPlayer();
	}

	// ��Ԃ̔��菈��
	CheckState();

	switch (m_state)
	{
	case STATE_STOP:		// ��~���

		break;

	case STATE_MOVE:		// �ړ����

		// �ړ�����
		Move();

		break;
	}

	// �d�͏���
	Gravity();

	// �N���n�ʂƂ̓����蔻��
	ElevationCollision();

	// ��ԃJ�E���g�����Z����
	m_nStateCount++;
}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CItocan::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=====================================
// �q�b�g����
//=====================================
void CItocan::Hit(void)
{

}

//=====================================
// ���̐ݒ菈��
//=====================================
void CItocan::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	CEnemy::SetData(pos);

	// �S�Ă̒l���N���A����
	m_state = STATE_STOP;			// ���
	m_nStateCount = 0;			// ��ԃJ�E���g

	// ���̐ݒ菈��
	SetEnableStep(true);			// ���݂�����ݒ�
	SetMove(MOVE);					// �ړ���
}

//=======================================
// �v���C���[�̔��菈��
//=======================================
void CItocan::CheckPlayer(void)
{
	if (CPlayer::Get() != nullptr)
	{ // �v���C���[�̏�񂪂���ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// �v���C���[�̈ʒu
		D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
		D3DXVECTOR3 rot = GetRot();		// �������擾����

		if (posPlayer.x >= pos.x)
		{ // �v���C���[�̈ʒu�����g�����E�ɂ���ꍇ

			// ������ݒ肷��
			rot.y = -D3DX_PI * 0.5f;
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			rot.y = D3DX_PI * 0.5f;
		}

		// ������ݒ肷��
		SetRot(rot);
	}
}

//=======================================
// ��Ԃ̔��菈��
//=======================================
void CItocan::CheckState(void)
{
	// ���[�J���|�C���^�錾
	CPlayer* pPlayer = CPlayer::Get();		// �v���C���[�̏����擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu

	if (pPlayer != nullptr)
	{ // �v���C���[�̏�񂪂���ꍇ

		if (fabsf(pos.x - pPlayer->GetPos().x) <= MOVE_DISTANCE)
		{ // ��苗�����̏ꍇ

			// �ړ���Ԃɂ���
			m_state = STATE_MOVE;
		}
		else
		{ // ��L�ȊO

			// �ʒu��ݒ肷��
			pos = GetInitPos();

			// �O��̈ʒu��ݒ肷��
			SetPosOld(GetInitPos());

			// ��~��Ԃɂ���
			m_state = STATE_STOP;
		}
	}
	else
	{ // ��L�ȊO

		// ��~��Ԃɂ���
		m_state = STATE_STOP;
	}

	// ����K�p����
	SetPos(pos);		// �ʒu
}

//=======================================
// �ړ�����
//=======================================
void CItocan::Move(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����
	D3DXVECTOR3 move = GetMove();	// �ړ���

	// �ړ��ʂ�ݒ肷��
	pos.x += sinf(-rot.y) * move.x;

	// �ʒu��ݒ肷��
	SetPos(pos);
}