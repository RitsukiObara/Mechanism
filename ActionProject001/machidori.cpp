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
#include "fraction.h"
#include "destruction.h"
#include "Particle.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define COLLISION_SIZE			(D3DXVECTOR3(40.0f, 93.0f, 44.0f))		// �����蔻��̃T�C�Y
#define MOVE_DISTANCE			(1400.0f)		// �ړ����鋗��
#define ROT_MOVE				(0.05f)			// �����̈ړ���
#define ADD_HEIGHT				(300.0f)		// �ǉ����鍂��
#define MOVE_HEIGHT				(50.0f)			// Y���̈ړ���
#define MOVE_WIDTH				(2.0f)			// X���̈ړ���
#define STANDBY_CORRECT			(0.08f)			// �X�^���o�C��Ԃ̕␳
#define STANDBY_ROT_DEST		(0.4f)			// �X�^���o�C��Ԃ̖ړI�̌���
#define STANDBY_COUNT			(60)			// �X�^���o�C��Ԃ̃J�E���g
#define ATTACK_CORRECT			(0.6f)			// �X�^���o�C��Ԃ̕␳
#define ATTACK_ROT_DEST			(0.0f)			// �X�^���o�C��Ԃ̖ړI�̌���
#define ATTACK_DOWN				(20.0f)			// �U����Ԃ̍~����
#define ATTACK_COUNT			(80)			// �U����Ԃ̃J�E���g
#define UP_HEIGHT				(10.0f)			// �U����Ԃ̍���
#define FRACTION_COUNT			(6)				// �j�Ђ̐�
#define DEATH_VIB_COUNT			(4)				// ���S���̐U������J�E���g
#define DEATH_COUNT				(60)			// ���S����܂ł̃J�E���g
#define DEATH_DSTR_SIZE			(D3DXVECTOR3(40.0f,40.0f,0.0f))			// ���S���̌��j�̃T�C�Y
#define DEATH_DSTR_COL			(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f))		// ���S���̌��j�̐F
#define DEATH_DSTR_LIFE			(20)			// ���S���̌��j�̎���
#define SMASH_ROTMOVE_Z			(0.02f)			// ������ю��̌����̈ړ���
#define SMASH_DEATH_COUNT		(70)			// �������ł��玀�ʂ܂ł̃J�E���g
#define HIT_DSTR_SIZE			(D3DXVECTOR3(40.0f,40.0f,0.0f))			// �q�b�g���̌��j�̃T�C�Y
#define HIT_DSTR_COL			(D3DXCOLOR(1.0f, 0.7f, 0.1f, 1.0f))		// �q�b�g���̌��j�̐F
#define HIT_DSTR_LIFE			(10)			// �q�b�g���̌��j�̎���

//==============================
// �R���X�g���N�^
//==============================
CMachidori::CMachidori() : CEnemy(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_state = STATE_FLY;	// ���
	m_nStateCount = 0;		// ��ԃJ�E���g
	m_fCurveRot = 0.0f;		// �J�[�u�p����
	m_fHeight = ADD_HEIGHT;	// �ǉ��̍���
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
	m_nStateCount = 0;		// ��ԃJ�E���g
	m_fCurveRot = 0.0f;		// �J�[�u�p����
	m_fHeight = ADD_HEIGHT;	// �ǉ��̍���
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

		// �X�^���o�C���
		StandBy();

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		if (m_nStateCount % STANDBY_COUNT == 0)
		{ // ��ԃJ�E���g�����ȏ�ɂȂ����ꍇ

			// ��ԃJ�E���g��0�ɂ���
			m_nStateCount = 0;

			// �U����Ԃɂ���
			m_state = STATE_ATTACK;

			// �ǉ��̍�����ݒ肷��
			m_fHeight = 0.0f;
		}

		break;

	case STATE_ATTACK:

		// �U����Ԃł̌����̐ݒ菈��
		AttackRot();

		// �U����Ԃ̍~������
		AttackDown();

		// �N���n�ʂƂ̓����蔻��
		if (ElevationCollision() == true)
		{
			// ��ԃJ�E���g�����Z����
			m_nStateCount++;
		}

		if (m_nStateCount >= ATTACK_COUNT)
		{ // ��ԃJ�E���g�����ȏ�̏ꍇ

			// �O��̍��E�󋵂̐ݒ菈��
			SetRightOld();

			// ��ԃJ�E���g������������
			m_nStateCount = 0;

			// �㏸��Ԃɂ���
			m_state = STATE_UP;
		}

		break;

	case STATE_UP:

		// �N���n�ʂ̓����蔻��
		Elevation();

		// �㏸��Ԃ̏㏸����
		UpAscent();

		break;

	case STATE_DEATH:

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		// ���S���̐U������
		DeathVib();

		// �d�͏���
		Gravity();

		// �N���n�ʂƂ̓����蔻��
		ElevationCollision();

		if (m_nStateCount >= DEATH_COUNT)
		{ // ��ԃJ�E���g����萔�ɂȂ����ꍇ

			// ���j�̐�������
			CDestruction::Create(GetPos(), DEATH_DSTR_SIZE, DEATH_DSTR_COL, CDestruction::TYPE_THORN, DEATH_DSTR_LIFE);

			// �p�[�e�B�N���̐�������
			CParticle::Create(GetPos(), CParticle::TYPE_ENEMYDEATH);

			// ���[�J���ϐ��錾
			CFraction::TYPE type = CFraction::TYPE_SCREW;

			for (int nCnt = 0; nCnt < FRACTION_COUNT; nCnt++)
			{
				// ��ނ�ݒ肷��
				type = (CFraction::TYPE)(rand() % CFraction::TYPE_MAX);

				// �j�Ђ̐�������
				CFraction::Create(GetPos(), type);
			}

			// �I������
			Uninit();

			// ���̐�̏������s��Ȃ�
			return;
		}

		break;

	case STATE_SMASH:

		// ��ԃJ�E���g�����Z����
		m_nStateCount++;

		// �d�͏���
		Gravity();

		// ������я���
		Smash();

		if (m_nStateCount >= SMASH_DEATH_COUNT)
		{ // ��ԃJ�E���g����萔�ɂȂ����ꍇ

			// �I������
			Uninit();

			// ���̐�̏������s��Ȃ�
			return;
		}

		break;

	default:

		// ��~
		assert(false);

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
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posDstr = GetPos();		// ���j���o���ʒu
	D3DXVECTOR3 move = GetMove();		// �ړ���

	// �����蔻��󋵂� OFF �ɂ���
	SetEnableCollision(false);

	// ��ԃJ�E���g������������
	m_nStateCount = 0;

	// ���S��Ԃɐݒ肷��
	m_state = STATE_DEATH;

	// �ړ��ʂ�ݒ肷��
	move.y = 0.0f;

	// �ړ��ʂ�K�p����
	SetMove(move);

	// �G�t�F�N�g���o���ʒu��ݒ肷��
	posDstr.y += GetCollSize().y;

	// ���j�̐�������
	CDestruction::Create(posDstr, HIT_DSTR_SIZE, HIT_DSTR_COL, CDestruction::TYPE_AIRY, HIT_DSTR_LIFE);
}

//=====================================
// ������уq�b�g����
//=====================================
void CMachidori::SmashHit(void)
{
	// ������уq�b�g����
	CEnemy::SmashHit();

	// �����蔻��󋵂� OFF �ɂ���
	SetEnableCollision(false);

	// ��ԃJ�E���g������������
	m_nStateCount = 0;

	// ������я�Ԃɐݒ肷��
	m_state = STATE_SMASH;

	// ���j�̐�������
	CDestruction::Create(GetPos(), DEATH_DSTR_SIZE, DEATH_DSTR_COL, CDestruction::TYPE_THORN, DEATH_DSTR_LIFE);

	// �p�[�e�B�N���̐�������
	CParticle::Create(GetPos(), CParticle::TYPE_ENEMYDEATH);

	// ���[�J���ϐ��錾
	CFraction::TYPE type = CFraction::TYPE_SCREW;

	for (int nCnt = 0; nCnt < FRACTION_COUNT; nCnt++)
	{
		// ��ނ�ݒ肷��
		type = (CFraction::TYPE)(rand() % CFraction::TYPE_MAX);

		// �j�Ђ̐�������
		CFraction::Create(GetPos(), type);
	}
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
	m_nStateCount = 0;		// ��ԃJ�E���g
	m_fCurveRot = 0.0f;		// �J�[�u�p����
	m_fHeight = ADD_HEIGHT;	// �ǉ��̍���

	// �O��̍��E�󋵂̐ݒ菈��
	SetRightOld();

	// ���̐ݒ菈��
	SetEnableStep(true);			// ���݂�����ݒ�
	SetCollSize(COLLISION_SIZE);	// �����蔻��̃T�C�Y
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
			move.x = MOVE_WIDTH;

			if (m_bRight == false)
			{ // �O�񂪍������̏ꍇ

				// �X�^���o�C��Ԃɂ���
				m_state = STATE_STANDBY;
			}
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			move.x = -MOVE_WIDTH;

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
	pos.y += sinf(m_fCurveRot) * MOVE_HEIGHT + m_fHeight;

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

//=====================================
// �X�^���o�C����
//=====================================
void CMachidori::StandBy(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();		// �������擾����

	// �����̕␳����
	useful::RotCorrect(STANDBY_ROT_DEST, &rot.x, STANDBY_CORRECT);

	// ������K�p����
	SetRot(rot);
}

//=====================================
// �U����Ԃł̌����̐ݒ菈��
//=====================================
void CMachidori::AttackRot(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();		// �������擾����

	// �����̕␳����
	useful::RotCorrect(ATTACK_ROT_DEST, &rot.x, ATTACK_CORRECT);

	// ������K�p����
	SetRot(rot);
}

//=====================================
// �U����Ԃ̍~������
//=====================================
void CMachidori::AttackDown(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	// �ʒu��������
	pos.y -= ATTACK_DOWN;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// �㏸��Ԃ̏㏸����
//=====================================
void CMachidori::UpAscent(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����

	// �ǉ��̍�����ݒ肷��
	m_fHeight += UP_HEIGHT;

	if (m_fHeight >= ADD_HEIGHT)
	{ // ��������萔�ȏ�ɂȂ����ꍇ

		// ������ݒ肷��
		m_fHeight = ADD_HEIGHT;

		// ���V��Ԃɂ���
		m_state = STATE_FLY;
	}

	// �ʒu��ݒ肷��
	pos.y += sinf(m_fCurveRot) * MOVE_HEIGHT + m_fHeight;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// ���S���̐U������
//=====================================
void CMachidori::DeathVib(void)
{
	if (m_nStateCount % DEATH_VIB_COUNT == 0)
	{
		// ���[�J���ϐ��錾
		D3DXVECTOR3 rot = GetRot();		// ����

		// ������ݒ肷��
		rot.x = (rand() % 51 - 25) * 0.01f;
		rot.z = (rand() % 51 - 25) * 0.01f;

		// ������K�p����
		SetRot(rot);
	}
}

//=====================================
// ������я�Ԃ̏���
//=====================================
void CMachidori::Smash(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����
	D3DXVECTOR3 move = GetMove();	// �ړ���

	// ������ݒ肷��
	rot.z += SMASH_ROTMOVE_Z;

	// �����̐��K������
	useful::RotNormalize(&rot.z);

	// �ʒu���X�V����
	pos.x += move.x;
	pos.z += move.z;

	// ����K�p����
	SetPos(pos);		// �ʒu
	SetRot(rot);		// ����
}